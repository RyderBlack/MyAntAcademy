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

    // Heuristic function (Euclidean distance as a simple heuristic)
    int heuristic(int from, int to) {
        // Simple heuristic: prefer nodes closer to the end
        // In a grid, this would be the Manhattan or Euclidean distance
        // Here we'll use absolute difference as a simple heuristic
        return std::abs(to - from);
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
