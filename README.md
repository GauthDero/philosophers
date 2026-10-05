*This project has been created as part of the 42 curriculum by gdero*

# Philosophers

## Description

An implementation of the classic Dining Philosophers problem, a well-known synchronization
challenge in computer science. The goal is to simulate several philosophers sharing a limited
number of forks, each needing two forks to eat, while avoiding deadlocks, race conditions, and
philosopher starvation.

## How it works

- Each philosopher is simulated as a separate thread.
- Shared resources (forks) are protected using mutexes to prevent race conditions.
- The simulation monitors philosopher states (eating, sleeping, thinking) and detects if a
  philosopher dies from starvation within a given time limit.

## Usage

```bash
make
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep>
```
