# CMake Minimum Version
cmake_minimum_required(VERSION 3.10)

# Project's Name
project(path_planning)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)

# Add include directories for the compiler
include_directories(
    include/
)

# Collect all source files from the src directory and save them in the SOURCES variable
file(GLOB SOURCES "src/*.cpp")

# Define the executable file from the collected source files
add_executable(astar_dijkstra ${SOURCES})