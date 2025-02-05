#include <iostream>
#include <string>
#include "process.h"
#include "scheduling.h"
#include "utils.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <getopt.h>

using namespace std;


int main(int argc, char* argv[]) {
    string inputFileName, outputFileName;
    int t_value = -1;
    int opt;
// Parse command-line arguments using getopt
    while ((opt = getopt(argc, argv, "f:o:t:")) != -1) {
        switch (opt) {
            case 'f':
                inputFileName = optarg;
                break;
            case 'o':
                outputFileName = optarg;
                break;
            case 't':
                try {
                    t_value = stoi(optarg); 
                } catch (invalid_argument& e) {
                    cerr << "Error: Invalid value for -t option. Must be an integer.\n";
                    return 1;
                }
                break;
            default:
                cerr << "Usage: " << argv[0] << " -f inputFile -o outputFile [-t value]\n";
                return 1;
        }
    }

    if (inputFileName.empty() || outputFileName.empty()) {
        cerr << "Error: Input and output files must be specified.\n";
        return 1;
    }
    // Checks if the input file is empty 
    if (isEndOfFile(inputFileName)) {
        handleEmptyInput(outputFileName);
    }

    Process* processList = nullptr;

    if (!readInputFile(inputFileName, processList)) {
        return 1;
    }
    sortProcessesByArrivalTime(processList);
// Create a copy
// Run algorithms
// Free memory used for lists

    Process* fcfsList = copyProcessList(processList);
    fcfs(fcfsList, outputFileName);
    freeMemory(fcfsList);

    Process* sjfList = copyProcessList(processList);
    sjfNonPreemptive(sjfList, outputFileName);
    freeMemory(sjfList);
    
    Process* sjfPreemptiveList = copyProcessList(processList);
    sjfPreemptive(sjfPreemptiveList, outputFileName);
    freeMemory(sjfPreemptiveList);
        
    Process* priorityList = copyProcessList(processList);
    priorityNonPreemptive(priorityList, outputFileName);
    freeMemory(priorityList);
    
    Process* priorityPreemptiveList = copyProcessList(processList);
    priorityPreemptive(priorityPreemptiveList, outputFileName);
    freeMemory(priorityPreemptiveList);
      
// Run Round-Robin algorithm
    if (t_value > 0) {
        Process* rrList = copyProcessList(processList);
        roundRobin(rrList, outputFileName, t_value);
        freeMemory(rrList);
    } else {
        cout << "Skipping Round-Robin as time quantum (t_value) is not set or invalid.\n";
        ofstream outputFile(outputFileName, ios::app);
        if (!outputFile) {
            cerr << "Error: Could not open " << outputFileName << "\n";
            return 1;
        }

        outputFile << "6:0:0.0\n";
        outputFile.close();
    }
   
    return 0;
}
