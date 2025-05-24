cmake_minimum_required(VERSION 3.21)
project(MyAntAcademy)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add all source files
set(SOURCES
        main.cpp
        AntGraph.cpp
        AntGraph.h
        ants.cpp
        ants.h
)

# Create the executable
add_executable(MyAntAcademy ${SOURCES})

# For Windows, set the executable to use the console subsystem
if(WIN32)
    if(MSVC)
        set_target_properties(MyAntAcademy PROPERTIES
                WIN32_EXECUTABLE FALSE
                LINK_FLAGS "/SUBSYSTEM:CONSOLE"
                )
    else()
        # For MinGW, use different syntax
        set_target_properties(MyAntAcademy PROPERTIES
                LINK_FLAGS "-Wl,-subsystem,console"
                )
    endif()
endif()

# Include the current directory for header files
target_include_directories(MyAntAcademy PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
