#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>

class AntColony {
public:
    AntColony(int numAnts);
    
    // Read colony structure from file
    void loadColony(const std::string& filename);
    
    // Find the minimum number of steps to move all ants to the dormitory
    int findMinimumSteps();
    
    // Print the colony structure
    void printColony() const;
    
    // Print step-by-step ant movements
    void printAntMovements();
    
private:
    struct Room {
        int capacity;  // Maximum number of ants that can be in this room
        int currentAnts;  // Current number of ants in this room
        std::vector<std::string> connections;  // Connected rooms
    };
    
    int numAnts;
    std::unordered_map<std::string, Room> rooms;
    bool dfs(int antsInVestibule, int step, int& minSteps);
    // --- New for path finding and simulation ---
    void findAllPathsDFS(const std::string& curr, const std::string& end, std::vector<std::string>& path, std::vector<std::vector<std::string>>& allPaths, std::unordered_map<std::string, bool>& visited);
    int simulateAnts(const std::vector<std::vector<std::string>>& paths);
};
