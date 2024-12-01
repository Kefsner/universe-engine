project(Universe)

# Collect all .cpp files in the src directory and its subdirectories
file(GLOB_RECURSE UNIVERSE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Add Universe as a static library with all .cpp files
add_library(Universe STATIC ${UNIVERSE_SRC})

# Platform-specific settings
if(WIN32)
    add_compile_definitions(UE_PLATFORM_WINDOWS)
elseif(UNIX)
    add_compile_definitions(UE_PLATFORM_LINUX)
endif()

target_precompile_headers(Universe PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/src/pch.hpp>
)

# Include directories
target_include_directories(Universe PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb
    ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES} # Include C++ standard library
)

# Add Glad (OpenGL loader) sources
target_sources(Universe PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/src/glad.c
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb/stb_image.cpp
)

# Link dependencies
# Add spdlog for logging
add_subdirectory(vendor/spdlog)
target_link_libraries(Universe PUBLIC spdlog::spdlog)

# Add GLFW for windowing
# Set GLFW to build with X11 support and disable Wayland
set(GLFW_BUILD_X11 ON CACHE BOOL "Build GLFW with X11 support")
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "Disable Wayland support for GLFW")

add_subdirectory(vendor/glfw)
target_link_libraries(Universe PUBLIC glfw)

# Link OpenGL
if(WIN32)
    target_link_libraries(Universe PUBLIC opengl32)
elseif(UNIX)
    find_package(OpenGL REQUIRED)
    target_link_libraries(Universe PUBLIC OpenGL::GL)
endif()
