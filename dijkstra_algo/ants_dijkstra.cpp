#include "ants_dijkstra.h"
#include <iomanip>

AnthillDijkstra::AnthillDijkstra(int total_rooms, int total_ants) 
    : total_rooms(total_rooms), total_ants(total_ants) {
    graph.resize(total_rooms);
    room_capacity.resize(total_rooms, 0);
}

void AnthillDijkstra::add_tunnels(int a, int b) {
    graph[a].push_back(b);
    graph[b].push_back(a);
}

void AnthillDijkstra::set_room_capacity(int room, int c) {
    room_capacity[room] = c;
}

bool AnthillDijkstra::is_full(int ants, int c) {
    return ants >= c;
}

bool AnthillDijkstra::has_tunnel(int a, int b) {
    return std::find(graph[a].begin(), graph[a].end(), b) != graph[a].end();
}

int AnthillDijkstra::calculate_weight(int from [[maybe_unused]], int to) {
    int base_weight = 1;
    
    // Penalty for low capacity rooms
    if (room_capacity[to] < total_ants) {
        int capacity_penalty = (total_ants / (room_capacity[to] + 1)) * 2;
        base_weight += capacity_penalty;
    }
    
    return base_weight;
}

void AnthillDijkstra::simulate_dijkstra() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "  🐜 DIJKSTRA ALGORITHM SIMULATION - STARTING" << "\n";
    std::cout << "  Rooms: " << total_rooms << " | Ants: " << total_ants << "\n";
    std::cout << std::string(60, '=') << "\n\n";

    int start_room = 0;
    int end_room = total_rooms - 1;

    // Initialize
    std::vector<int> distances(total_rooms, std::numeric_limits<int>::max());
    std::vector<int> previous(total_rooms, -1);
    distances[start_room] = 0;

    std::priority_queue<Node, std::vector<Node>, std::greater<>> pq;
    pq.push({start_room, 0, {start_room}});

    std::vector<bool> visited(total_rooms, false);

    std::cout << "🔍 Running Dijkstra's algorithm with weighted edges...\n";
    std::cout << "  Edge weights consider room capacities (lower capacity = higher weight)\n\n";

    // Dijkstra algorithm
    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (visited[current.room]) {
            continue;
        }

        visited[current.room] = true;

        if (current.room == end_room) {
            // Found path
            std::cout << "🎯 Found shortest weighted path (" << current.path.size() - 1 << " steps, total weight: " 
                      << current.distance << "):\n  ";
            
            for (size_t i = 0; i < current.path.size(); ++i) {
                std::cout << current.path[i];
                if (i < current.path.size() - 1) {
                    int weight = calculate_weight(current.path[i], current.path[i + 1]);
                    std::cout << " →[w=" << weight << "]→ ";
                }
            }
            std::cout << "\n\n";

            // Path analysis
            std::cout << "📊 Path analysis:\n";
            std::cout << "  • Total distance (weighted): " << current.distance << "\n";
            std::cout << "  • Number of rooms traversed: " << current.path.size() << "\n";
            std::cout << "  • Average weight per edge: " 
                      << std::fixed << std::setprecision(2) 
                      << (double)current.distance / (current.path.size() - 1) << "\n\n";

            // Simulate ant movement
            std::vector<int> best_path = current.path;
            std::vector<int> ants_per_room(total_rooms, 0);
            ants_per_room[0] = total_ants;
            int steps = 0;

            std::cout << std::string(60, '=') << "\n";
            std::cout << "  🚀 DIJKSTRA SIMULATION - MOVING ANTS TO DORMITORY" << "\n";
            std::cout << "  Using shortest weighted path: ";
            for (size_t i = 0; i < best_path.size(); ++i) {
                std::cout << best_path[i];
                if (i < best_path.size() - 1) std::cout << " → ";
            }
            std::cout << "\n" << std::string(60, '=') << "\n\n";

            while (ants_per_room[end_room] < total_ants) {
                std::cout << "\n⏱️  STEP " << steps << "\n";
                std::cout << std::string(30, '-') << "\n";
                
                std::vector<int> next_ants = ants_per_room;
                bool movement_occurred = false;

                // Move ants
                for (int i = static_cast<int>(best_path.size()) - 2; i >= 0; --i) {
                    int from = best_path[i];
                    int to = best_path[i + 1];

                    if (next_ants[from] > 0) {
                        int capacity_left = room_capacity[to] - next_ants[to];
                        int can_send = std::min(next_ants[from], capacity_left);
                        
                        if (can_send > 0) {
                            movement_occurred = true;
                            next_ants[from] -= can_send;
                            next_ants[to] += can_send;
                            std::cout << "  🐜 " << can_send << " ant(s) moved from Room " 
                                    << from << " to Room " << to;
                            
                            int weight = calculate_weight(from, to);
                            if (weight > 1) {
                                std::cout << " (weight: " << weight << ")";
                            }
                            std::cout << "\n";
                        }
                    }
                }

                ants_per_room = next_ants;

                // Print status
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
                
                // Delay
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }

            std::cout << "\n" << std::string(60, '=') << "\n";
            std::cout << "  🎉 DIJKSTRA SIMULATION COMPLETE! 🎉" << "\n";
            std::cout << "  All " << total_ants << " ants reached the dormitory" << "\n";
            std::cout << "  Total steps: " << steps << "\n";
            std::cout << "  Dijkstra distance: " << current.distance << "\n";
            std::cout << std::string(60, '=') << "\n\n";

            return;
        }

        // Explore neighbors
        for (int neighbor : graph[current.room]) {
            if (!visited[neighbor]) {
                int weight = calculate_weight(current.room, neighbor);
                int new_distance = current.distance + weight;

                if (new_distance < distances[neighbor]) {
                    distances[neighbor] = new_distance;
                    previous[neighbor] = current.room;
                    
                    std::vector<int> new_path = current.path;
                    new_path.push_back(neighbor);
                    pq.push({neighbor, new_distance, new_path});
                }
            }
        }
    }

    std::cout << "❌ No path found from start to dormitory using Dijkstra!\n";
}