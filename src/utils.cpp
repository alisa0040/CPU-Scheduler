#include "utils.h"
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

// Function to write results to the output file
void writeResultsToFile(const string& outputFileName, const string& algorithmID, Process* head, float averageWaitingTime) {
    ofstream outputFile(outputFileName, ios::app);
    if (!outputFile) {
        cerr << "Error: Could not open " << outputFileName << "\n";
        return;
    }

    outputFile << algorithmID << ":";
    Process* current = head;
    while (current != nullptr) {
        outputFile << current->waitingTime;
        if (current->next != nullptr) {
            outputFile << ":";
        }
        current = current->next;
    }

    outputFile << ":" << fixed << setprecision(2) << averageWaitingTime << "\n";
    outputFile.close();
}

// Function to free memory allocated for the linked list of processes
void freeMemory(Process* head) {
    Process* current;
    while (head != nullptr) {
        current = head;
        head = head->next;
        delete current;
    }
}

// Function to read process data from the input file
bool readInputFile(const string& inputFileName, Process*& processList) {
    ifstream inputFile(inputFileName);
    if (!inputFile) {
        cerr << "Error: Could not open " << inputFileName << "\n";
        return false;
    }

    int burstTime, arrivalTime, priority;
    char colon1, colon2;

    while (inputFile >> burstTime >> colon1 >> arrivalTime >> colon2 >> priority) {
        if (colon1 != ':' || colon2 != ':') {
            cerr << "Invalid format in " << inputFileName << ". Expected format: burstTime:arrivalTime:.\n";
            return false;
        }
        if (burstTime < 0 || arrivalTime < 0) {
            cerr << "Error: Negative burstTime or arrival time in " << inputFileName << "\n";
            return false;
        }
        addProcess(processList, burstTime, arrivalTime, priority);
    }

    inputFile.close();

    if (processList == nullptr) {
        cerr << "No process information found in " << inputFileName << ".\n";
        return false;
    }

    return true;
}

// Checks if the file is empty 
bool isEndOfFile(const string& inputFileName) {
    ifstream file(inputFileName, ios::binary);
    if (!file) {
        cerr << "Error: Could not open the file.\n";
        return false;
    }
    char ch;
    file.read(&ch, sizeof(ch));

    if (file.gcount() == 0) {
        return true; 
    }
    return false;
}

// Writes default rows for each algorithm with zeros if the input file is empty.
void handleEmptyInput(const string& outputFileName) {
    ofstream outputFile(outputFileName, ios::app); 
    for (int i = 1; i <= 6; i++) {
        outputFile << i << ":0:0.0\n";
    }

    outputFile.close();
}