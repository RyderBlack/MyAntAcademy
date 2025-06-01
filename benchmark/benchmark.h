#pragma once

// Function to run BFS algorithm on a specific anthill
// anthill_num: Index of the anthill to test (0-3)
// Returns the number of steps taken to solve the anthill, or -1 if no path found
int run_bfs(int anthill_num);

// Function to run A* algorithm on a specific anthill
// anthill_num: Index of the anthill to test (0-3)
// Returns the number of steps taken to solve the anthill, or -1 if no path found
int run_astar(int anthill_num);
