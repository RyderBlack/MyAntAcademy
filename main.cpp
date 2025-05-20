#include "AntColony.h"
#include <iostream>

int main() {
    std::string filename;
    std::cout << "Enter colony file name (e.g., fourmiliere_un.txt): ";
    std::cin >> filename;
    AntColony colony(1); // dummy value, will be overwritten by file
    colony.loadColony(filename);
    std::cout << "\nColony Structure:\n";
    colony.printColony();
    std::cout << "\nSimulating ant movements...\n";
    colony.printAntMovements();
    int minSteps = colony.findMinimumSteps();
    if (minSteps != INT_MAX && minSteps != -1) {
        std::cout << "\nMinimum steps required: " << minSteps << std::endl;
    } else {
        std::cout << "\nNo solution found!" << std::endl;
    }
    std::cout << "\nSimulation complete." << std::endl;
    return 0;
}
