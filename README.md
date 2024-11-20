Here's the updated README with the requested additions, placeholders for further topics, and descriptions for the `Application` class and the `Sandbox`:

---

# Universe Engine

The **Universe Engine** is a custom-built game engine project inspired by the Cherno's Hazel engine, aiming to provide a solid foundation for 3D game development. The current goal is to implement essential features, including delta time/timestep functionality, with plans to expand into a voxel-based world engine in the style of Minecraft. The project is structured to support modular development and testing.

---

## Project Structure

The Universe Engine is designed as a modular system, with the core engine built as a library and linked to a sandbox application for testing and experimentation.

### **Core Structure**
- **Universe**: The main engine library, which includes the core functionality for game development.
  - **src**: Contains the core source files for the engine, such as application management, rendering, and event handling.
  - **vendor**: Third-party libraries used to enhance engine capabilities (e.g., `GLFW`, `GLM`, `spdlog`).
- **Sandbox**: A testing environment that serves as a minimal game application to demonstrate and validate the engine's functionality.

### **How It Works**
The `Universe` engine is compiled as a static library (`libUniverse.a` or `Universe.lib`) and linked to the `Sandbox` project. The `Sandbox` application includes a minimal implementation of game functionality, such as testing layers, events, and rendering, using the core engine.

### Example Flow
1. **Develop Core Engine**: Implement features like event handling, rendering, and layers in the `Universe` project.
2. **Test in Sandbox**: Create a basic application in `Sandbox` that inherits from the `Application` class and adds layers or custom logic to test new engine features.

---

## Application and Sandbox

### **Application Class**
The `Application` class is the backbone of the engine. It manages:
- The **main loop**, which is responsible for:
  - Updating layers.
  - Processing events.
  - Managing rendering.
- The **window**, where rendering and user interaction occur.
- The **layer stack**, which allows modular components (like game logic or UI) to interact with the engine.

#### Key Features:
- Singleton design ensures only one `Application` instance exists.
- Provides a clean interface for adding layers and propagating events through them.
- Simplifies game and engine lifecycle management by centralizing core operations.

### **Sandbox**
The `Sandbox` application inherits from the `Application` class and acts as a testing ground for engine features. It allows developers to:
- Create and test new layers, events, and rendering techniques without modifying the core engine.
- Experiment with custom game logic while relying on the engine for foundational features like event handling and rendering.

#### Example:
A basic `Sandbox` implementation might look like this:
```cpp
class Sandbox : public Universe::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
    }
};

Universe::Application* Universe::CreateApplication() {
    return new Sandbox();
}
```

The `Sandbox` provides a minimal implementation of a game that demonstrates how to use the engine.

---

## Core Elements of a Game Engine (Placeholder Section)

In this section, we will describe the roles and goals of each major element in the game engine, including their general purpose and the specific features implemented in the Universe Engine.

### **Application Class**
The heart of the engine, managing the main loop, layers, and events.

### **Events**
Handles communication between different parts of the engine and processes user input, window interactions, and custom game events.

### **Layers**
Allows modular development by organizing game logic, UI, and rendering into distinct, stackable components.

### **Shaders**
Defines how vertices and fragments are processed in the graphics pipeline, enabling custom rendering techniques.

### **Buffers**
Stores and manages vertex and index data for rendering.

### **Window Management**
Handles creating and interacting with the platform-specific window, including input and context management.

### **Rendering Pipeline**
Implements the steps for transforming game data into visuals displayed on the screen.

### **Delta Time / Timestep**
A crucial mechanism for ensuring smooth movement and behavior regardless of frame rate.

## External Libraries

The Universe Engine uses several external libraries to simplify development and enhance performance:

### [GLFW](https://github.com/glfw/glfw)
**Description**: A multi-platform library for creating windows, handling input, and managing OpenGL contexts.  
**Reason**: GLFW abstracts window creation and input handling, making it easier to develop cross-platform applications. It’s essential for managing the OpenGL context needed for rendering in the engine.

### [GLAD](https://github.com/Dav1dde/glad)
**Description**: GLAD is an OpenGL function loader that handles loading OpenGL functions based on the system’s supported version.  
**Reason**: GLAD ensures compatibility with different versions of OpenGL, allowing the engine to use the latest features available on the user’s hardware. Unlike other dependencies, GLAD does not require Git submodule integration. Instead, it was manually downloaded and included directly in the project. No additional linking is necessary beyond including its source files.

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

### Build Process and Linking in C++

When developing in C++, the build process is typically divided into several phases:

1. **Preprocessing**: The compiler processes your source code, handling directives like `#include` and `#define`. This phase results in an intermediate code that includes all headers and macro expansions.

2. **Compilation**: The compiler takes the preprocessed source code and translates it into **object files** (`.o` or `.obj`), which are machine-readable files containing the compiled code but not yet linked into an executable.

3. **Linking**: The linker is responsible for combining the compiled object files and linking them with any required libraries (static or shared). It resolves external references in the object files to the actual implementations found in other object files or libraries. This phase results in an executable or a shared/static library.

    - **Static Linking**: In static linking, the compiled code from libraries (like `spdlog`) is included directly into the final executable. This means that when the program runs, the necessary library code is already bundled within the executable. The advantage of static linking is that the executable is self-contained, but the downside is that the executable file can be larger and any updates to the library require recompilation.

    - **Shared (Dynamic) Linking**: In shared linking, the library code is not embedded within the executable. Instead, the executable relies on external shared libraries (e.g., `.so` on Linux, `.dll` on Windows) that are loaded at runtime. This keeps the executable smaller and allows for shared usage of libraries across multiple programs, but it requires the library to be present at runtime.

4. **Assembly**: After linking, the final machine code is produced and can be executed directly on the machine.

### Header Files vs. Library Files

In C++, there are two key parts of a library:
- **Header Files (`.h`)**: These files define the interface of the library, including the functions, classes, and data types that you can use. They are included in your source code using `#include`.
- **Library Files**: These contain the actual implementations of the functions and classes declared in the headers. Library files can either be:
  - **Static Libraries** (`.a`, `.lib`): The library's code is bundled into your program during the linking phase. Once linked, the library's code is part of the final executable.
  - **Shared Libraries** (`.so`, `.dll`): The library's code is separate from the executable, and it is loaded dynamically at runtime. This allows multiple programs to use the same library without each program including a copy of the library's code.

### `include_directories()` vs. `target_link_libraries()`

- **`include_directories()`**: Tells the compiler where to find the header files of the libraries you're using. This ensures that functions, classes, and other elements declared in the headers are available during the compilation process.
  
- **`target_link_libraries()`**: Tells the linker which libraries your program depends on during the linking phase. This is required to ensure that the actual code from libraries (like `spdlog`, `GLFW`, or `GLM`) is included in your final executable.

While **`include_directories()`** ensures the compiler can find headers for the library, **`target_link_libraries()`** ensures the compiled code from the libraries is linked with your program during the linking phase.


### **Next Steps**
We’ll continue expanding this document with detailed descriptions for each engine component as development progresses. For now, the focus is on implementing foundational systems like layers, events, and shaders.