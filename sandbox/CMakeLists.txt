project(Sandbox)

# Add Sandbox as an executable
add_executable(Sandbox
    src/sandbox.cpp
    src/sandbox2D.cpp
)

# Link Sandbox against the Universe library
target_link_libraries(Sandbox PRIVATE Universe)

# Add include directories for Sandbox
target_include_directories(Sandbox PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Include debug/release-specific definitions and compiler options
target_compile_definitions(Sandbox PRIVATE 
    $<$<CONFIG:Debug>:DEBUG_BUILD>
    $<$<CONFIG:Release>:RELEASE_BUILD>
)
target_compile_options(Sandbox PRIVATE 
    $<$<CONFIG:Debug>:-g -O0>        # Enable debugging info for Debug builds
    $<$<CONFIG:Release>:-O3 -DNDEBUG> # Optimize for Release builds
)