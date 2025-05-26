
#include "ants.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <limits>
#include <functional>

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

    std::sort(all_paths.begin(), all_paths.end(), [&](const std::vector<int>& a, const std::vector<int>& b) {
        return a.size() < b.size();
    });

    if (all_paths.empty()) {
        std::cout << "Aucun chemin trouvé.\n";
        return;
    }

    std::cout << "\nChemins trouvés :\n";
    for (size_t i = 0; i < all_paths.size(); ++i) {
        std::cout << "  Chemin " << i + 1 << " : ";
        for (int room : all_paths[i]) {
            std::cout << room << " ";
        }
        std::cout << "\n";
    }

    std::vector<int> ants_per_room(total_rooms, 0);
    ants_per_room[0] = total_ants;
    int steps = 0;

    while (ants_per_room[end_room] < total_ants) {
        std::cout << "\nÉtape " << steps << " :\n";
        std::vector<int> next_ants = ants_per_room;

        for (const auto& path : all_paths) {
            for (int i = path.size() - 2; i >= 0; --i) {
                int from = path[i];
                int to = path[i + 1];

                int available = next_ants[from];
                int capacity_left = room_capacity[to] - next_ants[to];
                int can_send = std::min(available, capacity_left);

                if (can_send > 0) {
                    next_ants[from] -= can_send;
                    next_ants[to] += can_send;
                    std::cout << "  " << can_send << " fourmi(s) de " << from << " à " << to << "\n";
                }
            }
        }

        ants_per_room = next_ants;
        for (int i = 0; i < total_rooms; ++i) {
            std::cout << "  Salle " << i << " : " << ants_per_room[i] << " fourmi(s)\n";
        }
        steps++;
    }

    std::cout << "\n✅ Simulation terminée en " << steps << " étapes.\n";
}
