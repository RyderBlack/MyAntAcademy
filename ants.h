#ifndef ANTS_H
#define ANTS_H

#include <vector>

class Anthill {
    int total_rooms;
    int total_ants;
    std::vector<std::vector<int>> graph;
    std::vector<int> ants;
    std::vector<int> room_capacity;

public:
    Anthill(int total_rooms, int total_ants);
    void add_tunnels(int a, int b);
    void set_room_capacity(int room, int capacity);
    bool is_full(int ants, int capacity);
    bool has_tunnel(int a, int b);
    void simulate_bfs();
};

#endif