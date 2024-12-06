# Universe Engine

## Introduction

The Universe Engine is a custom-built, cross-platform game engine. This project is primarily inspired by [Cherno's Hazel engine](https://github.com/TheCherno/Hazel), whose development process is documented in [Cherno's Game Engine Series](https://www.youtube.com/watch?v=JxIZbV_XjAs&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT) in an outstandingly educational manner (at least for me).

## Project Goals

This engine is a practice project that merges my interests in game design and software development, serving as my entry point in both c++ and graphics programming. Therefore, its early stages will inevitably closely resemble Hazel's structure and functionalities. As I evolve into these concepts, I intend to add unique features and personal touches to differentiate it from its inspiration. The ultimate aim is to use this engine to develop a series of games based on ideas I am excited to bring to life.

## Documentation

I am documenting the development process extensively to create a comprehensive journal that might help others learning similar skills. These notes can be found under [JOURNAL.md](./docs/JOURNAL.md). This journal includes descriptions of each class and functionality, explaining their necessity and operation. Additional notes on general graphics programming concepts will also be included, complete with references (or at least that's the plan).

In future phases of the project, I plan to compile this documentation into a formal guide that could assist others in using this engine for their own game development projects.

## Development

Active development occurs in the `develop` branch, with the `main` branch hosting the most stable version of the engine. Feature-specific branches may also be created off `develop` as needed for testing new functionalities or fixes.

## Current Features

- Windows and Unix build scripts
- Basic systems for layers, events, rendering, shaders, cameras, input, and ImGui integration
- Basic 2D rendering capabilities

## Planned Features

- 2D physics system
- Animated 2D rendering capabilities

## Installation Guide

This guide provides instructions on how to build and run the project using the provided `win.bat` for Windows and `unix.sh` for Unix/Linux systems.

Ensure that you have `cmake` installed on your system and that all necessary submodules are initialized. Use the following command to initialize submodules, after cloning the repository:

```bash
git submodule update --init --recursive
```

Depending on you operating system, you can use either the `win.bat` script for Windows or the `unix.sh` script for Unix/Linux systems to manage the build process. Both scripts have the same options, whose usage is outlined below.

- **-b, --build**: Compile the latest changes.
- **-br, --build-run**: Compile the latest changes and then run the executable.
- **-r, --rebuild**: Remove all previous build files and recompile the project from scratch.
- **-rr, --rebuild-run**: Rebuild the entire project from scratch and run the executable.
- **-R, --run**: Run the executable without compiling. Ensure the build is up-to-date.
- **-h, --help**: Display help information outlining these options.

### Windows

To build the project on Windows, open a command prompt in the project's root directory and run the following command:

```cmd
.\win.bat -br
```

### Unix/Linux

To build the project on Unix/Linux systems, open a terminal in the project's root directory and run the following command:

```bash
./unix.sh -br
```

## Contributors

- **Kesley Raimundo** - *Initial Development* - [Kefsner](https://github.com/Kefsner)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
