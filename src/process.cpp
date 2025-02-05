#include "process.h"
#include <algorithm>

Process::Process(int bTime, int aTime, int pri, int wTime, int rTime, bool comp, Process* nxt)
    : burstTime(bTime), arrivalTime(aTime), priority(pri),
      waitingTime(wTime), completed(comp),remainingTime(rTime),  next(nxt) {}

void addProcess(Process*& head, int burstTime, int arrivalTime, int priority) {
    Process* newProcess = new Process(burstTime, arrivalTime, priority, 0, burstTime, false, nullptr);
    if (!head) {
        head = newProcess;
    } else {
        Process* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newProcess;
    }
}

Process* copyProcessList(Process* head) {
    if (!head) return nullptr;

    Process* copyHead = nullptr;
    Process* current = head;
    Process* copyCurrent = nullptr;

    while (current) {
        Process* newProcess = new Process(
            current->burstTime, current->arrivalTime, current->priority,
            0, current->burstTime, false, nullptr
        );

        if (!copyHead) {
            copyHead = newProcess;
            copyCurrent = copyHead;
        } else {
            copyCurrent->next = newProcess;
            copyCurrent = newProcess;
        }

        current = current->next;
    }

    return copyHead;
}

void sortProcessesByArrivalTime(Process*& head) {
    if (head == nullptr || head->next == nullptr) return;

    Process* sorted = nullptr;
    Process* current = head;
    while (current != nullptr) {
        Process* next = current->next;
        
        if (sorted == nullptr || sorted->arrivalTime > current->arrivalTime) {
            current->next = sorted;
            sorted = current;
        } else {
            Process* temp = sorted;
            while (temp->next != nullptr && temp->next->arrivalTime <= current->arrivalTime) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    head = sorted;
}