# Universe Engine

The **Universe Engine** is a custom-built game engine project inspired by Cherno's Hazel engine. It aims to provide a solid foundation for 3D game development, with a focus on modularity and ease of use. The current goal is to implement essential features, including delta time/timestep functionality, with plans to expand into a voxel-based world engine similar to Minecraft. The project is structured to support modular development and testing.

---

## Project Structure

The Universe Engine is designed as a modular system, with the core engine built as a library and linked to a sandbox application for testing and experimentation.

### **Core Structure**

- **universe**: The main engine library, which includes core functionality for game development.
  - **src**: Contains the core source files for the engine, such as application management, rendering, and event handling.
  - **vendor**: Third-party libraries used to enhance engine capabilities (e.g., `GLFW`, `GLM`, `spdlog`).
- **sandbox**: A testing environment that serves as a minimal game application to demonstrate and validate the engine's functionality.

### **How It Works**

The `universe` engine is compiled as a static library and linked to the `sandbox` project. The `sandbox` application includes a minimal implementation of game functionality, such as testing layers, events, and rendering, using the core engine.

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

- **Singleton Design**: Ensures only one `Application` instance exists.
- **Layer Management**: Provides a clean interface for adding layers and propagating events through them.
- **Lifecycle Management**: Simplifies game and engine lifecycle management by centralizing core operations.

### **Sandbox**

The `sandbox` application inherits from the `Application` class and acts as a testing ground for engine features. It allows developers to:

- Create and test new layers, events, and rendering techniques without modifying the core engine.
- Experiment with custom game logic while relying on the engine for foundational features like event handling and rendering.

#### Example:

A basic `sandbox` implementation might look like this:

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

The `sandbox` provides a minimal implementation of a game that demonstrates how to use the engine.

---

## Core Elements of the Engine

This section describes the roles and goals of each major element in the game engine, including their general purpose and the specific features implemented in the Universe Engine.

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

---

## External Libraries

The Universe Engine uses several external libraries to simplify development and enhance performance:

### [GLFW](https://github.com/glfw/glfw)

**Description**: A multi-platform library for creating windows, handling input, and managing OpenGL contexts.

**Reason**: GLFW abstracts window creation and input handling, making it easier to develop cross-platform applications. It’s essential for managing the OpenGL context needed for rendering in the engine.

### [GLAD](https://github.com/Dav1dde/glad)

**Description**: GLAD is an OpenGL function loader that handles loading OpenGL functions based on the system’s supported version.

**Reason**: GLAD ensures compatibility with different versions of OpenGL, allowing the engine to use the latest features available on the user’s hardware. It was manually downloaded and included directly in the project.

### [GLM](https://github.com/g-truc/glm)

**Description**: OpenGL Mathematics (GLM) is a mathematics library tailored for graphics applications, providing vector and matrix math functions.

**Reason**: GLM simplifies complex mathematical operations needed for graphics programming, such as transformations and camera management. It is optimized for OpenGL and is crucial for handling 3D mathematics in the engine.

### [spdlog](https://github.com/gabime/spdlog)

**Description**: A fast logging library for C++ applications.

**Reason**: spdlog offers efficient, thread-safe logging. It’s essential for debugging and monitoring, especially in larger projects where tracking execution flow and catching errors early is crucial.

### [ImGui](https://github.com/ocornut/imgui) (Branch: docking)

**Description**: Immediate Mode GUI library for creating real-time, in-app interfaces.

**Reason**: ImGui provides tools for building a real-time debugging and interface layer within the engine, allowing for live parameter adjustments and debugging views. The `docking` branch adds advanced features for multi-window docking, enhancing flexibility during development.

---

## Development Branches

- **main**: Stable release branch.
- **develop**: Active development branch where new features are tested.

---

## Build and Configuration

To build the engine, ensure you have CMake and a compatible C++ compiler installed. Build instructions and configurations are provided in the project files.

---

## Next Steps

We’ll continue expanding this document with detailed descriptions for each engine component as development progresses. For now, the focus is on implementing foundational systems like layers, events, and shaders.

---

## Contribution

Contributions are welcome! Feel free to open issues or submit pull requests to help improve the Universe Engine.

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.