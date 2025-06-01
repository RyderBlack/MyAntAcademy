#include "ants_astar.h"
#include <queue>
#include <limits>

AnthillAStar::AnthillAStar(int total_rooms, int total_ants) 
    : total_rooms(total_rooms), total_ants(total_ants) {
    graph.resize(total_rooms);
    room_capacity.resize(total_rooms, 0);
}

void AnthillAStar::add_tunnels(int a, int b) {
    graph[a].push_back(b);
    graph[b].push_back(a);
}

void AnthillAStar::set_room_capacity(int room, int c) {
    room_capacity[room] = c;
}

bool AnthillAStar::is_full(int ants, int c) {
    return ants >= c;
}

bool AnthillAStar::has_tunnel(int a, int b) {
    return std::find(graph[a].begin(), graph[a].end(), b) != graph[a].end();
}

void AnthillAStar::simulate_astar() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "  🐜 A* ANT SIMULATION - STARTING" << "\n";
    std::cout << "  Rooms: " << total_rooms << " | Ants: " << total_ants << "\n";
    std::cout << std::string(60, '=') << "\n\n";

    int start_room = 0;
    int end_room = total_rooms - 1;

    // Priority queue for A* algorithm
    std::priority_queue<Node, std::vector<Node>, std::greater<>> open_set;
    
    // Store the best path found so far
    std::vector<int> best_path;
    bool path_found = false;

    // Initialize the start node
    Node start_node{start_room, 0, heuristic(start_room, end_room), {start_room}};
    open_set.push(start_node);

    // For tracking visited nodes and their g_scores
    std::unordered_map<int, int> g_scores;
    g_scores[start_room] = 0;

    while (!open_set.empty()) {
        Node current = open_set.top();
        open_set.pop();

        // If we've reached the end, store the path and break
        if (current.room == end_room) {
            best_path = current.path;
            path_found = true;
            break;
        }

        // If we found a better path to this node, skip it
        if (g_scores[current.room] < current.g_score) {
            continue;
        }


        // Explore neighbors
        for (int neighbor : graph[current.room]) {
            int tentative_g_score = current.g_score + 1;  // Each step has equal cost

            // If this path to neighbor is better than any previous one
            if (g_scores.find(neighbor) == g_scores.end() || 
                tentative_g_score < g_scores[neighbor]) {
                
                g_scores[neighbor] = tentative_g_score;
                
                Node neighbor_node{
                    neighbor,
                    tentative_g_score,
                    tentative_g_score + heuristic(neighbor, end_room),
                    current.path
                };
                neighbor_node.path.push_back(neighbor);
                
                open_set.push(neighbor_node);
            }
        }
    }

    if (!path_found) {
        std::cout << "❌ No path found from start to dormitory!\n";
        return;
    }

    // Print the found path
    std::cout << "🔍 Found A* path (" << best_path.size() - 1 << " steps): ";
    for (size_t i = 0; i < best_path.size(); ++i) {
        std::cout << best_path[i];
        if (i < best_path.size() - 1) {
            std::cout << " → ";
        }
    }
    std::cout << "\n\n";

    // Simulation of ant movement
    std::vector<int> ants_per_room(total_rooms, 0);
    ants_per_room[0] = total_ants;
    int steps = 0;

    std::cout << std::string(60, '=') << "\n";
    std::cout << "  🚀 A* SIMULATION STARTING - MOVING ANTS TO DORMITORY" << "\n";
    std::cout << "  Using path: ";
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

        // Move ants one segment at a time in each step
        for (int segment = 0; segment < static_cast<int>(best_path.size()) - 1; ++segment) {
            // For each segment in the path, move ants if possible
            for (int i = 0; i < static_cast<int>(best_path.size()) - 1; ++i) {
                int from = best_path[i];
                int to = best_path[i + 1];

                // Only move ants from rooms that have ants and have capacity in the next room
                if (next_ants[from] > 0) {
                    int capacity_left = room_capacity[to] - next_ants[to];
                    if (capacity_left > 0) {
                        // Move at most 1 ant at a time per segment to simulate realistic movement
                        int can_send = std::min(1, std::min(next_ants[from], capacity_left));
                        
                        if (can_send > 0) {
                            movement_occurred = true;
                            next_ants[from] -= can_send;
                            next_ants[to] += can_send;
                            std::cout << "  🐜 " << can_send << " ant(s) moved from Room " 
                                    << from << " to Room " << to << "\n";
                        }
                    }
                }
            }
            
            // If we've moved ants, update the state and break to show the next step
            if (movement_occurred) {
                break;
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
    std::cout << "  🎉 A* SIMULATION COMPLETE! 🎉" << "\n";
    std::cout << "  All " << total_ants << " ants reached the dormitory" << "\n";
    std::cout << "  Total steps: " << steps << "\n";
    std::cout << std::string(60, '=') << "\n\n";
}
