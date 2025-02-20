```

                *    .    *    .    *
           .    *    .  PHILOSOPHERS  .    *    .
        *    .    *    .    *    .    *    .    *

```

# Philosophers ❄️

Welcome to the **Philosophers** project! This is a classic synchronization problem that involves multiple philosophers sitting around a table, thinking, and eating spaghetti. The challenge is to manage their behavior using multithreading while avoiding deadlocks and starvation.

## ❄️ Overview
The Dining Philosophers problem is a well-known problem in computer science that illustrates the difficulties of resource sharing and process synchronization. This implementation ensures that philosophers eat without encountering race conditions or deadlocks.

## ❄️ Features
- Efficient synchronization using mutexes and threads.
- Avoids deadlocks using careful design.
- Implements solutions for various numbers of philosophers.
- Handles edge cases and ensures smooth execution.

## ❄️ Installation
```sh
make
```

## ❄️ Usage
Run the program with:
```sh
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```
Example:
```sh
./philo 5 800 200 200
```

## ❄️ Rules
- Each philosopher must pick up two forks (mutexes) before eating.
- Philosophers alternate between eating, thinking, and sleeping.
- If a philosopher doesn’t eat within `time_to_die` milliseconds, they die.
- The simulation stops when a philosopher dies or when a specific number of meals is reached (optional argument).

## ❄️ Implementation Details
- Uses **pthread_mutex_t** for synchronization.
- Implements a structured logging system to track philosopher states.
- Ensures minimal starvation and optimized performance.

## ❄️ Notes
- No data races should occur.
- The use of `usleep()` helps regulate time precision.

## ❄️ Author
Developed with patience, logic, and a bit of spaghetti. 🍝

---

                *    .    *    .    *
           .    *    .  🍽️  💭  🍝  .    *    .
        *    .    *    .    *    .    *    .    *

```


