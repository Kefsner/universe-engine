# Universe Engine

The **Universe Engine** is a custom-built game engine project inspired by the Cherno's Hazel engine, aiming to provide a solid foundation for 3D game development. The current goal is to implement essential features, including delta time/timestep functionality, with plans to expand into a voxel-based world engine in the style of Minecraft. The project is structured to support modular development and testing.

## Project Structure
- **Universe**: Core engine code and external dependencies.
  - **src**: Main source files for the engine.
  - **vendor**: Third-party libraries required by the engine.
- **Sandbox**: A testing environment for trying out engine features in isolation.
- **Additional Files**: Includes `.gitignore`, `CMakeLists.txt`, and others for configuration and build setup.

## External Libraries
The Universe Engine uses several external libraries to simplify development and enhance performance:

### [GLFW](https://github.com/glfw/glfw)
**Description**: A multi-platform library for creating windows, handling input, and managing OpenGL contexts.
**Reason**: GLFW abstracts window creation and input handling, making it easier to develop cross-platform applications. It’s essential for managing the OpenGL context needed for rendering in the engine.

### [GLAD](https://github.com/Dav1dde/glad)
**Description**: GLAD is an OpenGL function loader that handles loading OpenGL functions based on the system’s supported version.
**Reason**: GLAD ensures compatibility with different versions of OpenGL, allowing the engine to use the latest features available on the user’s hardware.

### [GLM](https://github.com/g-truc/glm)
**Description**: OpenGL Mathematics (GLM) is a mathematics library tailored for graphics applications, providing vector and matrix math functions.
**Reason**: GLM simplifies complex mathematical operations needed for graphics programming, such as transformations and camera management. It is optimized for OpenGL and is crucial for handling 3D mathematics in the engine.

### [spdlog](https://github.com/gabime/spdlog)
**Description**: A fast logging library for C++ applications.
**Reason**: spdlog offers efficient, thread-safe logging. It’s essential for debugging and monitoring, especially in larger projects where tracking execution flow and catching errors early is crucial.

### [ImGui](https://github.com/ocornut/imgui) (Branch: docking)
**Description**: Immediate Mode GUI library for creating real-time, in-app interfaces.
**Reason**: ImGui provides tools for building a real-time debugging and interface layer within the engine, allowing for live parameter adjustments and debugging views. The `docking` branch adds advanced features for multi-window docking, enhancing flexibility during development.

## Development Branches
- **main**: Stable release branch.
- **develop**: Active development branch where new features are tested.
- **rework**: A branch dedicated to refactoring, updating external dependencies, and implementing foundational features up to delta time/timestep functionality.

## Build and Configuration
To build the engine, ensure you have CMake and a compatible C++ compiler installed. More information about specific CMake configurations will be added as development progresses.