#ifndef PROCESS_H
#define PROCESS_H

struct Process {
    int burstTime;      
    int arrivalTime; 
    int priority;     
    int waitingTime;  
    bool completed;  
    int remainingTime;
    Process* next;
    
// Constructor to initialize the process
    Process(int bTime, int aTime, int pri, int wTime, int rTime, bool comp, Process* nxt);
};

void addProcess(Process*& head, int burstTime, int arrivalTime, int priority);
Process* copyProcessList(Process* head);
void sortProcessesByArrivalTime(Process*& head);

#endif