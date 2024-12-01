# stb

The `stb` library included in this project is a lightweight, single-header library designed for a variety of graphics-related tasks. In this project, we specifically use `stb_image.h` to handle image loading. The library was obtained from the official [stb GitHub repository](https://github.com/nothings/stb).

## Integration in the Project

1. **Header-Only Design**:
   - `stb_image.h` is a header-only library, meaning it doesn't require separate compilation or linking for most of its functionality.
   - However, to enable its implementation, we define the `STB_IMAGE_IMPLEMENTATION` macro in the `stb_image.cpp` file included in this project.

2. **CMake Configuration**:
   - The `stb` library is directly included in the build process using the following lines in the `CMakeLists.txt`:

     **Include Directory**:
     ```cmake
     target_include_directories(Universe PUBLIC 
         ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb
     )
     ```

     This ensures that `stb_image.h` is available for inclusion in your project files.

     **Source File**:
     ```cmake
     target_sources(Universe PRIVATE 
         ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb/stb_image.cpp
     )
     ```

     This adds the `stb_image.cpp` file, where the implementation of `stb_image.h` is defined, to the build process.

3. **How It Works**:
   - To use `stb_image` in your code, simply include the header file:
     ```cpp
     #include "stb_image.h"
     ```
   - The `stb_image.cpp` file contains the required implementation. This setup ensures that the library integrates seamlessly into the engine.

4. **Image Loading**:
   - `stb_image.h` supports loading various image formats, including PNG, JPEG, BMP, TGA, and more.
   - It automatically handles tasks like loading pixel data and decoding images, making it ideal for game engine use.

## Notes for Developers

- **No External Build Needed**:
  - Unlike libraries such as `glfw` or `spdlog`, `stb` does not require external compilation or linking. Simply including its source file is sufficient.

- **Updating the Library**:
  - If you need to update `stb_image.h`, download the latest version from the [stb GitHub repository](https://github.com/nothings/stb), and replace the existing `stb_image.h` file.

- **Supported Formats**:
  - `stb_image` supports common formats like PNG, JPEG, BMP, and TGA. Refer to the documentation in `stb_image.h` for additional details.

- **Flipping Images**:
  - By default, OpenGL's texture coordinate system assumes the origin is at the bottom-left, while most image formats have the origin at the top-left. Use the following function to flip images vertically during loading:
    ```cpp
    stbi_set_flip_vertically_on_load(1);
    ```

## Summary

The `stb` library is simple, efficient, and requires minimal integration:
- Include the `vendor/stb` directory in your include paths.
- Add `stb_image.cpp` to your project's source files.
- Use `stb_image.h` to load and decode image files as needed.

This setup ensures `stb_image.h` is fully integrated with the engine while remaining easy to maintain and update.