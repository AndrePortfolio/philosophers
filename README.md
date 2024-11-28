# Philosophers Project

## Overview

The **Philosophers** project is a classic concurrency problem in computer science designed to teach the basics of multithreading, synchronization, and deadlock prevention. In this project, you will simulate the behavior of philosophers who sit around a table with a bowl of spaghetti and forks. The challenge is to manage concurrent access to shared resources (the forks) in such a way that the philosophers can eat, think, and sleep without starving or causing deadlock.

![image](https://github.com/AndrePortfolio/philosophers/blob/main/philosophers.png)

## What You Will Learn

- **Multithreading**: Understand how to create and manage threads using the `pthread` library in C.
- **Synchronization**: Use mutexes to prevent race conditions and ensure safe access to shared resources.
- **Thread Lifecycle**: Learn how to start, detach, and join threads.
- **Time Management**: Use functions like `usleep()` and `gettimeofday()` for accurate time tracking.
- **Program Safety**: Implement measures to avoid data races, segmentation faults, and memory leaks.

## Project Requirements

### Mandatory Part (`philo`)

1. **Arguments**:
   - `number_of_philosophers`: Number of philosophers and forks.
   - `time_to_die`: Time in milliseconds a philosopher can go without eating before dying.
   - `time_to_eat`: Time in milliseconds a philosopher takes to eat.
   - `time_to_sleep`: Time in milliseconds a philosopher sleeps.
   - `number_of_times_each_philosopher_must_eat` (optional): Simulation stops when all philosophers eat this number of times, or when a philosopher dies if not specified.
   
2. **Rules**:
   - Each philosopher is a separate thread.
   - Use mutexes to synchronize fork usage to avoid deadlock.
   - Properly handle shared resources to avoid data races.
   - Print state changes as per the specified format (e.g., "timestamp_in_ms X is eating").
   - Ensure that no philosopher dies due to starvation.

![image](https://github.com/AndrePortfolio/philosophers/blob/main/philo.png)

3. **Functions**:
   - Utilize functions such as `pthread_create`, `pthread_detach`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_lock`, `pthread_mutex_unlock`, `gettimeofday`, and `usleep`.

4. **External Libraries**:
   - No libft or any other external library is allowed for the mandatory part.
   - You can only use standard C libraries like `stdio.h`, `stdlib.h`, `string.h`, `unistd.h`, etc.

## What Needs to Be Done

1. **Design the Program**:
   - Set up the basic program structure with separate threads for each philosopher.
   - Create mutexes to handle forks and avoid data races.

2. **Implement Synchronization**:
   - Ensure that philosophers pick up and put down forks in a way that avoids deadlocks.
   - Use `pthread_mutex_lock` and `pthread_mutex_unlock` to protect shared resources.

3. **Handle Time Management**:
   - Use `gettimeofday` for accurate timestamps.
   - Implement `usleep()` to simulate eating, thinking, and sleeping times.

4. **Error Handling**:
   - Prevent issues like segmentation faults, double frees, and memory leaks.
   - Ensure the program does not have undefined behaviors.

5. **Log State Changes**:
   - Print the status of each philosopher with timestamps.
   - Make sure the "died" status is printed within 10 milliseconds of the actual death event.

## What I Learned

Through this project, I gained practical experience with:

- **Concurrency in C**: Writing multithreaded applications using `pthread` and managing concurrent operations safely.
- **Synchronization Techniques**: Learning to use mutexes effectively to prevent race conditions and ensuring the integrity of shared resources.
- **Problem Solving**: Applying algorithmic thinking to solve synchronization challenges, such as ensuring no deadlocks and managing resource allocation.
- **Debugging and Testing**: Using tools and techniques to test and debug multi-threaded applications, identifying potential issues with race conditions and deadlocks.
- **Programming Best Practices**: Writing code that adheres to standards, manages resources efficiently, and avoids common pitfalls in C programming.

## How to Run
    ```bash
      git clone https://github.com/AndrePortfolio/philosophers.git
      cd philosophers
      make
      ./philo <nbr-philos> <time-to-die> <time-to-eat> <time-to-sleep> <nbr-meals>
   ```
