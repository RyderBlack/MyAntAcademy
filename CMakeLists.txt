cmake_minimum_required(VERSION 3.15)
project(MyAntAcademy VERSION 1.0)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable more warnings
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Set output directories
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# BFS Version
add_executable(MyAntAcademy_bfs
    bfs_algo/main.cpp
    bfs_algo/ants.cpp
)
target_include_directories(MyAntAcademy_bfs PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/bfs_algo
)

# A* Version
add_executable(MyAntAcademy_astar
    astar_algo/main_astar.cpp
    astar_algo/ants_astar.cpp
)
target_include_directories(MyAntAcademy_astar PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/astar_algo
)

# Print configuration summary
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Benchmark executable
add_executable(MyAntAcademy_benchmark
    benchmark/benchmark.cpp
    benchmark/benchmark_impl.cpp
)
target_include_directories(MyAntAcademy_benchmark PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/benchmark
)

# Add install targets
install(TARGETS MyAntAcademy_bfs MyAntAcademy_astar MyAntAcademy_benchmark
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
