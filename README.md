<h1 align="center">42_philosophers</h1>

<p align="center">
  <a href="#about">About</a> &#xa0; | &#xa0;
  <a href="#features">Features</a> &#xa0; | &#xa0;
  <a href="#usage">Usage</a> &#xa0; | &#xa0;
  <a href="#used-functions">Used functions</a> &#xa0;
</p>

<br>

## About

The Philosophers project is a concurrency problem designed to teach the basics of threading and process synchronization using mutexes. It simulates a scenario where philosophers sit at a table and alternately eat, sleep, and think. The challenge is to manage the shared resources (forks) in a way that avoids deadlock and ensures all philosophers get a chance to eat.

## Features

- Simulate multiple philosophers sitting at a round table.
- Philosophers perform three actions: eat, think, and sleep.
- Philosophers use two forks to eat, which are shared resources.
- Ensure philosophers do not starve by managing their eating times.
- Implement mutexes to prevent data races and ensure correct fork usage.
- Log state changes of philosophers in a formatted manner.

## Usage

Parameters:

- number_of_philosophers: The number of philosophers and forks.
- time_to_die (in milliseconds): Maximum time a philosopher can go without eating before dying.
- time_to_eat (in milliseconds): Time a philosopher spends eating.
- time_to_sleep (in milliseconds): Time a philosopher spends sleeping.
- number_of_times_each_philosopher_must_eat (optional): If provided, the simulation stops when all philosophers have eaten at least this many times.

```shell
cd philo && make && ./philo 5 800 200 200 10
```

## Used functions

| **Function**          | **Man**                     | **Short Description**                        |
| --------------------- | --------------------------- | -------------------------------------------- |
| printf                | man 3 printf                | Prints formatted output to stdout            |
| malloc                | man 3 malloc                | Allocates a block of memory dynamically      |
| free                  | man 3 free                  | Deallocates a block of memory                |
| usleep                | man 3 usleep                | Suspends execution for microsecond intervals |
| gettimeofday          | man 2 gettimeofday          | Gets the current time                        |
| pthread_create        | man 3 pthread_create        | Creates a new thread                         |
| pthread_join          | man 3 pthread_join          | Waits for a thread to terminate              |
| pthread_mutex_init    | man 3 pthread_mutex_init    | Initializes a mutex                          |
| pthread_mutex_destroy | man 3 pthread_mutex_destroy | Destroys a mutex                             |
| pthread_mutex_lock    | man 3 pthread_mutex_lock    | Locks a mutex                                |
| pthread_mutex_unlock  | man 3 pthread_mutex_unlock  | Unlocks a mutex                              |

<br>

<div align="center">
  Made by <a href="https://github.com/Szabold1" target="_blank">Boldi</a>
</div>
