#include <iostream>
#include "ants_dijkstra.h"

int main() {
    // Anthill 1: Small anthill with 4 rooms and 2 ants
    {
        std::cout << "\n===== ANTHILL 1: SMALL ANTHILL (4 rooms, 2 ants) =====\n";
        AnthillDijkstra anthill(4, 2);
        anthill.set_room_capacity(0, 2);  // Start
        anthill.set_room_capacity(1, 1);
        anthill.set_room_capacity(2, 1);
        anthill.set_room_capacity(3, 2);  // End

        anthill.add_tunnels(0, 1);
        anthill.add_tunnels(0, 2);
        anthill.add_tunnels(1, 3);
        anthill.add_tunnels(2, 3);
        
        anthill.simulate_dijkstra();
    }

    // Anthill 2: Simple path with bottleneck
    {
        std::cout << "\n\n===== ANTHILL 2: BOTTLENECK PATH (4 rooms, 5 ants) =====\n";
        AnthillDijkstra anthill(4, 5);
        anthill.set_room_capacity(0, 5);
        anthill.set_room_capacity(1, 1);
        anthill.set_room_capacity(2, 1);
        anthill.set_room_capacity(3, 5);
        
        anthill.add_tunnels(0, 1);
        anthill.add_tunnels(1, 2);
        anthill.add_tunnels(2, 3);
        
        anthill.simulate_dijkstra();
    }

    // Anthill 3: Alternative paths with different capacities
    {
        std::cout << "\n\n===== ANTHILL 3: MULTIPLE PATHS (4 rooms, 5 ants) =====\n";
        AnthillDijkstra anthill(4, 5);
        anthill.set_room_capacity(0, 5);
        anthill.set_room_capacity(1, 1);
        anthill.set_room_capacity(2, 1);
        anthill.set_room_capacity(3, 5);

        anthill.add_tunnels(0, 1);
        anthill.add_tunnels(1, 2);
        anthill.add_tunnels(2, 3);
        anthill.add_tunnels(0, 3);  // Direct path
        
        anthill.simulate_dijkstra();
    }

    // Anthill 4: More complex anthill with multiple branches
    {
        std::cout << "\n\n===== ANTHILL 4: COMPLEX ANTHILL (6 rooms, 5 ants) =====\n";
        AnthillDijkstra anthill(6, 5);
        anthill.set_room_capacity(0, 5);
        anthill.set_room_capacity(1, 1);
        anthill.set_room_capacity(2, 1);
        anthill.set_room_capacity(3, 1);
        anthill.set_room_capacity(4, 1);
        anthill.set_room_capacity(5, 5);
        
        anthill.add_tunnels(0, 1);
        anthill.add_tunnels(1, 2);
        anthill.add_tunnels(4, 5);
        anthill.add_tunnels(1, 4);
        anthill.add_tunnels(2, 3);
        
        anthill.simulate_dijkstra();
    }

    // Anthill 5: Larger anthill with multiple paths
    {
        std::cout << "\n\n===== ANTHILL 5: LARGE ANTHILL (8 rooms, 10 ants) =====\n";
        AnthillDijkstra anthill(8, 10);
        
        anthill.set_room_capacity(0, 10);  // Start
        anthill.set_room_capacity(1, 2);
        anthill.set_room_capacity(2, 1);
        anthill.set_room_capacity(3, 1);
        anthill.set_room_capacity(4, 2);
        anthill.set_room_capacity(5, 2);
        anthill.set_room_capacity(6, 1);
        anthill.set_room_capacity(7, 10);  // End

        anthill.add_tunnels(3, 4);
        anthill.add_tunnels(0, 1);
        anthill.add_tunnels(1, 2);
        anthill.add_tunnels(2, 4);
        anthill.add_tunnels(4, 5);
        anthill.add_tunnels(5, 7);
        anthill.add_tunnels(4, 6);
        anthill.add_tunnels(6, 7);
        anthill.add_tunnels(1, 3);
        
        anthill.simulate_dijkstra();
    }

    // Anthill 6: King's anthill (very large)
    {
        std::cout << "\n\n===== ANTHILL 6: KING'S ANTHILL (16 rooms, 50 ants) =====\n";
        AnthillDijkstra anthill(16, 50);
        
        // Set capacities for all rooms
        anthill.set_room_capacity(0, 50);  // Start
        anthill.set_room_capacity(1, 8);
        anthill.set_room_capacity(2, 4);
        anthill.set_room_capacity(3, 2);
        anthill.set_room_capacity(4, 4);
        anthill.set_room_capacity(5, 2);
        anthill.set_room_capacity(6, 4);
        anthill.set_room_capacity(7, 2);
        anthill.set_room_capacity(8, 5);
        anthill.set_room_capacity(9, 1);
        anthill.set_room_capacity(10, 1);
        anthill.set_room_capacity(11, 1);
        anthill.set_room_capacity(12, 1);
        anthill.set_room_capacity(13, 4);
        anthill.set_room_capacity(14, 12);
        anthill.set_room_capacity(15, 50);  // End

        // Add all tunnels
        anthill.add_tunnels(0, 1);
        anthill.add_tunnels(1, 2);
        anthill.add_tunnels(2, 3);
        anthill.add_tunnels(3, 4);
        anthill.add_tunnels(4, 15);
        anthill.add_tunnels(1, 6);
        anthill.add_tunnels(6, 8);
        anthill.add_tunnels(8, 12);
        anthill.add_tunnels(12, 13);
        anthill.add_tunnels(13, 15);
        anthill.add_tunnels(2, 5);
        anthill.add_tunnels(5, 4);
        anthill.add_tunnels(6, 7);
        anthill.add_tunnels(7, 10);
        anthill.add_tunnels(10, 14);
        anthill.add_tunnels(14, 15);
        anthill.add_tunnels(3, 9);
        anthill.add_tunnels(9, 11);
        anthill.add_tunnels(11, 15);
        
        anthill.simulate_dijkstra();
    }

    return 0;
}