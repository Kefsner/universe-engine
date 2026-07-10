cmake_minimum_required(VERSION 4.3)

project(universe LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(spdlog REQUIRED)

add_executable(universe
    universe/main.cpp
)

target_link_libraries(universe PRIVATE
    glfw
    glad::glad
    OpenGL::GL
    spdlog::spdlog
)