#include <iostream>
#include "ants_astar.h"

int main() {
    // Test case 1: Simple 4-room anthill
    AnthillAStar ant_0(4, 2);
    ant_0.set_room_capacity(0, 2);  // Room 0 can hold 2 ants
    ant_0.set_room_capacity(1, 1);  // Room 1 can hold 1 ant
    ant_0.set_room_capacity(2, 1);  // Room 2 can hold 1 ant
    ant_0.set_room_capacity(3, 2);  // Room 3 (dormitory) can hold 2 ants

    // Create tunnels between rooms
    ant_0.add_tunnels(0, 1);  // Tunnel between room 0 and 1
    ant_0.add_tunnels(0, 2);  // Tunnel between room 0 and 2
    ant_0.add_tunnels(1, 3);  // Tunnel between room 1 and 3
    ant_0.add_tunnels(2, 3);  // Tunnel between room 2 and 3

    // More complex test case that demonstrates A* behavior
    AnthillAStar ant_1(6, 10);  // 6 rooms, 10 ants
    
    // Set different capacities for each room
    ant_1.set_room_capacity(0, 10);  // Start room can hold all ants
    ant_1.set_room_capacity(1, 2);   // Bottleneck room with low capacity
    ant_1.set_room_capacity(2, 5);   // Alternative path with higher capacity
    ant_1.set_room_capacity(3, 5);   
    ant_1.set_room_capacity(4, 5);
    ant_1.set_room_capacity(5, 10);  // Dormitory can hold all ants
    
    // Create the graph with multiple possible paths
    ant_1.add_tunnels(0, 1);  // Path 1: 0-1-3-5
    ant_1.add_tunnels(1, 3);
    ant_1.add_tunnels(3, 5);
    
    ant_1.add_tunnels(0, 2);  // Path 2: 0-2-4-5 (potentially better)
    ant_1.add_tunnels(2, 4);
    ant_1.add_tunnels(4, 5);
    
    ant_1.add_tunnels(1, 2);  // Connection between paths
    ant_1.add_tunnels(3, 4);

    // Run the simulation
    std::cout << "===== RUNNING A* SIMULATION =====\n";
    std::cout << "Testing A* with multiple paths and room capacities.\n";
    std::cout << "Expected behavior: A* should find the most efficient path\n";
    std::cout << "considering both distance and room capacities.\n\n";
    
    ant_1.simulate_astar();

    return 0;
}
