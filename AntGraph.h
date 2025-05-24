#ifndef ANT_GRAPH_H
#define ANT_GRAPH_H

#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>
#include <cmath>

#include <vector>
#include <string>
#include <map>

class AntGraph {
private:
    int f;  // Number of ants
    std::vector<std::string> states;
    std::map<std::string, std::vector<std::string>> transitions;
    
public:
    // Constructor that takes data directly
    AntGraph(int numAnts, 
             const std::vector<std::string>& states,
             const std::vector<std::pair<std::string, std::string>>& edges);
             
    // For backward compatibility
    AntGraph(const std::string& filename);
    
    // Get the value of f
    int getF() const { return f; }
    
    // Get all states
    const std::vector<std::string>& getStates() const { return states; }
    
    // Get transitions for a specific state
    const std::vector<std::string>& getTransitions(const std::string& state) const {
        static const std::vector<std::string> empty;
        auto it = transitions.find(state);
        return (it != transitions.end()) ? it->second : empty;
    }
    
    // Print the graph (for debugging)
    void print() const;
    
    // Find the shortest path using A* algorithm
    std::vector<std::string> findShortestPath(const std::string& start, const std::string& goal) const;
    
    // Get the start node (Sv)
    std::string getStartNode() const {
        for (const auto& state : states) {
            if (state == "Sv") return state;
        }
        return "";
    }
    
    // Get the destination node (Sd)
    std::string getDestinationNode() const {
        for (const auto& state : states) {
            if (state == "Sd") return state;
        }
        return "";
    }
    
    // Get the number of ants
    int getNumberOfAnts() const { return f; }
};

#endif // ANT_GRAPH_H
