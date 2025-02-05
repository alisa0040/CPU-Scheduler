#ifndef SCHEDULING_H
#define SCHEDULING_H

#include "process.h"
#include <string>
using namespace std;

void fcfs(Process* head, const string& outputFileName);
void sjfNonPreemptive(Process* head, const string& outputFileName);
void sjfPreemptive(Process* head, const string& outputFileName);
void priorityNonPreemptive(Process* head, const string& outputFileName);
void priorityPreemptive(Process* head, const string& outputFileName);
void roundRobin(Process* head, const string& outputFileName, int timeQuantum);

#endif