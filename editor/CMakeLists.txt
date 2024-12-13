project(Editor)

# Add Editor as an executable
add_executable(Editor
    src/editor.cpp
    src/editor_layer.cpp
)

# Link Editor against the Universe library
target_link_libraries(Editor PRIVATE Universe)

# Add include directories for Editor
target_include_directories(Editor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Include debug/release-specific definitions and compiler options
target_compile_definitions(Editor PRIVATE 
    $<$<CONFIG:Debug>:DEBUG_BUILD>
    $<$<CONFIG:Release>:RELEASE_BUILD>
)
target_compile_options(Editor PRIVATE 
    $<$<CONFIG:Debug>:-g -O0>        # Enable debugging info for Debug builds
    $<$<CONFIG:Release>:-O3 -DNDEBUG> # Optimize for Release builds
)