project(Universe)

# Collect all .cpp files in the src directory and its subdirectories
file(GLOB_RECURSE UNIVERSE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Add Universe as a static library with all .cpp files
add_library(Universe STATIC ${UNIVERSE_SRC})

# Platform-specific settings
if(WIN32)
    target_compile_definitions(Universe PUBLIC UE_PLATFORM_WINDOWS)
elseif(UNIX)
    target_compile_definitions(Universe PUBLIC UE_PLATFORM_LINUX)
endif()

# Specify include directories
target_include_directories(Universe PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm
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

# Link ImGui
target_sources(Universe PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_demo.cpp
)

target_include_directories(Universe PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends
)