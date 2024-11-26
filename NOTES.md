# Notes and Tutorials

This document contains detailed notes on how various aspects of the Universe Engine work, as well as tutorials and explanations of core concepts.

## Build Process and Linking in C++

When developing in C++, the build process is typically divided into several phases:

1. **Preprocessing**: The compiler processes your source code, handling directives like `#include` and `#define`. This phase results in an intermediate code that includes all headers and macro expansions.

2. **Compilation**: The compiler takes the preprocessed source code and translates it into **object files** (`.o` or `.obj`), which are machine-readable files containing the compiled code but not yet linked into an executable.

3. **Linking**: The linker is responsible for combining the compiled object files and linking them with any required libraries (static or shared). It resolves external references in the object files to the actual implementations found in other object files or libraries. This phase results in an executable or a shared/static library.

   - **Static Linking**: In static linking, the compiled code from libraries (like `spdlog`) is included directly into the final executable. This means that when the program runs, the necessary library code is already bundled within the executable. The advantage of static linking is that the executable is self-contained, but the downside is that the executable file can be larger and any updates to the library require recompilation.

   - **Shared (Dynamic) Linking**: In shared linking, the library code is not embedded within the executable. Instead, the executable relies on external shared libraries (e.g., `.so` on Linux, `.dll` on Windows) that are loaded at runtime. This keeps the executable smaller and allows for shared usage of libraries across multiple programs, but it requires the library to be present at runtime.

4. **Assembly**: After linking, the final machine code is produced and can be executed directly on the machine.

## Header Files vs. Library Files

In C++, there are two key parts of a library:

- **Header Files (`.h`, `.hpp`)**: These files define the interface of the library, including the functions, classes, and data types that you can use. They are included in your source code using `#include`.

- **Library Files**:

  - **Static Libraries** (`.a`, `.lib`): Contain the compiled code of the library. During the linking phase, this code is combined with your program's code to create a single executable.

  - **Shared Libraries** (`.so`, `.dll`): Contain the compiled code but are not included in the executable. Instead, they are loaded at runtime.

## `include_directories()` vs. `target_link_libraries()` in CMake

- **`include_directories()`**: Tells the compiler where to find the header files of the libraries you're using. This ensures that functions, classes, and other elements declared in the headers are available during the compilation process.

- **`target_link_libraries()`**: Tells the linker which libraries your program depends on during the linking phase. This is required to ensure that the actual code from libraries (like `spdlog`, `GLFW`, or `GLM`) is included in your final executable.

While **`include_directories()`** ensures the compiler can find headers for the library, **`target_link_libraries()`** ensures the compiled code from the libraries is linked with your program during the linking phase.

## Tutorials and Further Reading

- **Setting Up the Development Environment**: Detailed instructions on configuring your environment for building and running the Universe Engine.

- **Understanding the Rendering Pipeline**: An in-depth look at how the engine processes and renders graphics.

- **Implementing Custom Layers**: How to create and integrate your own layers into the engine.

- **Event Handling Mechanism**: Explanation of the event system and how to use it for input handling and custom events.

- **Working with Shaders**: A guide to writing and integrating shaders within the engine.

## Contributing to the Engine

We welcome contributions! Here are some ways you can help:

- **Reporting Bugs**: If you find any issues, please open an issue on the GitHub repository with detailed information.

- **Adding Features**: Feel free to fork the repository, add new features, and submit a pull request.

- **Improving Documentation**: Help us expand and refine the documentation and tutorials.

## Contact and Support

For questions or support, please contact the project maintainer at [your-email@example.com](mailto:your-email@example.com).

## **Setting Up Dependencies**

To build and run the engine on **Ubuntu Noble 24.04 LTS**, you need to install several dependencies. Below is the complete list of required packages with a brief description of each.

---

### **Installing Dependencies**

1. **Update the Package Manager**  
   Ensure your system's package list is up to date:
   ```bash
   sudo apt update
   ```

2. **Essential OpenGL and Mesa Libraries**  
   These libraries are required for rendering and OpenGL functionality:
   ```bash
   sudo apt install -y mesa-common-dev libglu1-mesa-dev
   ```
   - **`mesa-common-dev`**: Development files for Mesa, an open-source implementation of OpenGL.
   - **`libglu1-mesa-dev`**: Development files for the GLU (OpenGL Utility Library).

3. **X11 and Input Libraries**  
   These libraries provide support for windowing and input handling:
   ```bash
   sudo apt install -y libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
   ```
   - **`libx11-dev`**: Development files for X11, the core protocol for Linux graphical interfaces.
   - **`libxrandr-dev`**: Adds support for screen resizing and rotation.
   - **`libxinerama-dev`**: Provides multi-monitor support.
   - **`libxcursor-dev`**: Cursor management and theme support.
   - **`libxi-dev`**: Input handling, such as mouse and keyboard support.

4. **Wayland Libraries**  
   Necessary for Wayland support and modern display servers:
   ```bash
   sudo apt install -y libwayland-dev wayland-protocols
   ```
   - **`libwayland-dev`**: Development files for Wayland, a modern replacement for X11.
   - **`wayland-protocols`**: Definitions of standard Wayland protocols.

5. **Keyboard Input Handling Libraries**  
   Required for keyboard functionality in GLFW:
   ```bash
   sudo apt install -y libxkbcommon-dev
   ```
   - **`libxkbcommon-dev`**: Keyboard handling library for X11 and Wayland.

6. **`libdecor` for Window Decorations**  
   These packages enable window decorations for Wayland environments:
   ```bash
   sudo apt install -y libdecor-0-0 libdecor-0-dev libdecor-0-plugin-1-gtk
   ```
   - **`libdecor-0-0`**: The main library for Wayland client-side decorations.
   - **`libdecor-0-dev`**: Development files for building applications using `libdecor`.
   - **`libdecor-0-plugin-1-gtk`**: A GTK plugin for `libdecor` to match the GTK theme.

---

### **Complete Installation Command**
To install all dependencies in one go:
```bash
sudo apt update && sudo apt install -y \
    mesa-common-dev libglu1-mesa-dev \
    libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev \
    libxkbcommon-dev libwayland-dev wayland-protocols \
    libdecor-0-0 libdecor-0-dev libdecor-0-plugin-1-gtk
```

---

### **Building the Project**
Once the dependencies are installed, follow these steps to build and run the project:

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-repository/universe-engine.git
   cd universe-engine
   ```

2. **Run the Build Script**:
   ```bash
   ./build.sh
   ```

3. **Run the Sandbox Application**:
   ```bash
   ./run.sh
   ```

---

### **Notes**
- If you encounter missing package errors, ensure you're using **Ubuntu Noble 24.04 LTS** or a compatible version. For older versions, some packages (like `libdecor`) might not be available and may require manual installation or upgrading your OS.
- Ensure that your system has the latest graphics drivers installed for optimal performance.