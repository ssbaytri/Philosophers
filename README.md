# Philosophers

<!-- Add your header image here -->
<img src="https://drive.google.com/uc?id=1YW80HjDtAuGa4OgQHYgm1B49gpDmMjYK" alt="Philosophers" width="100%">

> *"I never thought philosophy would be so deadly"*

## 📖 Overview

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

### Mandatory Part (Threads & Mutexes)
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Bonus Part (Processes & Semaphores)
```bash
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters
- **number_of_philosophers**: Number of philosophers and forks
- **time_to_die** (ms): Maximum time between meals before death
- **time_to_eat** (ms): Time spent eating (holding two forks)
- **time_to_sleep** (ms): Time spent sleeping
- **number_of_times_each_philosopher_must_eat** (optional): Simulation stops when all philosophers have eaten this many times

### Example
```bash
./philo 5 800 200 200
./philo 4 410 200 200 5
```

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

### Mandatory Part
- **Technology**: Threads and Mutexes
- **Structure**: Each philosopher = separate thread
- **Synchronization**: One mutex per fork to prevent duplication
- **Directory**: `philo/`

### Bonus Part
- **Technology**: Processes and Semaphores
- **Structure**: Each philosopher = separate process
- **Synchronization**: Semaphores represent available forks
- **Directory**: `philo_bonus/`

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

**Version**: 12.0  
**School**: 42  
**Difficulty**: ⭐⭐⭐⭐☆

*Remember: The goal isn't just to make it work, but to understand the underlying concepts of concurrent programming and resource synchronization.*
