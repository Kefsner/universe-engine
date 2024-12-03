# Root CMakeLists.txt
cmake_minimum_required(VERSION 3.15)
project(UniverseEngine)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type (Debug, Release)" FORCE)
endif()

# Add subdirectories for Universe and Sandbox
add_subdirectory(universe)
add_subdirectory(sandbox)