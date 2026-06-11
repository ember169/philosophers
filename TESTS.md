# Philosophers — Test Reference

Build before every test session: `make re`

---

## 1. Argument Validation

All commands below must exit with code 1 and print nothing.

| # | Command | Expected |
|---|---|---|
| 1.1 | `./philo` | exit 1, no output |
| 1.2 | `./philo 5` | exit 1, no output |
| 1.3 | `./philo 5 800 200` | exit 1, no output |
| 1.4 | `./philo 5 800 200 200 7 8` | exit 1, no output |
| 1.5 | `./philo abc 800 200 200` | exit 1, no output |
| 1.6 | `./philo 5 abc 200 200` | exit 1, no output |
| 1.7 | `./philo 5 800 abc 200` | exit 1, no output |
| 1.8 | `./philo 5 800 200 abc` | exit 1, no output |
| 1.9 | `./philo 5 800 200 200 abc` | exit 1, no output |
| 1.10 | `./philo 5.5 800 200 200` | exit 1, no output |
| 1.11 | `./philo +5 800 200 200` | exit 1, no output |
| 1.12 | `./philo 0 800 200 200` | exit 1, no output |
| 1.13 | `./philo 5 0 200 200` | exit 1, no output |
| 1.14 | `./philo 5 800 0 200` | exit 1, no output |
| 1.15 | `./philo 5 800 200 0` | exit 1, no output |
| 1.16 | `./philo 5 800 200 200 0` | exit 1, no output |
| 1.17 | `./philo -1 800 200 200` | exit 1, no output |
| 1.18 | `./philo 5 -1 200 200` | exit 1, no output |
| 1.19 | `./philo 9999999999 800 200 200` | exit 1, no output (no OOM crash) |
| 1.20 | `./philo 5 9999999999 200 200` | exit 1, no output |

---

## 2. N=1 — Single Philosopher

One philosopher can only pick up one fork and will always starve.
`must_eat_nb` has no effect: the philosopher cannot eat and will die regardless.

| # | Command | Expected |
|---|---|---|
| 2.1 | `./philo 1 800 200 200` | Prints "has taken a fork", then "died" at ~800ms. Exactly 1 death. |
| 2.2 | `./philo 1 200 200 200` | "died" at ~200ms. |
| 2.3 | `./philo 1 100 200 200` | "died" at ~100ms. |
| 2.4 | `./philo 1 800 200 200 1` | must_eat ignored — still 1 death at ~800ms. |
| 2.5 | `./philo 1 800 200 200 5` | must_eat ignored — still 1 death at ~800ms. |

---

## 3. N=2

| # | Command | Expected |
|---|---|---|
| 3.1 | `timeout 5 ./philo 2 800 200 200` | Runs for 5s, 0 deaths. |
| 3.2 | `./philo 2 300 200 100` | 1 death at ~300ms. |
| 3.3 | `./philo 2 800 200 200 5` | 10 meals total, 0 deaths, then clean exit. |
| 3.4 | `./philo 2 200 100 100` | 0 deaths (cycle=200ms == time_to_die, but eating resets the clock). |

---

## 4. Canonical Test Cases

These are the four cases from the project subject.

| # | Command | Expected |
|---|---|---|
| 4.1 | `timeout 10 ./philo 5 800 200 200` | Runs indefinitely. 0 deaths over 10s. |
| 4.2 | `./philo 1 800 200 200` | Philosopher dies after ~800ms. |
| 4.3 | `./philo 4 310 200 100` | Exactly 1 philosopher dies. Death at ~310ms (≤320ms). |
| 4.4 | `./philo 5 800 200 200 7` | 35 total "is eating" lines, 0 deaths, then clean exit. |

---

## 5. Death Detection Accuracy

Subject requirement: a philosopher must not die more than **10ms** after `time_to_die`.

```sh
./philo 1 800 200 200       # "died" timestamp must be 800–810ms
./philo 4 310 200 100       # "died" timestamp must be 310–320ms
./philo 2 300 200 100       # "died" timestamp must be 300–310ms
./philo 5 200 200 200       # "died" timestamp must be 200–210ms
```

Check the timestamp printed before "died" and verify it is within 10ms of `time_to_die`.

---

## 6. Post-Death Output Correctness

No philosopher may print any state message after the "died" line has been printed.

```sh
./philo 4 310 200 100
```

- Exactly 1 "died" line in the output.
- The "died" line has the highest timestamp in the output (or is tied — no line after it).
- Run 5 times and verify the above holds on every run.

---

## 7. must_eat Variations

| # | Command | Expected |
|---|---|---|
| 7.1 | `./philo 5 800 200 200 1` | 5 "is eating" lines (1 per philo), 0 deaths, clean exit. |
| 7.2 | `./philo 5 800 200 200 7` | 35 "is eating" lines, 0 deaths, clean exit. |
| 7.3 | `./philo 2 800 200 200 5` | 10 "is eating" lines, 0 deaths, clean exit. |
| 7.4 | `./philo 3 800 200 200 3` | 9 "is eating" lines, 0 deaths, clean exit. |
| 7.5 | `./philo 1 800 200 200 1` | N=1 ignores must_eat — 1 death at ~800ms. |
| 7.6 | `./philo 5 100 10 10 5` | 25 "is eating" lines, 0 deaths, clean exit (fast timing). |

---

## 8. Tight / Borderline Timing

| # | Command | Expected |
|---|---|---|
| 8.1 | `timeout 5 ./philo 5 600 200 200` | 0 deaths (600 > 2×200). |
| 8.2 | `timeout 5 ./philo 4 600 200 200` | 0 deaths. |
| 8.3 | `./philo 3 500 200 200` | Death expected (with 3 philos, cycle ≈ 800ms > 500ms). |
| 8.4 | `./philo 5 200 200 200` | Death expected (time_to_die == time_to_eat, no slack). |
| 8.5 | `./philo 5 10 5 5` | Death expected (very tight, ~10ms). |
| 8.6 | `timeout 5 ./philo 10 50 10 10` | 0 deaths. |

---

## 9. Large N

| # | Command | Expected |
|---|---|---|
| 9.1 | `./philo 100 800 200 200 3` | 300 "is eating" lines, 0 deaths, clean exit. |
| 9.2 | `./philo 200 800 200 200 2` | 400 "is eating" lines, 0 deaths, clean exit. |

---

## 10. Consistency (Run 10 Times)

These tests must pass on every single run out of 10. Use the loop below.

```sh
# 4.4 — must_eat, no deaths
PASS=0; FAIL=0
for i in $(seq 1 10); do
    OUT=$(./philo 5 800 200 200 7 2>&1)
    D=$(echo "$OUT" | grep -c " died$" || true)
    M=$(echo "$OUT" | grep -c "is eating" || true)
    if [ "$D" -eq 0 ] && [ "$M" -eq 35 ]; then PASS=$((PASS+1))
    else FAIL=$((FAIL+1)); echo "  FAIL run $i: deaths=$D meals=$M"; fi
done
echo "PASS=$PASS FAIL=$FAIL"
```

```sh
# 6 — post-death correctness
for i in $(seq 1 10); do
    OUT=$(./philo 4 310 200 100 2>&1)
    D=$(echo "$OUT" | grep -c " died$" || true)
    if [ "$D" -eq 1 ]; then echo "run $i: OK"
    else echo "run $i: FAIL deaths=$D"; fi
done
```

---

## 11. TSan — Zero Data Races

The Makefile always builds with `-fsanitize=thread`. Run each command and check that the output contains **no** `ThreadSanitizer` warning lines.

```sh
timeout 3 ./philo 5 800 200 200     # must show no TSan warnings
./philo 1 800 200 200
./philo 4 310 200 100
./philo 5 800 200 200 7
./philo 5 800 200 200 1
./philo 2 800 200 200 5
./philo 1 800 200 200 1
```

Quick grep check:
```sh
./philo 5 800 200 200 7 2>&1 | grep -c "ThreadSanitizer"   # must print 0
```

---

## Quick Smoke Test (all in one)

Copy-paste this block to run the most important checks at once:

```sh
make re && \
echo "--- canonical ---" && \
OUT=$(timeout 5 ./philo 5 800 200 200 2>&1); echo "5 800 200 200: deaths=$(echo "$OUT" | grep -c ' died$')" && \
OUT=$(./philo 1 800 200 200 2>&1); echo "1 800 200 200: died_at=$(echo "$OUT" | grep ' died$' | awk '{print $1}')ms" && \
OUT=$(./philo 4 310 200 100 2>&1); echo "4 310 200 100: deaths=$(echo "$OUT" | grep -c ' died$')" && \
OUT=$(./philo 5 800 200 200 7 2>&1); echo "5 800 200 200 7: deaths=$(echo "$OUT" | grep -c ' died$') meals=$(echo "$OUT" | grep -c 'is eating')" && \
echo "--- validation ---" && \
./philo +5 800 200 200 2>&1; echo "+5: exit=$?" && \
./philo 9999999999 800 200 200 2>&1; echo "9999999999: exit=$?" && \
echo "--- TSan ---" && \
echo "5 800 200 200 7 TSan races: $(./philo 5 800 200 200 7 2>&1 | grep -c ThreadSanitizer)"
```

Expected output:
```
5 800 200 200: deaths=0
1 800 200 200: died_at=800ms  (or 801ms)
4 310 200 100: deaths=1
5 800 200 200 7: deaths=0 meals=35
+5: exit=1
9999999999: exit=1
5 800 200 200 7 TSan races: 0
```
