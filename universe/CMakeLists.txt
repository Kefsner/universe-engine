project(Universe)

# Collect all .cpp files in the src directory and its subdirectories
file(GLOB_RECURSE UNIVERSE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Add Universe as a static library with all .cpp files
add_library(Universe STATIC ${UNIVERSE_SRC})

# Specify include directories
target_include_directories(Universe PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include  # Include glad's headers
)

# Include the glad.c file in the Universe library
target_sources(Universe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/src/glad.c)

# Link dependencies
# Link spdlog
add_subdirectory(vendor/spdlog)
target_link_libraries(Universe PUBLIC spdlog::spdlog)

# Link GLFW
add_subdirectory(vendor/glfw)
target_link_libraries(Universe PUBLIC glfw)

# Link OpenGL
target_link_libraries(Universe PUBLIC opengl32)
