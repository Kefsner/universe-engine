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