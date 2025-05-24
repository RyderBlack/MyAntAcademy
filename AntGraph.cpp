#include "AntGraph.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <iostream>
#include <stdexcept>

// New constructor that takes data directly
AntGraph::AntGraph(int numAnts, 
                   const std::vector<std::string>& states,
                   const std::vector<std::pair<std::string, std::string>>& edges)
    : f(numAnts), states(states) {
    
    // Initialize all states
    for (const auto& state : states) {
        transitions[state] = {};
    }
    
    // Add all edges
    for (const auto& edge : edges) {
        // Check if source state exists
        if (transitions.find(edge.first) == transitions.end()) {
            throw std::runtime_error("Invalid edge source state: " + edge.first);
        }
        // Check if target state exists
        if (std::find(states.begin(), states.end(), edge.second) == states.end()) {
            throw std::runtime_error("Invalid edge target state: " + edge.second);
        }
        
        transitions[edge.first].push_back(edge.second);
    }
}

// Original constructor that reads from file
AntGraph::AntGraph(const std::string& filename) : f(0) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    
    std::string line;
    while (std::getline(file, line)) {
        // Remove any carriage return characters (for Windows line endings)
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        
        if (line.empty()) continue;
        
        // Parse f=5 line
        if (line[0] == 'f' && line.find('=') != std::string::npos) {
            f = std::stoi(line.substr(line.find('=') + 1));
            continue;
        }
        
        // Parse state transitions (Sx - Sy)
        if (line.find(" - ") != std::string::npos) {
            std::istringstream iss(line);
            std::string from, arrow, to;
            if (iss >> from >> arrow >> to) {
                transitions[from].push_back(to);
                // Add states to our states list if not already present
                if (std::find(states.begin(), states.end(), from) == states.end()) {
                    states.push_back(from);
                }
                if (std::find(states.begin(), states.end(), to) == states.end()) {
                    states.push_back(to);
                }
            }
        } 
        // Parse single state (S1, S2, etc.)
        else if (!line.empty()) {
            if (std::find(states.begin(), states.end(), line) == states.end()) {
                states.push_back(line);
            }
        }
    }
}

// Heuristic function for A* - simple implementation (can be improved)
// For this problem, since we don't have coordinates, we'll use a simple heuristic
int heuristic(const std::string& a, const std::string& b) {
    // If the states are the same, return 0
    if (a == b) return 0;
    
    // If one is Sv and the other is Sd, return a higher value
    if ((a == "Sv" && b == "Sd") || (a == "Sd" && b == "Sv")) {
        return 10;
    }
    
    // Default heuristic: return 1 for any transition
    return 1;
}

std::vector<std::string> AntGraph::findShortestPath(const std::string& start, const std::string& goal) const {
    // Priority queue for open set: stores pairs of (f_score, node)
    using pii = std::pair<int, std::string>;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> openSet;
    
    // Maps to store g_scores and f_scores
    std::unordered_map<std::string, int> g_score;
    std::unordered_map<std::string, int> f_score;
    
    // To keep track of the path
    std::unordered_map<std::string, std::string> came_from;
    
    // Initialize all nodes with infinity
    for (const auto& state : states) {
        g_score[state] = std::numeric_limits<int>::max();
        f_score[state] = std::numeric_limits<int>::max();
    }
    
    // Start with the start node
    g_score[start] = 0;
    f_score[start] = heuristic(start, goal);
    openSet.push({f_score[start], start});
    
    // For node exploration
    std::unordered_set<std::string> closedSet;
    
    while (!openSet.empty()) {
        // Get the node with the lowest f_score
        std::string current = openSet.top().second;
        
        // If we've reached the goal, reconstruct the path
        if (current == goal) {
            std::vector<std::string> path;
            while (current != start) {
                path.push_back(current);
                current = came_from[current];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }
        
        openSet.pop();
        
        // If we've already processed this node, skip it
        if (closedSet.find(current) != closedSet.end()) {
            continue;
        }
        
        closedSet.insert(current);
        
        // Check all neighbors
        for (const auto& neighbor : getTransitions(current)) {
            // Tentative g_score is the distance from start to the neighbor through current
            int tentative_g_score = g_score[current] + 1; // Each step has a cost of 1
            
            if (tentative_g_score < g_score[neighbor]) {
                // This path to neighbor is better than any previous one
                came_from[neighbor] = current;
                g_score[neighbor] = tentative_g_score;
                f_score[neighbor] = g_score[neighbor] + heuristic(neighbor, goal);
                
                // Add to open set if not already there
                openSet.push({f_score[neighbor], neighbor});
            }
        }
    }
    
    // No path found
    return {};
}

void AntGraph::print() const {
    std::cout << "Graph with f = " << f << " (number of ants)" << std::endl;
    std::cout << "States: ";
    for (const auto& state : states) {
        std::cout << state << " ";
    }
    std::cout << "\nTransitions:\n";
    
    for (const auto& [from, toList] : transitions) {
        std::cout << "  " << from << " -> ";
        for (const auto& to : toList) {
            std::cout << to << " ";
        }
        std::cout << std::endl;
    }
    
    // Find and print the shortest path if start and end nodes exist
    std::string start = getStartNode();
    std::string goal = getDestinationNode();
    
    if (!start.empty() && !goal.empty()) {
        std::vector<std::string> path = findShortestPath(start, goal);
        if (!path.empty()) {
            std::cout << "\nShortest path from " << start << " to " << goal << ": ";
            for (size_t i = 0; i < path.size(); ++i) {
                if (i > 0) std::cout << " -> ";
                std::cout << path[i];
            }
            std::cout << "\n";
        } else {
            std::cout << "\nNo path found from " << start << " to " << goal << "\n";
        }
    } else {
        if (start.empty()) std::cout << "\nStart node (Sv) not found!\n";
        if (goal.empty()) std::cout << "Destination node (Sd) not found!\n";
    }
}
