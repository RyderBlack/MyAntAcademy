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

# Add executable
add_executable(MyAntAcademy
    main.cpp
    ants.cpp
    ants.h
)

# Set target properties
target_include_directories(MyAntAcademy PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Set output directory for the executable
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# Print configuration summary
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Add install target
install(TARGETS MyAntAcademy
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
