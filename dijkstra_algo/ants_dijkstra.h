#ifndef ANTS_DIJKSTRA_H
#define ANTS_DIJKSTRA_H

#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

class AnthillDijkstra {
    struct Node {
        int room;
        int distance;
        std::vector<int> path;

        bool operator>(const Node& other) const {
            return distance > other.distance;
        }
    };

    int total_rooms;
    int total_ants;
    std::vector<std::vector<int>> graph;
    std::vector<int> room_capacity;

    int calculate_weight(int from, int to);

public:
    AnthillDijkstra(int total_rooms, int total_ants);
    void add_tunnels(int a, int b);
    void set_room_capacity(int room, int capacity);
    bool is_full(int ants, int capacity);
    bool has_tunnel(int a, int b);
    void simulate_dijkstra();
};

#endif