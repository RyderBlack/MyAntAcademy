#include "ants.h"
#include "AntGraph.h"
#include "anthill_data.h"
#include <iostream>
#include <vector>
#include <string>

// Function to process a single anthill
void processAnthill(const AnthillData& anthill) {
    try {
        std::cout << "\n=== Processing Anthill ===\n";
        
        // Create graph from embedded data
        AntGraph graph(anthill.numAnts, anthill.states, anthill.edges);
        
        // Print the graph information
        graph.print();
        
        // Get start and goal nodes
        std::string start = graph.getStartNode();
        std::string goal = graph.getDestinationNode();
        
        if (start.empty() || goal.empty()) {
            std::cerr << "Error: Missing start (Sv) or goal (Sd) node in the graph.\n";
            return;
        }
        
        std::cout << "Start node: " << start << std::endl;
        std::cout << "Goal node: " << goal << std::endl;
        
        // Find the shortest path using A*
        std::cout << "Finding shortest path..." << std::endl;
        std::vector<std::string> path = graph.findShortestPath(start, goal);
        
        if (!path.empty()) {
            // Print the path
            std::cout << "\n=== Shortest Path ===\n";
            std::cout << "Number of ants: " << graph.getNumberOfAnts() << "\n";
            std::cout << "Path: ";
            for (size_t i = 0; i < path.size(); ++i) {
                if (i > 0) std::cout << " -> ";
                std::cout << path[i];
            }
            std::cout << "\n";
            
            // Calculate the number of steps (excluding the start node)
            int steps = path.size() - 1;
            std::cout << "Number of steps: " << steps << "\n";
            
            // Calculate the number of moves needed for all ants to reach the goal
            // Each ant must wait for the previous one to move to the next room
            int total_moves = graph.getNumberOfAnts() + steps - 1;
            std::cout << "Total moves needed for all " << graph.getNumberOfAnts() 
                      << " ants to reach " << goal << ": " << total_moves << "\n";
            
        } else {
            std::cout << "\nNo path found from " << start << " to " << goal << "\n";
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error processing anthill: " << e.what() << std::endl;
    }
}

int main() {
    // Process all anthills
    std::cout << "=== Ant Colony Path Finding ===\n";
    
    // Process first anthill
    std::cout << "\n--- First Anthill ---";
    processAnthill(Anthills::fourmiliere_un);
    
    // Process second anthill
    std::cout << "\n--- Second Anthill ---";
    processAnthill(Anthills::fourmiliere_deux);
    
    // Process third anthill
    std::cout << "\n--- Third Anthill ---";
    processAnthill(Anthills::fourmiliere_trois);
    
    std::cout << "\n=== All anthills processed ===\n";
    
    // Your existing code
    Anthill Small_hill(4, 3); 
    Small_hill.set_room_capacity(0, 3);
    Small_hill.set_room_capacity(1, 1);
    Small_hill.set_room_capacity(2, 1);
    Small_hill.set_room_capacity(3, 3);

    Small_hill.add_tunnels(0,1);
    Small_hill.add_tunnels(0,2);
    Small_hill.add_tunnels(1,4);
    Small_hill.add_tunnels(2,4);
    


    Anthill Big_hill(16, 50);
    Big_hill.set_room_capacity(0, 50);
    Big_hill.set_room_capacity(1, 1);
    Big_hill.set_room_capacity(2, 1);
    Big_hill.set_room_capacity(3, 1);
    Big_hill.set_room_capacity(4, 1);
    Big_hill.set_room_capacity(5, 1);
    Big_hill.set_room_capacity(6, 1);
    Big_hill.set_room_capacity(7, 1);
    Big_hill.set_room_capacity(8, 1);
    Big_hill.set_room_capacity(9, 1);
    Big_hill.set_room_capacity(10, 1);
    Big_hill.set_room_capacity(11, 1);
    Big_hill.set_room_capacity(12, 1);
    Big_hill.set_room_capacity(13, 1);
    Big_hill.set_room_capacity(14, 1);
    Big_hill.set_room_capacity(15, 50);

    Big_hill.add_tunnels(1,2);
    Big_hill.add_tunnels(2,3);
    Big_hill.add_tunnels(3,4);
    Big_hill.add_tunnels(4,15);
    Big_hill.add_tunnels(0,1);
    Big_hill.add_tunnels(2,5);
    Big_hill.add_tunnels(5,4);
    Big_hill.add_tunnels(13,15);
    Big_hill.add_tunnels(8,12);
    Big_hill.add_tunnels(12,13);
    Big_hill.add_tunnels(6,7);
    Big_hill.add_tunnels(7,9);
    Big_hill.add_tunnels(9,14);
    Big_hill.add_tunnels(14,15);
    Big_hill.add_tunnels(7,10);
    Big_hill.add_tunnels(10,14);
    Big_hill.add_tunnels(1,6);
    Big_hill.add_tunnels(6,8);
    Big_hill.add_tunnels(8,11);
    Big_hill.add_tunnels(11,13);
}

