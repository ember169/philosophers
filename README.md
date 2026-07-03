*This project has been created as part of the 42 curriculum by lgervet*

# philosophers
![Dining Philosophers' Problem](https://github.com/user-attachments/assets/ad104678-976e-4058-b291-e3316bd2a677)<br>
Discovering Linux threads and mutexes through the classic [Philosopher's dining problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem).

## Description
This project is a simulation of the classic synchronization problem. Several philosophers sit at a round table, alternating between eating, sleeping, and thinking.

### The Rules
*[Subject](https://cdn.intra.42.fr/pdf/pdf/199862/en.subject.pdf)*
- Dining Setup: One philosopher, one bowl of spaghetti, and as many forks as there are philosophers.
- The Fork Dilemma: A philosopher needs two forks to eat—the one to their left and the one to their right.
- The Routine: 
  -  Eat: Pick up two forks, eat for a set time.
  -  Sleep: Put down forks and rest.
  -  Think: Wait for forks to become available again.
- Survival: Philosophers must eat within a specific timeframe or they will die of starvation.
- Constraints:
  - Philosophers do not communicate.
  - They have no knowledge of the health status of others.
  - The simulation stops immediately if a philosopher dies.
- Authorized external functions: 
  > `memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`, `pthread_create`, `pthread_detach`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock`


### Implementation

#### Architecture Overview

```
./philo <nb_philos> <time_to_die> <time_to_eat> <time_to_sleep> [must_eat_nb]
          │
          ▼
       main.c
  ┌──────────────────────────────────────────────────────────┐
  │  1. get_rules()       → parse args into t_rules          │
  │  2. malloc(t_philo[]) → array of N philosophers          │
  │  3. malloc(mutex[])   → array of N fork mutexes          │
  │  4. alloc_forks()     → pthread_mutex_init each fork     │
  │  5. initialize_threads()                                 │
  │       ├─ create_threads() → spawn N philo threads        │
  │       └─ pthread_create  → spawn 1 manager thread        │
  │  6. pthread_join(manager) → wait for simulation end      │
  │  7. (main calls clean_exit on exit)                   │
  └──────────────────────────────────────────────────────────┘

Philosopher threads (routine):          Manager thread (manage_philo):
  while (!should_die):                    infinite loop:
    try_to_eat()                            for each philo:
      lock left_fork                          check time since last meal
      lock right_fork                         if > time_to_die → mark dead
      update last_meal_time (meal_mutex)    if any dead → clean_exit()
      sleep(time_to_eat)
      unlock forks
    sleep(time_to_sleep)
    think
  print "died"
```

**Data structures:**
- `t_rules` — shared config: N, time_to_die/eat/sleep, must_eat_number, launch_time, manager thread
- `t_philo` — per philosopher: id, should_die, last_meal_time, meal_mutex, thread_id, left/right fork ptrs, rules ptr

**Key mutexes:**
- N fork mutexes (in forks[] array) — prevent two philosophers using same fork
- Per-philosopher meal_mutex — protect last_meal_time reads/writes

## Instructions

### Compiling
Run `make` in root repertory to compile the binary.<br>
Run `make re` to delete and recompile the binary.

### Executing
Run the program with the following arguments:
```
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

**Arguments:**
1. `number_of_philosophers`: Number of philosophers and forks.
2. `time_to_die` (ms): Maximum time between two meals before a philosopher dies.
3. `time_to_eat` (ms): Time taken to eat (requires two forks).
4. `time_to_sleep` (ms): Time spent sleeping.
5. `number_of_times_each_philosopher_must_eat` (Optional): If all philosophers eat this many times, the simulation stops.<br>

**Example**:
```
./philo 5 800 200 200
```

### Verification

- `make` should compile with `-Wall -Wextra -Werror` and no warnings
- `./philo 5 800 200 200` — should run indefinitely with no deaths
- `./philo 1 800 200 200` — philosopher should die after ~800ms
- `./philo 4 310 200 100` — a philosopher should die
- `./philo 5 800 200 200 7` — should stop after each philosopher eats 7 times
- Run with `-fsanitize=thread` (already in Makefile) — zero data race reports

## Resources

### Documentation
#### Concept & Theory
- [Dining Philosophers' problem, Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Mutual Exclusion, Wikipedia](https://en.wikipedia.org/wiki/Mutual_exclusion)
- [Lock in computer science, Wikipedia](https://en.wikipedia.org/wiki/Lock_(computer_science))
- [Spinlock, Wikipedia](https://en.wikipedia.org/wiki/Spinlock)
- [Test and set, Wikipedia](https://en.wikipedia.org/wiki/Test-and-set)
- [Why Are Threads Needed On Single Core Processors, Core Dumped, 2025](https://www.youtube.com/watch?v=M9HHWFp84f0)
- [Threads On Multicore Systems, Core Dumped, 2025](https://www.youtube.com/watch?v=5sw9XJokAqw)

#### Learning Resources (Threads & Mutex)
- [Unix Threads in C, Youtube, 2021](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
- [Multithreading in C, Geeksforgeeks, 2025](https://www.geeksforgeeks.org/c/multithreading-in-c/)
- [Threads mutex et programmation concurrente en C, Codequoi, 2022](https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/)

#### Technical Reference & Helpers
- **Manpages**: [pthreads](https://man7.org/linux/man-pages/man7/pthreads.7.html), [pthread_mutex_lock](https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread_mutex_lock.html), [pthread_mutex_init](https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread_mutex_init.html)
- **Code tips**: [The gettimeofday() function](https://c-for-dummies.com/blog/?p=4236), [Passing struct to pthread as an argument](https://stackoverflow.com/questions/20196121/passing-struct-to-pthread-as-an-argument), [ANSI codes for terminal colors](https://github.com/SanderMertens/colorize/blob/master/colorize.c)
- **Vizualisation & debugging**:[Philogramm](https://github.com/sugoidesune/42philogramm), [Data Race detection (-fsanitize=thread)](https://github.com/google/sanitizers/wiki/ThreadSanitizerCppManual)

### AI Usage
- Documentation hierarchy
- Code architecture documentation
- Key concepts of multithreading vulgarization
- Mutex architecture rework to safely print (`rules->print_mutex`)
- Batch testing
- Diagnose a deadlock risk in my philosopher loop