project(Universe)

# Collect all .cpp files in the src directory and its subdirectories
file(GLOB_RECURSE UNIVERSE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Add Universe as a static library with all .cpp files
add_library(Universe STATIC ${UNIVERSE_SRC})

# Specify include directories
target_include_directories(Universe PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link dependencies
add_subdirectory(vendor/spdlog)
target_link_libraries(Universe PUBLIC spdlog::spdlog)
