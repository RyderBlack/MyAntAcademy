#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <filesystem>
#include <fstream>
#include "benchmark.h"

const std::vector<std::string> ANTHILL_NAMES = {
    "Small Hill (4 rooms)",
    "Medium Hill 1 (4 rooms)",
    "Medium Hill 2 (4 rooms, loop)",
    "Medium Hill 3 (6 rooms)",
    "Large Hill (8 rooms)",
    "Extra Large Hill (16 rooms)",
    "King Hill (23 rooms)"
};

const int NUM_ANTHILLS = 7;

struct BenchmarkResult {
    std::string anthill_name;
    int bfs_steps;
    double bfs_time_ms;
    int astar_steps;
    double astar_time_ms;
    int dijkstra_steps;
    double dijkstra_time_ms;
};

void print_results_table(const std::vector<BenchmarkResult>& results) {
    const int name_width = 30;
    const int steps_width = 12;
    const int time_width = 16;
    const int algo_width = 14;
    
    // Header
    std::cout << std::left 
              << std::setw(name_width) << "ANTHILL"
              << std::right
              << std::setw(steps_width) << "BFS STEPS"
              << std::setw(time_width) << "BFS TIME (ms)"
              << std::setw(steps_width) << "A* STEPS"
              << std::setw(time_width) << "A* TIME (ms)"
              << std::setw(steps_width) << "DIJKSTRA STEPS"
              << std::setw(time_width) << "DIJKSTRA TIME (ms)"
              << std::setw(algo_width) << "FASTEST"
              << "\n" << std::string(140, '=') << "\n";
    
    // Rows
    for (const auto& result : results) {
        std::string fastest_algo = "BFS";
        double min_time = result.bfs_time_ms;
        
        if (result.astar_time_ms < min_time) {
            fastest_algo = "A*";
            min_time = result.astar_time_ms;
        }
        
        if (result.dijkstra_time_ms < min_time) {
            fastest_algo = "Dijkstra";
            min_time = result.dijkstra_time_ms;
        }
        
        std::cout << std::left << std::setw(name_width) << result.anthill_name
                  << std::right
                  << std::setw(steps_width) << result.bfs_steps
                  << std::setw(time_width) << std::fixed << std::setprecision(3) << result.bfs_time_ms
                  << std::setw(steps_width) << result.astar_steps
                  << std::setw(time_width) << std::fixed << std::setprecision(3) << result.astar_time_ms
                  << std::setw(steps_width) << result.dijkstra_steps
                  << std::setw(time_width) << std::fixed << std::setprecision(3) << result.dijkstra_time_ms
                  << std::setw(algo_width) << fastest_algo
                  << "\n";
    }
    
    // Summary
    if (!results.empty()) {
        double total_bfs_time = 0;
        double total_astar_time = 0;
        double total_dijkstra_time = 0;
        int bfs_wins = 0;
        int astar_wins = 0;
        int dijkstra_wins = 0;
        
        for (const auto& result : results) {
            total_bfs_time += result.bfs_time_ms;
            total_astar_time += result.astar_time_ms;
            total_dijkstra_time += result.dijkstra_time_ms;
            
            double min_time = std::min({result.bfs_time_ms, result.astar_time_ms, result.dijkstra_time_ms});
            
            if (result.bfs_time_ms == min_time) bfs_wins++;
            else if (result.astar_time_ms == min_time) astar_wins++;
            else dijkstra_wins++;
        }
        
        const int label_width = 25;
        const int value_width = 20;
        
        std::cout << "\n" << std::string(50, '=') << "\n";
        std::cout << "SUMMARY" << "\n";
        std::cout << std::string(50, '-') << "\n";
        
        std::cout << std::left << std::setw(label_width) << "BFS was fastest in:"
                  << std::right << std::setw(value_width) 
                  << bfs_wins << " out of " << results.size() << " cases\n";
                  
        std::cout << std::left << std::setw(label_width) << "A* was fastest in:"
                  << std::right << std::setw(value_width)
                  << astar_wins << " out of " << results.size() << " cases\n";
                  
        std::cout << std::left << std::setw(label_width) << "Dijkstra was fastest in:"
                  << std::right << std::setw(value_width)
                  << dijkstra_wins << " out of " << results.size() << " cases\n\n";
                  
        std::cout << std::left << std::setw(label_width) << "Total BFS time:"
                  << std::right << std::setw(value_width) << std::fixed << std::setprecision(3) 
                  << total_bfs_time << " ms\n";
                  
        std::cout << std::left << std::setw(label_width) << "Total A* time:"
                  << std::right << std::setw(value_width) << std::fixed << std::setprecision(3) 
                  << total_astar_time << " ms\n";
                  
        std::cout << std::left << std::setw(label_width) << "Total Dijkstra time:"
                  << std::right << std::setw(value_width) << std::fixed << std::setprecision(3) 
                  << total_dijkstra_time << " ms\n";
        
        // Find overall fastest
        double min_total = std::min({total_bfs_time, total_astar_time, total_dijkstra_time});
        std::string fastest_overall;
        
        if (total_bfs_time == min_total) fastest_overall = "BFS";
        else if (total_astar_time == min_total) fastest_overall = "A*";
        else fastest_overall = "Dijkstra";
        
        std::cout << "\n" << std::left << std::setw(label_width) << "Fastest overall:"
                  << std::right << std::setw(value_width) << fastest_overall << "\n";
    }
}

int main() {
    std::cout << "Starting benchmark of BFS vs A* vs Dijkstra algorithms...\n\n";
    
    std::vector<BenchmarkResult> results;
    
    for (int i = 0; i < NUM_ANTHILLS; i++) {
        std::string anthill_name = ANTHILL_NAMES[i];
        
        std::cout << "Running benchmark for " << anthill_name << "...\n";
        
        // Run BFS
        auto bfs_start = std::chrono::high_resolution_clock::now();
        int bfs_steps = run_bfs(i);
        auto bfs_end = std::chrono::high_resolution_clock::now();
        double bfs_time = std::chrono::duration<double, std::milli>(bfs_end - bfs_start).count();
        
        // Run A*
        auto astar_start = std::chrono::high_resolution_clock::now();
        int astar_steps = run_astar(i);
        auto astar_end = std::chrono::high_resolution_clock::now();
        double astar_time = std::chrono::duration<double, std::milli>(astar_end - astar_start).count();
        
        // Run Dijkstra
        auto dijkstra_start = std::chrono::high_resolution_clock::now();
        int dijkstra_steps = run_dijkstra(i);
        auto dijkstra_end = std::chrono::high_resolution_clock::now();
        double dijkstra_time = std::chrono::duration<double, std::milli>(dijkstra_end - dijkstra_start).count();
        
        results.push_back({anthill_name, bfs_steps, bfs_time, astar_steps, astar_time, dijkstra_steps, dijkstra_time});
    }
    
    std::cout << "\nBenchmark results:\n";
    print_results_table(results);
    
    return 0;
}