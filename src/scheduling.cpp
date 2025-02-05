#include "scheduling.h"
#include "utils.h"
#include <algorithm>
#include <iostream>

using namespace std;

// Function to calculate the waiting times for each process Fcfs scheduling
void fcfs(Process* head, const string& outputFileName) {
    int totalWaitingTime = 0;
    int previousCompletion = 0;
    int processCount = 0;
    Process* current = head;

    while (current != nullptr) {
        processCount++;
        current = current->next;
    }

    current = head;
    while (current != nullptr) {
        int processStart = max(current->arrivalTime, previousCompletion);
        current->waitingTime = processStart - current->arrivalTime;
        totalWaitingTime += current->waitingTime;
        previousCompletion = processStart + current->burstTime;
        current = current->next;
    }
// Sort the linked list of processes by their arrival times
    float averageWaitingTime = static_cast<float>(totalWaitingTime) / processCount;
    // Write results to output file
    writeResultsToFile(outputFileName, "1", head, averageWaitingTime);
}

// Function to calculate waiting time for SJF scheduling
void sjfNonPreemptive(Process* head, const string& outputFileName) {
    int totalWaitingTime = 0;
    int currentTime = 0;
    int processCount = 0;
    Process* current = head;

    while (current != nullptr) {
        processCount++;
        current = current->next;
    }

    for (int i = 0; i < processCount; i++) {
        Process* selectedProcess = nullptr;
        Process* temp = head;

        // Find the process with the shortest burst time that has arrived and is not completed
        while (temp != nullptr) {
            if (!temp->completed && temp->arrivalTime <= currentTime) {
                if (selectedProcess == nullptr || temp->burstTime < selectedProcess->burstTime) {
                    selectedProcess = temp;
                }
            }
            temp = temp->next;
        }

        if (selectedProcess != nullptr) {
            // Calculate waiting time for the selected process
            selectedProcess->waitingTime = currentTime - selectedProcess->arrivalTime;
            totalWaitingTime += selectedProcess->waitingTime;

            // Update current time to reflect process completion
            currentTime += selectedProcess->burstTime;
            selectedProcess->completed = true;
        } else {
            currentTime++;
        }
    }

    float averageWaitingTime = static_cast<float>(totalWaitingTime) / processCount;

    // Write results to output file
    writeResultsToFile(outputFileName, "2", head, averageWaitingTime);
}

// Shortest Job First (Preemptive)
void sjfPreemptive(Process* head, const string& outputFileName) {
    int totalWaitingTime = 0;
    int currentTime = 0;
    int processCount = 0;
    Process* current = head;

    // Count the number of processes and initialize remaining time
    while (current != nullptr) {
        processCount++;
        current->remainingTime = current->burstTime; 
        current->completed = false;             
        current = current->next;
    }

    Process* selectedProcess = nullptr;

    while (true) {
        // Find the process with the shortest remaining time that has arrived
        Process* temp = head;
        selectedProcess = nullptr;

        while (temp != nullptr) {
            if (!temp->completed && temp->arrivalTime <= currentTime) {
                if (selectedProcess == nullptr || temp->remainingTime < selectedProcess->remainingTime) {
                    selectedProcess = temp;
                }
            }
            temp = temp->next;
        }

        if (selectedProcess == nullptr) {
            currentTime++;
            continue;
        }

        selectedProcess->remainingTime--;
        currentTime++;

        if (selectedProcess->remainingTime == 0) {
            selectedProcess->completed = true;
            int completionTime = currentTime;
            selectedProcess->waitingTime = completionTime - selectedProcess->arrivalTime - selectedProcess->burstTime;
            totalWaitingTime += selectedProcess->waitingTime;
        }

// Check if all processes are completed
        bool allCompleted = true;
        temp = head;
        while (temp != nullptr) {
            if (!temp->completed) {
                allCompleted = false;
                break;
            }
            temp = temp->next;
        }

        if (allCompleted) break;
    }

    float averageWaitingTime = static_cast<float>(totalWaitingTime) / processCount;

    // Write results to output file
    writeResultsToFile(outputFileName, "3", head, averageWaitingTime);
}

// priority Scheduling Non-Preemptive
void priorityNonPreemptive(Process* head, const string& outputFileName) {
    int totalWaitingTime = 0; 
    int currentTime = 0; 
    int processCount = 0; 
    Process* current = head;

    while (current != nullptr) {
        processCount++;
        current = current->next;
    }

    for (int i = 0; i < processCount; i++) {
        Process* selectedProcess = nullptr;
        Process* temp = head;

        while (temp != nullptr) {
            if (!temp->completed && temp->arrivalTime <= currentTime) {
                if (selectedProcess == nullptr || 
                    temp->priority < selectedProcess->priority || 
                    (temp->priority == selectedProcess->priority && temp->arrivalTime < selectedProcess->arrivalTime)) {
                    selectedProcess = temp;
                }
            }
            temp = temp->next;
        }

        if (selectedProcess != nullptr) {
            selectedProcess->waitingTime = max(0, currentTime - selectedProcess->arrivalTime);
            totalWaitingTime += selectedProcess->waitingTime;

            currentTime = max(currentTime, selectedProcess->arrivalTime) + selectedProcess->burstTime;

            selectedProcess->completed = true;
        } else {
            currentTime++;
        }
    }

    float averageWaitingTime = static_cast<float>(totalWaitingTime) / processCount;
   // Write results to output file
    writeResultsToFile(outputFileName, "4", head, averageWaitingTime);
}

// priority Scheduling Preemptive
void priorityPreemptive(Process* head, const string& outputFileName) {
    int totalWaitingTime = 0;
    int currentTime = 0;
    int processCount = 0;
    Process* current = head;

    while (current != nullptr) {
        processCount++;
        current->remainingTime = current->burstTime;
        current->completed = false;
        current = current->next;
    }

    while (true) {
        Process* selectedProcess = nullptr;
        Process* temp = head;
 // Find the highest priority process that has arrived and is not completed
        while (temp != nullptr) {
            if (!temp->completed && temp->arrivalTime <= currentTime) {
                if (selectedProcess == nullptr || 
                    temp->priority < selectedProcess->priority || 
                    (temp->priority == selectedProcess->priority && temp->remainingTime < selectedProcess->remainingTime)) {
                    selectedProcess = temp;
                }
            }
            temp = temp->next;
        }
// No process is ready to execute, so increment the current time
        if (selectedProcess == nullptr) {
            currentTime++;
            continue;
        }

        selectedProcess->remainingTime--;
        currentTime++;

        if (selectedProcess->remainingTime == 0) {
            selectedProcess->completed = true;
            int completionTime = currentTime;
            selectedProcess->waitingTime = completionTime - selectedProcess->arrivalTime - selectedProcess->burstTime;
            totalWaitingTime += selectedProcess->waitingTime;
        }
// Check if all processes are completed
        bool allCompleted = true;
        temp = head;
        while (temp != nullptr) {
            if (!temp->completed) {
                allCompleted = false;
                break;
            }
            temp = temp->next;
        }

        if (allCompleted) break;
    }

    float averageWaitingTime = static_cast<float>(totalWaitingTime) / processCount;
// Write results to output file
    writeResultsToFile(outputFileName, "5", head, averageWaitingTime);
}

// Round-Robin scheduling
void roundRobin(Process* head, const string& outputFileName, int timeQuantum) {
    int totalWaitingTime = 0;
    int currentTime = 0;
    int processCount = 0;
    Process* current = head;

    // Count processes and initialize remaining time
    while (current != nullptr) {
        processCount++;
        current->remainingTime = current->burstTime;
        current->completed = false;
        current = current->next;
    }

    // Round-Robin execution
    bool allCompleted = false;
    while (!allCompleted) {
        allCompleted = true;
        current = head;

        while (current != nullptr) {
            if (current->remainingTime > 0) {
                allCompleted = false;

                // Execute the process for the time quantum or the remaining time
                int executionTime = min(timeQuantum, current->remainingTime);
                currentTime += executionTime;
                current->remainingTime -= executionTime;

                // If the process is completed
                if (current->remainingTime == 0) {
                    current->completed = true;
                    int completionTime = currentTime;
                    current->waitingTime = completionTime - current->arrivalTime - current->burstTime;
                    totalWaitingTime += current->waitingTime;
                }
            }
            current = current->next;
        }
    }

    float averageWaitingTime = static_cast<float>(totalWaitingTime) / processCount;

    // Write results to the output file
    writeResultsToFile(outputFileName, "6", head, averageWaitingTime);
}
