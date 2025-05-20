#include "ants.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

Anthill::Anthill(int rooms, int capacity) {
    total_capacity = capacity;
    n = rooms;
    graph.resize(n);
    ants.resize(n, 0);
    room_capacity.resize(n,0);
}

void Anthill::add_tunnels(int a, int b) {
    graph[a].push_back(b);
    graph[b].push_back(a);
}

void Anthill::set_room_capacity(int room, int c) {
    room_capacity[room] = c;
}
        
  