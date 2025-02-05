# CPU Scheduler Simulator

## 📌 Overview
The **CPU Scheduler Simulator** is an advanced implementation of various CPU scheduling algorithms developed in C++ without using vectors and arrays. This project is designed to provide an in-depth understanding of how different scheduling strategies affect process execution. It takes input from a file and outputs the scheduling results, including individual and average waiting times for each algorithm.

This project is particularly useful for:
- Understanding the fundamentals of CPU scheduling in operating systems.
- Comparing the performance of different scheduling algorithms.
- Simulating real-world CPU process management.

The simulator implements **six key CPU scheduling algorithms**:
1. **First-Come, First-Served (FCFS)** – Processes are executed in the order they arrive.
2. **Shortest Job First - Non-Preemptive (SJF Non-Preemptive)** – Selects the process with the shortest burst time, but once started, it cannot be interrupted.
3. **Shortest Job First - Preemptive (SJF Preemptive)** – If a new process arrives with a shorter burst time, the current one is preempted.
4. **Priority Scheduling - Non-Preemptive**  – The process with the highest priority is executed first, without interruption.
5. **Priority Scheduling - Preemptive** – If a higher-priority process arrives, it preempts the currently running one.
6. **Round Robin (RR)** (with configurable time quantum)  – Each process is given a fixed time quantum, after which it is moved to the end of the queue.

## 📂 Project Structure
The project follows a structured modular design, ensuring clarity and maintainability:

```
CPU-Scheduler/
│── src/
│   ├── main.cpp         # Entry point of the program
│   ├── process.h        # Header file for the Process structure
│   ├── process.cpp      # Defines the Process structure and related operations
│   ├── scheduling.h     # Header file for scheduling algorithms
│   ├── scheduling.cpp   # Implements the CPU scheduling algorithms
│   ├── utils.h          # Header file for utility functions
│   ├── utils.cpp        # Contains utility functions such as file handling
│── input.txt            # Sample input file
│── output.txt           # Output file (generated after execution)
│── test.sh              # Script to run test cases
│── Makefile             # Build automation script
│── README.md            # Project documentation
```

## 🔧 Implementation Details

### 🏗 Process Structure
Each process is represented using a linked list node:
```cpp
struct Process {
    int burstTime;
    int arrivalTime;
    int priority;
    int waitingTime;
    int remainingTime;
    bool completed;
    Process* next;
};
```
This ensures efficient memory management without the use of arrays or vectors.

### ⚙️ Key Functions
- **`readInputFile(std::string filename, Process*& head)`**: Reads the input file and creates a linked list of processes.
- **`freeMemory(Process* head)`**: Frees dynamically allocated memory for processes after execution.
- **`sortProcessesByArrivalTime(Process*& head)`**: Sorts the linked list of processes based on arrival time.
- **`fcfs(Process* head, std::string outputFile)`**: Implements First-Come, First-Served scheduling.
- **`sjfNonPreemptive(Process* head, std::string outputFile)`**: Implements Shortest Job First (Non-Preemptive) scheduling.
- **`sjfPreemptive(Process* head, std::string outputFile)`**: Implements Shortest Job First (Preemptive) scheduling.
- **`priorityNonPreemptive(Process* head, std::string outputFile)`**: Implements Priority Scheduling (Non-Preemptive).
- **`priorityPreemptive(Process* head, std::string outputFile)`**: Implements Priority Scheduling (Preemptive).
- **`roundRobin(Process* head, std::string outputFile, int timeQuantum)`**: Implements Round Robin scheduling with a user-defined time quantum.

### 📥 Input Format
The input is read from `input.txt` with the following format:
```
BurstTime:ArrivalTime:Priority
5:0:3
4:1:2
3:1:1
4:2:2
3:3:1
5:4:3
```

### 📤 Output Format
The output is written to `output.txt`, where:
- Each line corresponds to an algorithm and contains:
  ```
  Algorithm_Number:WT1:WT2:WT3:...:AverageWT
  ```
- Example output:
  ```
  1:0:4:8:10:13:15:8.33
  2:0:10:4:13:5:15:7.83
  3:6:10:0:13:1:15:7.50
  4:0:10:4:13:5:15:7.83
  5:14:6:0:9:1:15:7.50
  6:18:11:13:13:14:15:14.00
  ```

## 🚀 How to Run the Project
### 1️⃣ Clone the Repository
```sh
git clone 
cd CPU-Scheduler
```

### 2️⃣ Run the Tests
```sh
make test
```
This will:
- Compile the project
- Run the simulator on a sample input file
- Validate the correctness of the output

### 4️⃣ Run the Simulator Manually
To execute the scheduler manually:
```sh
g++ -o scheduler  src/*.cpp
./scheduler -t <time quantum> -f input.txt -o output.txt
```
For example, to run Round Robin with a time quantum of 2:
```sh
g++ -o scheduler  src/*.cpp
./scheduler -t 2 -f input.txt -o output.txt 
```

## 🎯 Why This Project is Important?
### ✅ Academic & Research Applications
- Provides a **clear and efficient** implementation of CPU scheduling algorithms.
- Helps **students and researchers** understand scheduling strategies.
- Can be extended to **simulate real-world scheduling policies** in OS design.

### 🛠 Industry Relevance
- Reinforces **low-level memory management** using **linked lists** instead of dynamic containers.
- Improves **problem-solving skills** in system programming.
- Teaches low-level memory management using linked lists instead of arrays/vectors, which is essential for system programming.

---
### ✨ Author: Alisa
If you found this project useful or have suggestions, feel free to reach out! 🚀

