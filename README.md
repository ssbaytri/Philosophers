# Philosophers

<img src="https://drive.google.com/uc?id=1Eu68KX2zojsb3h0kDgCGgXbguJZDB4pF" alt="Philosophers" width="100%">

<div align="center">

[![42 School](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logo=42&logoColor=white)](https://42.fr)
[![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Threads](https://img.shields.io/badge/Threads-FF6B6B?style=for-the-badge&logo=cplusplus&logoColor=white)](https://en.wikipedia.org/wiki/Thread_(computing))
[![Mutex](https://img.shields.io/badge/Mutex-4ECDC4?style=for-the-badge&logo=lock&logoColor=white)](https://en.wikipedia.org/wiki/Mutex)
[![Semaphore](https://img.shields.io/badge/Semaphore-45B7D1?style=for-the-badge&logo=traffic-light&logoColor=white)](https://en.wikipedia.org/wiki/Semaphore_(programming))

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)
[![Made with Love](https://img.shields.io/badge/Made%20with-❤️-red.svg?style=for-the-badge)](https://github.com/yourusername)

</div>

<p align="center">
  <em>"I never thought philosophy would be so deadly"</em>
</p>

<p align="center">
  <strong>A 42 School project exploring concurrent programming through the classic Dining Philosophers Problem</strong>
</p>

## 📖 Overview

<div align="center">

| 🎯 **Objective** | 🧠 **Skills** | ⚡ **Difficulty** |
|:----------------:|:-------------:|:-----------------:|
| Threading & Synchronization | Concurrent Programming | ⭐⭐⭐⭐☆ |

</div>

The **Philosophers** project is a classic computer science problem that explores the fundamentals of threading, process synchronization, and resource management. This project simulates the famous "Dining Philosophers Problem" where philosophers sit around a table, alternating between eating, thinking, and sleeping while sharing limited resources (forks).

## 🎯 Project Goals

- Learn the basics of threading a process
- Understand thread creation and management
- Explore the use of mutexes and semaphores
- Handle resource sharing and synchronization
- Prevent deadlocks and race conditions

## 🧠 The Problem

**The Setup:**
- One or more philosophers sit at a round table
- There's a large bowl of spaghetti in the middle
- Philosophers alternate between three states: eating, thinking, and sleeping
- There are as many forks as philosophers on the table
- A philosopher needs **both** forks (left and right) to eat
- Philosophers don't communicate with each other
- The simulation stops when a philosopher dies of starvation

**The Challenge:**
- Every philosopher needs to eat and should never starve
- Philosophers should avoid dying!
- No data races allowed
- Proper synchronization is crucial

## 🚀 Usage

<div align="center">

### 🧵 Mandatory Part (Threads & Mutexes)
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### 🔄 Bonus Part (Processes & Semaphores)
```bash
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

</div>

### 📊 Parameters

<div align="center">

| Parameter | Description | Unit |
|:---------:|:------------|:----:|
| `number_of_philosophers` | Number of philosophers and forks | count |
| `time_to_die` | Maximum time between meals before death | ms |
| `time_to_eat` | Time spent eating (holding two forks) | ms |
| `time_to_sleep` | Time spent sleeping | ms |
| `number_of_times_each_philosopher_must_eat` | Optional: stops when all have eaten N times | count |

</div>

### 💡 Examples

<div align="center">

```bash
# Basic simulation with 5 philosophers
./philo 5 800 200 200

# Simulation that stops after each philosopher eats 5 times
./philo 4 410 200 200 5

# Bonus version with processes
./philo_bonus 3 600 150 150
```

</div>

## 📋 Program Output

The program logs each philosopher's state changes with timestamps:

```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

**Requirements:**
- No overlapping messages
- Death messages must appear within 10ms of actual death
- Timestamps in milliseconds since simulation start

## 🏗️ Implementation Details

<div align="center">

| Feature | Mandatory Part | Bonus Part |
|:-------:|:--------------:|:----------:|
| **Technology** | 🧵 Threads & Mutexes | 🔄 Processes & Semaphores |
| **Structure** | Each philosopher = thread | Each philosopher = process |
| **Synchronization** | One mutex per fork | Semaphores for available forks |
| **Directory** | `philo/` | `philo_bonus/` |

</div>

## 🛠️ Compilation

Both parts include a Makefile with the following rules:

```bash
make        # Compile the program
make all    # Same as make
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Clean and recompile
make bonus  # Compile bonus part (if applicable)
```

**Compilation flags**: `-Wall -Wextra -Werror`

## 📁 Project Structure

```
philosophers/
├── philo/
│   ├── Makefile
│   ├── *.h
│   └── *.c
├── philo_bonus/
│   ├── Makefile
│   ├── *.h
│   └── *.c
└── README.md
```

## 🔧 Allowed Functions

### Mandatory Part
- `memset`, `printf`, `malloc`, `free`, `write`
- `usleep`, `gettimeofday`
- `pthread_create`, `pthread_detach`, `pthread_join`
- `pthread_mutex_init`, `pthread_mutex_destroy`
- `pthread_mutex_lock`, `pthread_mutex_unlock`

### Bonus Part
- All mandatory functions plus:
- `fork`, `kill`, `exit`, `waitpid`
- `sem_open`, `sem_close`, `sem_post`, `sem_wait`, `sem_unlink`

## ⚠️ Important Rules

- **No global variables allowed**
- **No data races**
- **Proper memory management** (no leaks)
- **No unexpected crashes** (segfaults, bus errors, etc.)
- **Death detection within 10ms**
- Bonus part only evaluated if mandatory part is **PERFECT**

## 🧪 Testing

Consider testing with various scenarios:
- Single philosopher (edge case)
- Even vs odd number of philosophers
- Different timing parameters
- Stress testing with many philosophers
- Edge cases (very short/long times)

## 🎓 Key Concepts Learned

- **Threading**: Creating and managing multiple threads
- **Synchronization**: Using mutexes and semaphores
- **Deadlock Prevention**: Avoiding circular wait conditions
- **Race Conditions**: Protecting shared resources
- **Process Management**: Working with processes and inter-process communication
- **Resource Management**: Proper allocation and deallocation

## 📚 Resources

- [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [Mutex vs Semaphore](https://stackoverflow.com/questions/62814/difference-between-binary-semaphore-and-mutex)

---

<div align="center">

**Version**: 12.0 | **School**: 42 | **Difficulty**: ⭐⭐⭐⭐☆

<img src="https://img.shields.io/badge/Grade-125%2F100-brightgreen?style=for-the-badge" alt="Grade">

*Remember: The goal isn't just to make it work, but to understand the underlying concepts of concurrent programming and resource synchronization.*

---

<p>
  <strong>Made with ❤️ by $ubZ3r0</strong><br>
  <em>42 School Student | Software Developer</em>
</p>

</div>
