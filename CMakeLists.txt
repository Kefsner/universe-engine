cmake_minimum_required(VERSION 4.3)

project(universe LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(spdlog REQUIRED)
find_package(imgui REQUIRED)
find_package(glm REQUIRED)
find_package(Stb REQUIRED)
find_package(EnTT CONFIG REQUIRED)

add_library(universe STATIC
    universe/src/Application.cpp

    universe/src/core/Window.cpp
    universe/src/core/ImGuiLayer.cpp
    universe/src/core/AssetManager.cpp
    universe/src/core/Logger.cpp

    universe/src/renderer/Shader.cpp
    universe/src/renderer/Renderer.cpp
    universe/src/renderer/Texture.cpp
    universe/src/renderer/VertexArray.cpp
    universe/src/renderer/VertexBuffer.cpp
    universe/src/renderer/IndexBuffer.cpp
)

target_include_directories(universe
PUBLIC
    universe/include
    universe/src
PRIVATE
    ${Stb_INCLUDE_DIR}
)

target_link_libraries(universe PUBLIC
    glfw
    glad::glad
    OpenGL::GL
    spdlog::spdlog
    imgui::imgui
    glm::glm
    EnTT::EnTT
)

target_compile_definitions(universe PRIVATE
    $<$<CONFIG:Debug>:UNIVERSE_DEBUG>
    $<$<CONFIG:Release>:UNIVERSE_RELEASE>
)


add_executable(game
    game/Game.cpp
)

target_link_libraries(game PRIVATE universe)