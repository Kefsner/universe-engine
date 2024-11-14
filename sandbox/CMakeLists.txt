project(Sandbox)

# Add Sandbox as an executable
add_executable(Sandbox src/sandbox.cpp)

# Link Sandbox against the Universe library
target_link_libraries(Sandbox PRIVATE Universe)