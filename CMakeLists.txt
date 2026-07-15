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

add_executable(universe
    universe/main.cpp

    universe/core/Window.cpp
    universe/core/ImGuiLayer.cpp
    universe/core/AssetManager.cpp

    universe/renderer/Shader.cpp
    universe/renderer/Renderer.cpp
    universe/renderer/Texture.cpp
    universe/renderer/VertexArray.cpp
    universe/renderer/VertexBuffer.cpp
    universe/renderer/IndexBuffer.cpp
)

target_include_directories(universe PRIVATE
    ${Stb_INCLUDE_DIR}
    universe/
)

target_link_libraries(universe PRIVATE
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