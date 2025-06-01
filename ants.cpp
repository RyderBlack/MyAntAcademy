#include "ants.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <limits>
#include <functional>
#include <thread>
#include <chrono>

Anthill::Anthill(int total_rooms, int total_ants) : total_rooms(total_rooms), total_ants(total_ants) {
    graph.resize(total_rooms);
    ants.resize(total_rooms, 0);
    room_capacity.resize(total_rooms, 0);
}

void Anthill::add_tunnels(int a, int b) {
    graph[a].push_back(b);
    graph[b].push_back(a);
}

void Anthill::set_room_capacity(int room, int c) {
    room_capacity[room] = c;
}

bool Anthill::is_full(int ants, int c) {
    return ants >= c;
}

bool Anthill::has_tunnel(int a, int b) {
    return std::find(graph[a].begin(), graph[a].end(), b) != graph[a].end();
}

void Anthill::simulate_bfs() {
    std::vector<int> distance(total_rooms, -1);
    std::queue<int> q;
    int end_room = total_rooms - 1;
    int start_room = 0;
    distance[end_room] = 0;
    q.push(end_room);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : graph[current]) {
            if (distance[neighbor] == -1) {
                distance[neighbor] = distance[current] + 1;
                q.push(neighbor);
            }
        }
    }

    std::vector<std::vector<int>> all_paths;
    all_paths.reserve(1000);
    std::vector<int> path;
    std::function<void(int)> dfs = [&](int current) {
        path.push_back(current);
        if (current == end_room) {
            all_paths.push_back(path);
        } else {
            for (int neighbor : graph[current]) {
                if (std::find(path.begin(), path.end(), neighbor) == path.end()) {
                    dfs(neighbor);
                }
            }
        }
        path.pop_back();
    };
    dfs(start_room);

    // Priorité sur le nombre de noeud, puis la capacité des noeuds
    std::sort(all_paths.begin(), all_paths.end(), [&](const std::vector<int>& a, const std::vector<int>& b) {
        int sum_a = 0, sum_b = 0;
        for (int room : a) sum_a += room_capacity[room];
        for (int room : b) sum_b += room_capacity[room];

        if (a.size() != b.size()) return a.size() < b.size();
        return sum_a > sum_b; 
    });

    // L'inverse, priorité sur la capacité, puis sur le nombre de noeuds
    //std::sort(all_paths.begin(), all_paths.end(), [&](const std::vector<int>& a, const std::vector<int>& b) {
        //int sum_a = 0, sum_b = 0;
        //for (int room : a) sum_a += room_capacity[room];
        //for (int room : b) sum_b += room_capacity[room];

        //if (sum_a != sum_b) return sum_a > sum_b;          
        //return a.size() < b.size();                        
    //});

    // Print simulation header
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "  🐜 ANT SIMULATION - STARTING" << "\n";
    std::cout << "  Rooms: " << total_rooms << " | Ants: " << total_ants << "\n";
    std::cout << std::string(60, '=') << "\n\n";

    if (all_paths.empty()) {
        std::cout << "❌ No paths found from start to dormitory!\n";
        return;
    }

    // Print all found paths with better formatting
    std::cout << "🔍 Found " << all_paths.size() << " possible path(s) from Start (Room 0) "
              << "to Dormitory (Room " << end_room << "):\n\n";
    for (size_t i = 0; i < all_paths.size(); ++i) {
        std::cout << "  🛣️  Path #" << i + 1 << " (" << all_paths[i].size() - 1 
                  << " steps): ";
        for (size_t j = 0; j < all_paths[i].size(); ++j) {
            std::cout << all_paths[i][j];
            if (j < all_paths[i].size() - 1) {
                std::cout << " → ";
            }
        }
        std::cout << "\n";
    }

    std::vector<int> ants_per_room(total_rooms, 0);
    ants_per_room[0] = total_ants;
    int steps = 0;

    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "  🚀 SIMULATION STARTING - MOVING ANTS TO DORMITORY" << "\n";
    std::cout << std::string(60, '=') << "\n\n";

    while (ants_per_room[end_room] < total_ants) {
        std::cout << "\n⏱️  STEP " << steps << "\n";
        std::cout << std::string(30, '-') << "\n";
        
        std::vector<int> next_ants = ants_per_room;
        bool movement_occurred = false;

        // For each path, try to move ants along it
        for (const auto& path : all_paths) {
            for (int i = path.size() - 2; i >= 0; --i) {
                int from = path[i];
                int to = path[i + 1];

                int available = next_ants[from];
                int capacity_left = room_capacity[to] - next_ants[to];
                int can_send = std::min(available, capacity_left);

                if (can_send > 0) {
                    movement_occurred = true;
                    next_ants[from] -= can_send;
                    next_ants[to] += can_send;
                    std::cout << "  🐜 " << can_send << " ant(s) moved from Room " 
                              << from << " to Room " << to << "\n";
                }
            }
        }

        // Update ant counts
        ants_per_room = next_ants;

        // Print current room status
        std::cout << "\n  ROOM STATUS (" << ants_per_room[end_room] << "/" << total_ants 
                  << " ants in dormitory):\n";
        for (int i = 0; i < total_rooms; ++i) {
            std::string room_type = (i == 0) ? "START" : 
                                   (i == end_room) ? "DORMITORY" : "ROOM";
            std::cout << "  • " << room_type << " " << i << ": " 
                      << ants_per_room[i] << "/" << room_capacity[i] << " ants";
            if (i == end_room && ants_per_room[i] > 0) {
                std::cout << " 🏠";
            }
            std::cout << "\n";
        }

        if (!movement_occurred && ants_per_room[end_room] < total_ants) {
            std::cout << "\n⚠️  No movement possible - ants are stuck! Check room capacities.\n";
            break;
        }

        steps++;
        
        // Small delay for better visualization (500ms)
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "  🎉 SIMULATION COMPLETE! 🎉" << "\n";
    std::cout << "  All " << total_ants << " ants reached the dormitory" << "\n";
    std::cout << "  Total steps: " << steps << "\n";
    std::cout << std::string(60, '=') << "\n\n";
} 