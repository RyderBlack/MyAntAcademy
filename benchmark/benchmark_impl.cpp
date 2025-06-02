#include "benchmark.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <iostream>
#include <climits>
#include <string>
#include <chrono>
#include <iomanip>

// Forward declarations
namespace {
    struct Point {
        size_t x, y;
        Point() : x(0), y(0) {}
        Point(size_t x, size_t y) : x(x), y(y) {}
        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }
        bool operator!=(const Point& other) const {
            return !(*this == other);
        }
        bool operator<(const Point& other) const {
            return std::tie(x, y) < std::tie(other.x, other.y);
        }
    };

    struct PointHash {
        size_t operator()(const Point& p) const {
            return std::hash<size_t>()(p.x) ^ (std::hash<size_t>()(p.y) << 1);
        }
    };

    struct Node {
        Point pos;
        int steps;
        int heuristic;
        std::vector<Point> path;
        
        bool operator>(const Node& other) const {
            return (steps + heuristic) > (other.steps + other.heuristic);
        }
    };

    struct DijkstraNode {
        Point pos;
        int distance;
        std::vector<Point> path;
        
        bool operator>(const DijkstraNode& other) const {
            return distance > other.distance;
        }
    };

    bool is_valid_move(const std::vector<std::string>& grid, size_t x, size_t y) {
        if (grid.empty()) return false;
        return x < grid.size() && y < grid[0].size() && grid[x][y] != '#';
    }

    int manhattan_distance(const Point& a, const Point& b) {
        return static_cast<int>((a.x > b.x ? a.x - b.x : b.x - a.x) + 
                              (a.y > b.y ? a.y - b.y : b.y - a.y));
    }
}

// BFS implementation
int run_bfs(int anthill_num) {
    std::vector<std::string> grid;
    Point start, end;
    
    // Define anthills
    switch (anthill_num) {
        case 0: // Small Hill (4 rooms)
            grid = {
                "#######",
                "#S...#",
                "#.###.#",
                "#.#.#.#",
                "#....##",
                "#E#.#.#",
                "#######"
            };
            start = Point(1, 1);
            end = Point(5, 1);
            break;
            
        case 1: // Medium Hill 1 (4 rooms)
            grid = {
                "#######",
                "#S....#",
                "#.#####",
                "#.....#",
                "#####.#",
                "#E....#",
                "#######"
            };
            start = Point(1, 1);
            end = Point(5, 1);
            break;
            
        case 2: // Medium Hill 2 (4 rooms, loop)
            grid = {
                "#######",
                "#S....#",
                "#.###.#",
                "#.#...#",
                "#.#####",
                "#E....#",
                "#######"
            };
            start = Point(1, 1);
            end = Point(5, 1);
            break;
            
        case 3: // Medium Hill 3 (6 rooms)
            grid = {
                "#######",
                "#S....#",
                "#.#####",
                "#.....#",
                "#.#####",
                "#E....#",
                "#######"
            };
            start = Point(1, 1);
            end = Point(5, 1);
            break;
            
        case 4: // Large Hill (8 rooms)
            grid = {
                "########",
                "#S.....#",
                "#.#####.",
                "#.....#.",
                "#.#####.",
                "#.....#.",
                "#E#####.",
                "########"
            };
            start = Point(1, 1);
            end = Point(6, 1);
            break;
            
        case 5: // Extra Large Hill (16 rooms)
            grid = {
                "##########",
                "#S.......#",
                "#.########",
                "#........#",
                "########.#",
                "#........#",
                "#.########",
                "#........#",
                "##########"
            };
            start = Point(1, 1);
            end = Point(7, 8);
            break;
            
        case 6: // King Hill (23 rooms)
            grid = {
                "###########",
                "#S........#",
                "#.########.",
                "#..........",
                "#.########.",
                "#..........",
                "#.########.",
                "#..........",
                "#.########.",
                "#..........",
                "#.########.",
                "#..........",
                "#.########.",
                "#E........#",
                "###########"
            };
            start = Point(1, 1);
            end = Point(13, 1);
            break;
            
        default:
            std::cerr << "Invalid anthill number: " << anthill_num << std::endl;
            return -1;
    }
    
    // BFS
    std::queue<Node> q;
    std::unordered_set<Point, PointHash> visited;
    
    q.push(Node{start, 0, 0, {start}});
    visited.insert(start);
    
    const std::vector<Point> moves = {Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0)};
    
    while (!q.empty()) {
        Node current = q.front();
        q.pop();
        
        if (current.pos == end) {
            return current.steps;
        }
        
        for (const auto& move : moves) {
            Point next_pos(current.pos.x + move.x, current.pos.y + move.y);
            
            if (is_valid_move(grid, next_pos.x, next_pos.y) && 
                visited.find(next_pos) == visited.end()) {
                
                visited.insert(next_pos);
                std::vector<Point> new_path = current.path;
                new_path.push_back(next_pos);
                q.push(Node{next_pos, current.steps + 1, 0, new_path});
            }
        }
    }
    
    return -1;
}

// A* implementation
int run_astar(int anthill_num) {
    std::vector<std::string> grid;
    Point start, end;
    
    // Define anthills (same as BFS)
    switch (anthill_num) {
        case 0: // Small Hill (4 rooms)
            grid = {
                "#######",
                "#S...#",
                "#.###.#",
                "#.#.#.#",
                "#....##",
                "#E#.#.#",
                "#######"
            };
            start = Point(1, 1);
            end = Point(5, 1);
            break;
            
        case 1: // Medium Hill 1 (4 rooms)
            grid = {
                "#######",
                "#S....#",
                "#.#####",
                "#.....#",
                "#####.#",
                "#E....#",
                "#######"
            };
            start = Point(1, 1);
            end = Point(5, 1);
            break;
            
        case 2: // Medium Hill 2 (4 rooms, loop)
            grid = {
                "#######",
                "#S....#",
                "#.###.#",
                "#.#...#",
                "#.#####",
                "#E....#",
                "#######"
            };
            start = Point(1, 1);
            end = Point(5, 1);
            break;
            
        case 3: // Medium Hill 3 (6 rooms)
            grid = {
                "#######",
                "#S....#",
                "#.#####",
                "#.....#",
                "#.#####",
                "#E....#",
                "#######"
            };
            start = Point(1, 1);
            end = Point(5, 1);
            break;
            
        case 4: // Large Hill (8 rooms)
            grid = {
                "########",
                "#S.....#",
                "#.#####.",
                "#.....#.",
                "#.#####.",
                "#.....#.",
                "#E#####.",
                "########"
            };
            start = Point(1, 1);
            end = Point(6, 1);
            break;
            
        case 5: // Extra Large Hill (16 rooms)
            grid = {
                "##########",
                "#S.......#",
                "#.########",
                "#........#",
                "########.#",
                "#........#",
                "#.########",
                "#........#",
                "##########"
            };
            start = Point(1, 1);
            end = Point(7, 8);
            break;
            
        case 6: // King Hill (23 rooms)
            grid = {
                "###########",
                "#S........#",
                "#.########.",
                "#..........",
                "#.########.",
                "#..........",
                "#.########.",
                "#..........",
                "#.########.",
                "#..........",
                "#.########.",
                "#..........",
                "#.########.",
                "#E........#",
                "###########"
            };
            start = Point(1, 1);
            end = Point(13, 1);
            break;
            
        default:
            std::cerr << "Invalid anthill number: " << anthill_num << std::endl;
            return -1;
    }
    
    // A*
    std::priority_queue<Node, std::vector<Node>, std::greater<>> open_set;
    std::unordered_map<Point, int, PointHash> g_score;
    
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[0].size(); ++j) {
            g_score[Point(i, j)] = INT_MAX;
        }
    }
    
    g_score[start] = 0;
    open_set.push(Node{start, 0, manhattan_distance(start, end), {start}});
    
    const std::vector<Point> moves = {Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0)};
    
    while (!open_set.empty()) {
        Node current = open_set.top();
        open_set.pop();
        
        if (current.pos == end) {
            return current.steps;
        }
        
        if (current.steps > g_score[current.pos]) {
            continue;
        }
        
        for (const auto& move : moves) {
            Point next_pos(current.pos.x + move.x, current.pos.y + move.y);
            
            if (is_valid_move(grid, next_pos.x, next_pos.y)) {
                int tentative_g_score = current.steps + 1;
                
                if (tentative_g_score < g_score[next_pos]) {
                    g_score[next_pos] = tentative_g_score;
                    int h_score = manhattan_distance(next_pos, end);
                    std::vector<Point> new_path = current.path;
                    new_path.push_back(next_pos);
                    open_set.push(Node{next_pos, tentative_g_score, h_score, new_path});
                }
            }
        }
    }
    
    return -1;
}

// Dijkstra implementation
int run_dijkstra(int anthill_num) {
    std::vector<std::string> grid;
    Point start, end;
    
    // Define anthills (same as others)
    switch (anthill_num) {
        case 0: // Small Hill (4 rooms)
            grid = {
                "#######",
                "#S...#",
                "#.###.#",
                "#.#.#.#",
                "#....##",
                "#E#.#.#",
                "#######"
            };
            start = Point(1, 1);
            end = Point(5, 1);
            break;
            
        case 1: // Medium Hill 1 (4 rooms)
            grid = {
                "#######",
                "#S....#",
                "#.#####",
                "#.....#",
                "#####.#",
                "#E....#",
                "#######"
            };
            start = Point(1, 1);
            end = Point(5, 1);
            break;
            
        case 2: // Medium Hill 2 (4 rooms, loop)
            grid = {
                "#######",
                "#S....#",
                "#.###.#",
                "#.#...#",
                "#.#####",
                "#E....#",
                "#######"
            };
            start = Point(1, 1);
            end = Point(5, 1);
            break;
            
        case 3: // Medium Hill 3 (6 rooms)
            grid = {
                "#######",
                "#S....#",
                "#.#####",
                "#.....#",
                "#.#####",
                "#E....#",
                "#######"
            };
            start = Point(1, 1);
            end = Point(5, 1);
            break;
            
        case 4: // Large Hill (8 rooms)
            grid = {
                "########",
                "#S.....#",
                "#.#####.",
                "#.....#.",
                "#.#####.",
                "#.....#.",
                "#E#####.",
                "########"
            };
            start = Point(1, 1);
            end = Point(6, 1);
            break;
            
        case 5: // Extra Large Hill (16 rooms)
            grid = {
                "##########",
                "#S.......#",
                "#.########",
                "#........#",
                "########.#",
                "#........#",
                "#.########",
                "#........#",
                "##########"
            };
            start = Point(1, 1);
            end = Point(7, 8);
            break;
            
        case 6: // King Hill (23 rooms)
            grid = {
                "###########",
                "#S........#",
                "#.########.",
                "#..........",
                "#.########.",
                "#..........",
                "#.########.",
                "#..........",
                "#.########.",
                "#..........",
                "#.########.",
                "#..........",
                "#.########.",
                "#E........#",
                "###########"
            };
            start = Point(1, 1);
            end = Point(13, 1);
            break;
            
        default:
            std::cerr << "Invalid anthill number: " << anthill_num << std::endl;
            return -1;
    }
    
    // Dijkstra
    std::priority_queue<DijkstraNode, std::vector<DijkstraNode>, std::greater<>> pq;
    std::unordered_map<Point, int, PointHash> distances;
    
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[0].size(); ++j) {
            distances[Point(i, j)] = INT_MAX;
        }
    }
    
    distances[start] = 0;
    pq.push({start, 0, {start}});
    
    std::unordered_set<Point, PointHash> visited;
    const std::vector<Point> moves = {Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0)};
    
    while (!pq.empty()) {
        DijkstraNode current = pq.top();
        pq.pop();
        
        if (visited.find(current.pos) != visited.end()) {
            continue;
        }
        
        visited.insert(current.pos);
        
        if (current.pos == end) {
            return current.path.size() - 1;
        }
        
        for (const auto& move : moves) {
            Point next_pos(current.pos.x + move.x, current.pos.y + move.y);
            
            if (is_valid_move(grid, next_pos.x, next_pos.y) && 
                visited.find(next_pos) == visited.end()) {
                
                int new_distance = current.distance + 1;
                
                if (new_distance < distances[next_pos]) {
                    distances[next_pos] = new_distance;
                    std::vector<Point> new_path = current.path;
                    new_path.push_back(next_pos);
                    pq.push({next_pos, new_distance, new_path});
                }
            }
        }
    }
    
    return -1;
}