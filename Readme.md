This project has been created as part of the 42 curriculum by miwehbe.

# Philosopher

This project is part of the 42 curriculum, based on the classic dining philosophers problem: philosophers sit around a table, each one needs two forks to eat, but there's only one fork between each two neighbors.
Each philosopher is a thread, forks are mutexes , and if you don't handle things carefully, you get data races, deadlocks, or someone dying when they shouldn't.

# Usage
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

# Example:
```bash
# No one should die
./philo 5 800 200 200

# Each philosopher must eat at least 3 times
./philo 4 410 200 200 3

# One philosopher — guaranteed to die
./philo 1 800 200 200
```
# Make rules
```bash
make        # build the program
make clean  # remove object files
make fclean # remove object files + executable
make re     # clean everything and rebuild
```
# How it works
Each philosopher runs in a loop: think ->take forks -> eat -> sleep -> repeat
Forks are protected with mutexes so two philosophers can't grab the same fork at the same time. A separate monitor thread checks whether any philosopher has gone too long without eating ,if they hit time_to_die, it prints the death and stops everything.

# What was hard
- Avoiding deadlocks.
- Timing  everything is in ms, small delays matter.
- Making sure no two messages print at the same time.
- Debugging threads.

# Resources

- [man - pthread_create](https://man7.org/linux/man-pages/man3/pthread_create.3.html) : creating threads
- [man - pthread_mutex_lock](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html) : locking and unlocking mutexes
- [man - gettimeofday](https://man7.org/linux/man-pages/man2/gettimeofday.2.html) : getting the current time in microseconds
- [man - usleep](https://man7.org/linux/man-pages/man3/usleep.3.html) : sleeping for microseconds
- [Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem) : the original problem explained clearly
- [CodeVault — Threads in C playlist](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2) : probably the most useful resource for this project

# Notes
I used AI a bit just to understand some concepts like data races and deadlocks.

---

"It works. Nobody dies. I'm not touching it again."