# Known Issues

## Fork-acquisition starvation bug (unresolved)

`philosophers_tester` flags two related failures that remain unresolved as of 2026-07-05:

- `./philo 5 900 295 60 10` — dies deterministically, even though nobody should (best-case cycle is only 355ms against a 900ms `time_to_die`, a large margin).
- `./philo 8 180 60 121 2` — flaky: a death is expected but doesn't always happen.

### Root cause

`_dispatch_even`/`_dispatch_odd` in `srcs/philo_meals.c` use plain blocking `pthread_mutex_lock` for each fork in sequence (parity-based ordering: even ids take left-then-right, odd ids take right-then-left). This prevents **deadlock** but not **starvation**: a philosopher can successfully grab its first fork, then block indefinitely on its second fork *while still holding the first* — a "fork hostage" pattern. Traced exactly once via log timestamps: philosopher 5 grabs fork1 (needed by philosopher 1) then blocks on fork5 (held by philosopher 4, eating), holding fork1 hostage long enough that philosopher 1 misses its own death deadline.

### Hard constraints

`en.subject.pdf` Chapter VI's authorized-function list for the mandatory part is exhaustive (see also `README.md`'s "Authorized external functions" line):

```
memset, printf, malloc, free, write, usleep, gettimeofday,
pthread_create, pthread_detach, pthread_join,
pthread_mutex_init, pthread_mutex_destroy,
pthread_mutex_lock, pthread_mutex_unlock
```

Notably **not** authorized: `pthread_mutex_trylock`, `sem_t`/semaphore.h, `pthread_cond_*`. Any fix must be built only from blocking mutex lock/unlock plus `usleep`-based polling. A semaphore-based "arbitrator" solution was also explicitly ruled out by preference, independent of the subject constraint.

### Attempts tried (all reverted — none achieved zero regression)

1. **Global gate mutex (capacity 1)**, held across the whole fork-acquisition sequence. Over-serialized the entire ring (stalled unrelated philosophers too) — made timing worse, not better.
2. **"Arbitrator" admission bound** (`n-1` concurrent philosophers allowed to acquire-or-eat, via a hand-rolled mutex + counter). Zero effect: actual peak contention in the failing case is only 2-3 out of 5 philosophers, well under any `n-1` cap. This bug is about *duration* a fork is held hostage, not the *count* of concurrent attempters.
3. **Manual "trylock" emulation** (`bool fork_taken[n]` + dedicated mutex, atomic check-and-reserve both fork indices before touching the real fork mutexes). Logically sound but introduced real data races (new Helgrind/ThreadSanitizer failures) that weren't root-caused before reverting.
4. **Atomic all-or-nothing claim** (single `table_mutex` + `bool fork_busy[n]`, with exactly one helper function as the sole code path touching the flag array, called on every exit path). This one was race-free and deadlock-free, and cut the `5 900 295 60 10` death rate from 10/10 to ~8/10 — but not to zero. Residual failure traced precisely: two neighbors with *identical* eat/sleep durations start in perfect lockstep and release/reclaim their shared boundary fork at the exact same instant forever, permanently excluding the philosopher sandwiched between them (a deterministic resonance, not bad luck).
5. **Jittered backoff** on top of attempt 4 (vary retry `usleep` by philosopher id + current time). No meaningful improvement — the resonance is driven by the *reclaiming neighbors'* synchronized timing, not the waiting philosopher's poll interval.
6. **Reintroducing the startup stagger** on top of attempt 4 (delay each philosopher's first attempt by `(id-1)*time_to_eat/n`). Fixed `5 900 295 60 10` (10/10 across 30 runs) but **regressed** `4 410 200 200 10`, `4 800 390 60 10`, and `8/18 180 85 85 10` — net trade of one failure set for another.

### Current state

`main` has all starvation-fix attempts reverted. Only these fixes remain applied (both validated, no regression):
- Startup-stagger **removal** (not the same as attempt 6 above — the original stagger caused a *different* deterministic bug, fixed early in the investigation; do not reintroduce without re-sweeping the full test battery).
- Norminette fixes (`exit.c` re-indented, `manager.c` long-line split, `philo_spawn.c` redundant parameter removed).

### If picking this back up

The unexplored direction: a genuine priority/fairness rule (e.g. a reclaiming philosopher checks whether a neighbor has been waiting and yields), not another symmetric admission-control or jitter tweak — both were tried and don't address the actual resonance mechanism. Any new attempt should be swept against the full battery in `philosophers_tester/src/tests.py` (`death_1` ×5, `death_2` ×10, `death_3` ×10, `other` ×10), with multiple runs for timing-sensitive cases, before being considered fixed.
