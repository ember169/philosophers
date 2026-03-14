*This project has been created as part of the 42 curriculum by lgervet*

# philosophers
![Dining Philosophers' Problem](https://github.com/user-attachments/assets/ad104678-976e-4058-b291-e3316bd2a677)<br>
Discovering Linux threads and mutexes through the classic [Philosopher's dining problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem).

## Description
This project is a simulation of the classic synchronization problem. Several philosophers sit at a round table, alternating between eating, sleeping, and thinking.

### The Rules
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
*Building...*

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

## Resources

### Documentation

- [pthreads, Linux Manpage](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [Multithreading in C, Geeksforgeeks, 2025](https://www.geeksforgeeks.org/c/multithreading-in-c/)
- [Why Are Threads Needed On Single Core Processors, Core Dumped, 2025](https://www.youtube.com/watch?v=M9HHWFp84f0)
- [Threads On Multicore Systems, Core Dumped, 2025](https://www.youtube.com/watch?v=5sw9XJokAqw)
- [The gettimeofday() Function, C for dummies, 2020](https://c-for-dummies.com/blog/?p=4236)
- [Passing struct to pthread as an argument, Stack overflow, 2014](https://stackoverflow.com/questions/20196121/passing-struct-to-pthread-as-an-argument)
- [Dining Philosophers' problem, Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Mutual Exclusion, Wikipedia](https://en.wikipedia.org/wiki/Mutual_exclusion)
- [Lock in computer science, Wikipedia](https://en.wikipedia.org/wiki/Lock_(computer_science))
- [Spinlock, Wikipedia](https://en.wikipedia.org/wiki/Spinlock)
- [Test and set, Wikipedia](https://en.wikipedia.org/wiki/Test-and-set)
- [Pthread mutex lock, Pubs opengroup](https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread_mutex_lock.html)
- [Pthread mutex init, Pubs opengroup](https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread_mutex_init.html)
- [ANSI codes for terminal colors, Github](https://github.com/SanderMertens/colorize/blob/master/colorize.c)

### AI Usage
*Building...*
