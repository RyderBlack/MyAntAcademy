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
    // Print table header with consistent column widths
    const int name_width = 30;    // Increased for longer anthill names
    const int steps_width = 12;
    const int time_width = 16;
    const int algo_width = 14;
    const int diff_width = 14;
    
    // Print header
    std::cout << std::left 
              << std::setw(name_width) << "ANTHILL"
              << std::right
              << std::setw(steps_width) << "BFS STEPS"
              << std::setw(time_width) << "BFS TIME (ms)"
              << std::setw(steps_width) << "A* STEPS"
              << std::setw(time_width) << "A* TIME (ms)"
              << std::setw(algo_width) << "FASTER"
              << std::setw(diff_width) << "STEPS DIFF"
              << std::setw(time_width) << "TIME DIFF (ms)"
              << "\n" << std::string(120, '=') << "\n";
    
    // Print each row
    for (const auto& result : results) {
        std::string faster_algo = (result.bfs_time_ms < result.astar_time_ms) ? "BFS" : "A*";
        int steps_diff = result.bfs_steps - result.astar_steps;
        double time_diff = std::abs(result.bfs_time_ms - result.astar_time_ms);
        
        std::cout << std::left << std::setw(name_width) << result.anthill_name
                  << std::right
                  << std::setw(steps_width) << result.bfs_steps
                  << std::setw(time_width) << std::fixed << std::setprecision(3) << result.bfs_time_ms
                  << std::setw(steps_width) << result.astar_steps
                  << std::setw(time_width) << std::fixed << std::setprecision(3) << result.astar_time_ms
                  << std::setw(algo_width) << faster_algo
                  << std::setw(diff_width) << steps_diff
                  << std::setw(time_width) << std::fixed << std::setprecision(3) << time_diff
                  << "\n";
    }
    
    // Print summary with better formatting
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
        
        // Calculate the maximum width needed for the summary
        const int label_width = 25;
        const int value_width = 15;
        
        std::cout << "\n" << std::string(50, '=') << "\n";
        std::cout << "SUMMARY" << "\n";
        std::cout << std::string(50, '-') << "\n";
        
        // Print summary with aligned columns
        std::cout << std::left << std::setw(label_width) << "BFS was faster in:"
                  << std::right << std::setw(value_width) 
                  << bfs_wins << " out of " << results.size() << " cases\n";
                  
        std::cout << std::left << std::setw(label_width) << "A* was faster in:"
                  << std::right << std::setw(value_width)
                  << astar_wins << " out of " << results.size() << " cases\n\n";
                  
        std::cout << std::left << std::setw(label_width) << "Total BFS time:"
                  << std::right << std::setw(value_width) << std::fixed << std::setprecision(3) 
                  << total_bfs_time << " ms\n";
                  
        std::cout << std::left << std::setw(label_width) << "Total A* time:"
                  << std::right << std::setw(value_width) << std::fixed << std::setprecision(3) 
                  << total_astar_time << " ms\n";
        
        if (total_bfs_time < total_astar_time) {
            double percent_faster = ((total_astar_time - total_bfs_time) / total_astar_time) * 100;
            std::cout << "\n" << std::left << std::setw(label_width) << "BFS was faster by:"
                      << std::right << std::setw(value_width) << std::fixed << std::setprecision(1)
                      << percent_faster << "%\n";
        } else if (total_astar_time < total_bfs_time) {
            double percent_faster = ((total_bfs_time - total_astar_time) / total_bfs_time) * 100;
            std::cout << "\n" << std::left << std::setw(label_width) << "A* was faster by:"
                      << std::right << std::setw(value_width) << std::fixed << std::setprecision(1)
                      << percent_faster << "%\n";
        } else {
            std::cout << "\n" << std::left << std::setw(label_width) << "Both algorithms"
                      << std::right << std::setw(value_width) << "performed equally\n";
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
