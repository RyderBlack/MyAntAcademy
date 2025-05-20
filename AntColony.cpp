#include "AntColony.h"
#include <iostream>
#include <sstream>
#include <queue>

AntColony::AntColony(int numAnts) : numAnts(numAnts) {
    // Initialize vestibule and dormitory
    rooms["Sv"] = {1000, numAnts, {}};  // Vestibule can hold all ants
    rooms["Sd"] = {1000, 0, {}};        // Dormitory can hold all ants
}

void AntColony::loadColony(const std::string& filename) {
    std::string projectDir = "C:/Users/ryrym_i6sf5hg/CLionProjects/MyAntAcademy/anthills/";
    std::ifstream file(projectDir + filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << projectDir + filename << std::endl;
        return;
    }

    std::string line;
    // Parse number of ants
    int fileAnts = 1;
    if (std::getline(file, line)) {
        if (line.rfind("f=", 0) == 0) {
            fileAnts = std::stoi(line.substr(2));
        }
    }
    numAnts = fileAnts;
    // Read room definitions
    std::vector<std::string> roomNames;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        if (line.find('-') != std::string::npos) break; // Stop when we reach connections
        // Parse room capacity if present
        size_t braceL = line.find('{');
        size_t braceR = line.find('}');
        std::string roomName = line;
        int capacity = 1;
        if (braceL != std::string::npos && braceR != std::string::npos && braceL < braceR) {
            roomName = line.substr(0, braceL);
            roomName.erase(roomName.find_last_not_of(" \t") + 1);
            std::string capStr = line.substr(braceL+1, braceR-braceL-1);
            capacity = std::stoi(capStr);
        } else {
            roomName.erase(roomName.find_last_not_of(" \t") + 1);
        }
        rooms[roomName] = {capacity, 0, {}};
        roomNames.push_back(roomName);
    }
    // Add Sv and Sd if not already present
    if (rooms.find("Sv") == rooms.end()) rooms["Sv"] = {1000, 0, {}};
    if (rooms.find("Sd") == rooms.end()) rooms["Sd"] = {1000, 0, {}};
    // Parse connection lines
    do {
        if (line.empty() || line[0] == '#') continue;
        size_t dash = line.find('-');
        if (dash == std::string::npos) continue;
        // Remove whitespace around room names
        std::string left = line.substr(0, dash);
        std::string right = line.substr(dash + 1);
        left.erase(0, left.find_first_not_of(" \t"));
        left.erase(left.find_last_not_of(" \t") + 1);
        right.erase(0, right.find_first_not_of(" \t"));
        right.erase(right.find_last_not_of(" \t") + 1);
        // Add connection in both directions
        rooms[left].connections.push_back(right);
        rooms[right].connections.push_back(left);
    } while (std::getline(file, line));
    file.close();
}

bool AntColony::dfs(int antsInVestibule, int step, int& minSteps) {
    // Base case: all ants are in the dormitory
    if (antsInVestibule == 0 && rooms["Sd"].currentAnts == numAnts) {
        minSteps = std::min(minSteps, step);
        return true;
    }

    // Try to move all possible ants in one step
    bool anyMovement = false;
    
    // First try to move ants from vestibule
    if (antsInVestibule > 0) {
        for (const auto& connectedRoom : rooms["Sv"].connections) {
            if (rooms[connectedRoom].currentAnts < rooms[connectedRoom].capacity) {
                // Move one ant
                rooms[connectedRoom].currentAnts++;
                antsInVestibule--;
                anyMovement = true;
            }
        }
    }

    // Then try to move ants from other rooms
    for (const auto& [roomName, room] : rooms) {
        if (roomName != "Sv" && roomName != "Sd" && room.currentAnts > 0) {
            for (const auto& connectedRoom : room.connections) {
                if (rooms[connectedRoom].currentAnts < rooms[connectedRoom].capacity) {
                    // Move one ant
                    rooms[roomName].currentAnts--;
                    rooms[connectedRoom].currentAnts++;
                    anyMovement = true;
                }
            }
        }
    }

    // If we made any movements, try the next step
    if (anyMovement) {
        dfs(antsInVestibule, step + 1, minSteps);
    }
    
    // Backtrack all movements
    // First restore vestibule ants
    if (antsInVestibule != numAnts) {
        for (const auto& connectedRoom : rooms["Sv"].connections) {
            while (rooms[connectedRoom].currentAnts > 0) {
                rooms[connectedRoom].currentAnts--;
                antsInVestibule++;
            }
        }
    }

    // Then restore other rooms
    for (const auto& [roomName, room] : rooms) {
        if (roomName != "Sv" && roomName != "Sd" && room.currentAnts > 0) {
            for (const auto& connectedRoom : room.connections) {
                while (rooms[connectedRoom].currentAnts > 0) {
                    rooms[connectedRoom].currentAnts--;
                    rooms[roomName].currentAnts++;
                }
            }
        }
    }
    
    return false;
}

void AntColony::findAllPathsDFS(const std::string& curr, const std::string& end, std::vector<std::string>& path, std::vector<std::vector<std::string>>& allPaths, std::unordered_map<std::string, bool>& visited) {
    path.push_back(curr);
    visited[curr] = true;
    if (curr == end) {
        allPaths.push_back(path);
    } else {
        for (const auto& next : rooms[curr].connections) {
            if (!visited[next] && next != "Sv") // allow Sd to be revisited but not Sv
                findAllPathsDFS(next, end, path, allPaths, visited);
        }
    }
    path.pop_back();
    visited[curr] = false;
}

int AntColony::simulateAnts(const std::vector<std::vector<std::string>>& paths) {
    if (paths.empty()) return -1;
    int pathCount = paths.size();
    std::vector<int> antOnPath(pathCount, 0); // ant index on each path
    std::vector<int> antStep(pathCount, 0);   // step index for each ant on path
    int antsMoved = 0;
    int steps = 0;
    std::vector<int> pathOccupancy(pathCount, -1); // which ant is at which step on each path
    std::vector<std::vector<int>> roomOccupancy(numAnts + 2, std::vector<int>(pathCount, -1));
    std::vector<int> antPositions(numAnts, 0); // position on path for each ant
    std::vector<int> antPath(numAnts, -1);     // which path for each ant
    int finished = 0;
    // Assign ants to paths in round robin
    for (int i = 0; i < numAnts; ++i) antPath[i] = i % pathCount;
    // Simulate step by step
    std::vector<int> pathPos(pathCount, 0);
    std::vector<int> antAtRoom(numAnts, 0); // position in path
    std::vector<int> antDone(numAnts, 0);
    while (finished < numAnts) {
        steps++;
        std::unordered_map<std::string, int> occupied;
        for (int pi = 0; pi < pathCount; ++pi) {
            occupied[paths[pi][0]] = -1; // Sv can have many
        }
        // Move ants from end to start to avoid collision
        for (int ai = 0; ai < numAnts; ++ai) {
            if (antDone[ai]) continue;
            int p = antPath[ai];
            int pos = antAtRoom[ai];
            if (pos + 1 < (int)paths[p].size()) {
                std::string nextRoom = paths[p][pos + 1];
                if ((nextRoom == "Sd" || occupied.find(nextRoom) == occupied.end()) && (nextRoom == "Sd" || occupied[nextRoom] == -1)) {
                    antAtRoom[ai]++;
                    if (nextRoom != "Sd") occupied[nextRoom] = ai;
                    if (nextRoom == "Sd") { finished++; antDone[ai] = 1; }
                } else {
                    if (pos != 0) occupied[paths[p][pos]] = ai;
                }
            } else {
                if (pos != 0) occupied[paths[p][pos]] = ai;
            }
        }
    }
    return steps;
}

void AntColony::printAntMovements() {
    // Find all simple paths from Sv to Sd
    std::vector<std::vector<std::string>> allPaths;
    std::vector<std::string> path;
    std::unordered_map<std::string, bool> visited;
    findAllPathsDFS("Sv", "Sd", path, allPaths, visited);
    if (allPaths.empty()) {
        std::cout << "No path from Sv to Sd!" << std::endl;
        return;
    }
    int pathCount = allPaths.size();
    int finished = 0;
    int steps = 0;
    int antCount = numAnts;
    std::vector<int> antPath(antCount, 0); // which path for each ant
    for (int i = 0; i < antCount; ++i) antPath[i] = i % pathCount;
    std::vector<int> antAtRoom(antCount, 0); // position in path
    std::vector<int> antDone(antCount, 0);
    std::vector<std::string> antState(antCount, "Sv");
    while (finished < antCount) {
        steps++;
        std::unordered_map<std::string, int> occupied;
        for (int pi = 0; pi < pathCount; ++pi) occupied[allPaths[pi][0]] = -1; // Sv can have many
        std::vector<std::string> moves;
        for (int ai = 0; ai < antCount; ++ai) {
            if (antDone[ai]) continue;
            int p = antPath[ai];
            int pos = antAtRoom[ai];
            if (pos + 1 < (int)allPaths[p].size()) {
                std::string nextRoom = allPaths[p][pos + 1];
                if ((nextRoom == "Sd" || occupied.find(nextRoom) == occupied.end()) && (nextRoom == "Sd" || occupied[nextRoom] == -1)) {
                    moves.push_back("f" + std::to_string(ai + 1) + " - " + allPaths[p][pos] + " - " + nextRoom);
                    antAtRoom[ai]++;
                    antState[ai] = nextRoom;
                    if (nextRoom != "Sd") occupied[nextRoom] = ai;
                    if (nextRoom == "Sd") { finished++; antDone[ai] = 1; }
                } else {
                    if (pos != 0) occupied[allPaths[p][pos]] = ai;
                }
            } else {
                if (pos != 0) occupied[allPaths[p][pos]] = ai;
            }
        }
        if (!moves.empty()) {
            std::cout << "+++ " << steps << " +++" << std::endl;
            for (const auto& m : moves) std::cout << m << std::endl;
        }
    }
}

int AntColony::findMinimumSteps() {
    // Find all simple paths from Sv to Sd
    std::vector<std::vector<std::string>> allPaths;
    std::vector<std::string> path;
    std::unordered_map<std::string, bool> visited;
    findAllPathsDFS("Sv", "Sd", path, allPaths, visited);
    if (allPaths.empty()) return -1;
    return simulateAnts(allPaths);
}

void AntColony::printColony() const {
    for (const auto& [roomName, room] : rooms) {
        std::cout << roomName << " (capacity: " << room.capacity << ", ants: " << room.currentAnts << ") -> ";
        for (const auto& connection : room.connections) {
            std::cout << connection << " ";
        }
        std::cout << std::endl;
    }
}
