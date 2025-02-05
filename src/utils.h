#ifndef UTILS_H
#define UTILS_H

#include "process.h"
#include <string>
using namespace std;

void writeResultsToFile(const string& outputFileName, const string& algorithmID, Process* head, float averageWaitingTime);
void freeMemory(Process* head);
bool readInputFile(const string& inputFileName, Process*& processList);
bool isEndOfFile(const string& inputFileName);
void handleEmptyInput(const string& outputFileName);

#endif