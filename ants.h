#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Anthill{
    int n;
    int total_capacity;
    std::vector<std::vector<int>> graph;
    std::vector<int> ants;
    std::vector<int> room_capacity; 

    public:
        Anthill(int rooms, int capacity);
        void add_tunnels(int a, int b);
        void set_room_capacity(int room, int capacity);

};