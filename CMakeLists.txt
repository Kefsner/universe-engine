cmake_minimum_required(VERSION 3.15)
project(UniverseEngine)

# Set the C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for your source code and spdlog
include_directories(${PROJECT_SOURCE_DIR}/universe/src)

# Add spdlog as a subdirectory (make sure the path is correct)
add_subdirectory(${PROJECT_SOURCE_DIR}/universe/vendor/spdlog)

# Add the main.cpp file to the executable
add_executable(UniverseEngine 
    universe/src/universe.cpp
    universe/src/engine/core/logger/logger.cpp
)

# Define UE_ENABLE_LOGGING to enable logging
target_compile_definitions(UniverseEngine PRIVATE UE_ENABLE_LOGGING)

# Link only spdlog (now spdlog is correctly added via subdirectory)
target_link_libraries(UniverseEngine PRIVATE spdlog::spdlog)
