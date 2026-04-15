This project has been created as part of the 42 curriculum by miwehbe.

# philosopher

## Description

Philosophers is a 42 project based on the classic Dining Philosophers problem. The idea is simple: a bunch of philosophers are sitting at a round table with a bowl of spaghetti in the middle. Each philosopher needs two forks to eat, but there is only one fork between each pair of philosophers. They spend their time eating, sleeping, and thinking — and your job is to make sure none of them starve.

The catch is that each philosopher runs as a separate thread, and the forks are shared resources. If you don't handle access to those forks carefully, you end up with data races, deadlocks, or a dead philosopher — none of which are acceptable.

This project is where you learn threads and mutexes for real. Not just the theory — you actually have to use them correctly under timing pressure, and a single mistake can cause a philosopher to die milliseconds too late or two threads to grab the same fork at the same time. It's the kind of project that teaches you to think about concurrency in a way that nothing else really does.

---

## Instructions

### Compilation

```bash
cd philo
make
```

### Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers` — how many philosophers (and forks) are at the table
- `time_to_die` (ms) — if a philosopher hasn't started eating within this time since their last meal, they die
- `time_to_eat` (ms) — how long it takes to eat (holds two forks during this time)
- `time_to_sleep` (ms) — how long a philosopher sleeps after eating
- `number_of_times_each_philosopher_must_eat` (optional) — simulation stops when all philosophers have eaten this many times

### Examples

```bash
# 5 philosophers, none should die
./philo 5 800 200 200

# 4 philosophers, each must eat at least 3 times
./philo 4 410 200 200 3

# 1 philosopher — will always die (only one fork)
./philo 1 800 200 200
```

### Make rules

```bash
make        # builds the philo binary
make clean  # removes object files
make fclean # removes object files and binary
make re     # fclean + make
```

---

## How it works

Each philosopher is a thread. Each fork is protected by a mutex to prevent two philosophers from grabbing the same fork at the same time.

The lifecycle of each philosopher loops like this: think → take left fork → take right fork → eat → put forks down → sleep → repeat.

A separate monitoring routine checks continuously whether any philosopher has exceeded their `time_to_die` without starting a meal. If one has, it prints the death message and stops the simulation. All state messages (eating, sleeping, thinking, died) are printed with a timestamp in milliseconds.

The trickiest part is making sure the death detection is accurate within 10ms, and that no two messages ever print at the same time — which requires careful use of mutexes around the printing as well.

---

## Resources

- [man - pthread_create](https://man7.org/linux/man-pages/man3/pthread_create.3.html) — creating threads
- [man - pthread_mutex_lock](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html) — locking and unlocking mutexes
- [man - gettimeofday](https://man7.org/linux/man-pages/man2/gettimeofday.2.html) — getting the current time in microseconds
- [man - usleep](https://man7.org/linux/man-pages/man3/usleep.3.html) — sleeping for microseconds
- [Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem) — the original problem explained clearly
- [CodeVault — Threads in C playlist](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2) — probably the most useful resource for this project

**How AI was used:** AI was used to help understand the concept of data races and why certain mutex locking orders can lead to deadlocks. No code was written by AI — all implementation was done manually after understanding the concepts through the resources above and peer discussions.

---

"It compiles, no one dies, no data races. I've never been more proud of something I barely understand."