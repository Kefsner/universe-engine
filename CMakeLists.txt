# Root CMakeLists.txt
cmake_minimum_required(VERSION 3.15)
project(UniverseEngine)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories for Universe and Sandbox
add_subdirectory(universe)
add_subdirectory(sandbox)