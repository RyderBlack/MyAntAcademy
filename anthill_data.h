#pragma once
#include <vector>
#include <string>
#include <utility>  // for std::pair

struct AnthillData {
    int numAnts;
    std::vector<std::string> states;
    std::vector<std::pair<std::string, std::string>> edges;
};

namespace Anthills {
    // First anthill (from fourmiliere_un.txt)
    inline AnthillData fourmiliere_un = {
        5,  // f=5
        {"Sv", "S1", "S2", "Sd"},  // States
        {  // Edges
            {"Sv", "S1"},
            {"S1", "S2"},
            {"S2", "Sd"}
        }
    };

    // Second anthill (from fourmiliere_deux.txt)
    inline AnthillData fourmiliere_deux = {
        3,  // f=3
        {"Sv", "S1", "S2", "S3", "Sd"},
        {
            {"Sv", "S1"},
            {"S1", "S2"},
            {"S2", "S3"},
            {"S3", "Sd"},
            {"S1", "S3"}  // Example of an alternative path
        }
    };

    // Third anthill (from fourmiliere_trois.txt)
    inline AnthillData fourmiliere_trois = {
        7,
        {"Sv", "S1", "S2", "S3", "S4", "Sd"},
        {
            {"Sv", "S1"},
            {"S1", "S2"},
            {"S2", "S3"},
            {"S3", "S4"},
            {"S4", "Sd"},
            {"S1", "S3"},  // Alternative path
            {"S2", "S4"}   // Another alternative
        }
    };
}
