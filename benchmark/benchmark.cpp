#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <filesystem>
#include <fstream>
#include "benchmark.h"

// List of anthill names for display
const std::vector<std::string> ANTHILL_NAMES = {
    "Small Hill (4 rooms)",
    "Medium Hill 1 (4 rooms)",
    "Medium Hill 2 (4 rooms, loop)",
    "Medium Hill 3 (6 rooms)",
    "Large Hill (8 rooms)",
    "Extra Large Hill (16 rooms)",
    "King Hill (23 rooms)"
};

const int NUM_ANTHILLS = 7; // Number of anthills available

struct BenchmarkResult {
    std::string anthill_name;
    int bfs_steps;
    double bfs_time_ms;
    int astar_steps;
    double astar_time_ms;
};

void print_results_table(const std::vector<BenchmarkResult>& results) {
    // Print table header
    std::cout << std::left << std::setw(20) << "Anthill"
              << std::setw(15) << "BFS Steps"
              << std::setw(20) << "BFS Time (ms)"
              << std::setw(15) << "A* Steps"
              << std::setw(20) << "A* Time (ms)"
              << std::setw(15) << "Faster Algo"
              << std::setw(15) << "Steps Diff"
              << std::setw(20) << "Time Diff (ms)"
              << "\n";
    
    std::cout << std::string(130, '-') << "\n";
    
    // Print each row
    for (const auto& result : results) {
        std::string faster_algo = (result.bfs_time_ms < result.astar_time_ms) ? "BFS" : "A*";
        int steps_diff = result.bfs_steps - result.astar_steps;
        double time_diff = std::abs(result.bfs_time_ms - result.astar_time_ms);
        
        std::cout << std::left << std::setw(20) << result.anthill_name
                  << std::setw(15) << result.bfs_steps
                  << std::setw(20) << std::fixed << std::setprecision(3) << result.bfs_time_ms
                  << std::setw(15) << result.astar_steps
                  << std::setw(20) << std::fixed << std::setprecision(3) << result.astar_time_ms
                  << std::setw(15) << faster_algo
                  << std::setw(15) << steps_diff
                  << std::setw(20) << std::fixed << std::setprecision(3) << time_diff
                  << "\n";
    }
    
    // Print summary
    if (!results.empty()) {
        double total_bfs_time = 0;
        double total_astar_time = 0;
        int bfs_wins = 0;
        int astar_wins = 0;
        
        for (const auto& result : results) {
            total_bfs_time += result.bfs_time_ms;
            total_astar_time += result.astar_time_ms;
            if (result.bfs_time_ms < result.astar_time_ms) {
                bfs_wins++;
            } else {
                astar_wins++;
            }
        }
        
        std::cout << "\nSummary:\n";
        std::cout << "BFS was faster in " << bfs_wins << " out of " << results.size() << " cases\n";
        std::cout << "A* was faster in " << astar_wins << " out of " << results.size() << " cases\n";
        std::cout << "Total BFS time: " << std::fixed << std::setprecision(3) << total_bfs_time << " ms\n";
        std::cout << "Total A* time: " << std::fixed << std::setprecision(3) << total_astar_time << " ms\n";
        
        if (total_bfs_time < total_astar_time) {
            double percent_faster = ((total_astar_time - total_bfs_time) / total_astar_time) * 100;
            std::cout << "BFS was " << std::fixed << std::setprecision(1) << percent_faster << "% faster overall\n";
        } else {
            double percent_faster = ((total_bfs_time - total_astar_time) / total_bfs_time) * 100;
            std::cout << "A* was " << std::fixed << std::setprecision(1) << percent_faster << "% faster overall\n";
        }
    }
}

int main() {
    std::cout << "Starting benchmark of BFS vs A* algorithms...\n\n";
    
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
        
        results.push_back({anthill_name, bfs_steps, bfs_time, astar_steps, astar_time});
    }
    
    std::cout << "\nBenchmark results:\n";
    print_results_table(results);
    
    return 0;
}
