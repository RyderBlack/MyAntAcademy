#ifndef ANTS_ASTAR_H
#define ANTS_ASTAR_H

#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

class AnthillAStar {
    struct Node {
        int room;
        int g_score;  // Cost from start to current node
        int f_score;  // g_score + heuristic
        std::vector<int> path;  // Path from start to this node

        bool operator>(const Node& other) const {
            return f_score > other.f_score;
        }
    };

    int total_rooms;
    int total_ants;
    std::vector<std::vector<int>> graph;
    std::vector<int> room_capacity;

    // Enhanced heuristic function that considers both distance and room capacities
    int heuristic(int from, int to, const std::vector<int>& path = {}, int current_ants = 0) {
        // Base case: if we're at the target, no cost
        if (from == to) return 0;
        
        // Calculate base distance (minimum possible steps)
        int base_distance = std::abs(to - from);
        
        // If we have the path so far, consider the capacities of rooms
        if (!path.empty()) {
            // Find the minimum capacity in the remaining path
            int min_capacity = room_capacity[to];  // Start with target room capacity
            
            // Consider the capacity of rooms in the current path
            for (int room : path) {
                if (room != from) {  // Don't consider current room
                    min_capacity = std::min(min_capacity, room_capacity[room]);
                }
            }
            
            // If we have a bottleneck, increase the cost
            // This makes paths with higher capacity rooms more attractive
            if (min_capacity < total_ants) {
                // The more severe the bottleneck, the more we penalize this path
                float capacity_penalty = static_cast<float>(total_ants) / (min_capacity + 1);
                base_distance = static_cast<int>(base_distance * capacity_penalty);
            }
            
            // Consider the number of ants that will need to pass through
            if (current_ants > 0) {
                // If we have many ants, paths with higher capacity are more important
                float ant_ratio = static_cast<float>(current_ants) / min_capacity;
                base_distance = static_cast<int>(base_distance * (1.0f + ant_ratio));
            }
        }
        
        return base_distance;
    }

public:
    AnthillAStar(int total_rooms, int total_ants);
    void add_tunnels(int a, int b);
    void set_room_capacity(int room, int capacity);
    bool is_full(int ants, int capacity);
    bool has_tunnel(int a, int b);
    void simulate_astar();
};

#endif // ANTS_ASTAR_H
