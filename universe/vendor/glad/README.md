# Glad

Glad was downloaded from [https://glad.dav1d.de/](https://glad.dav1d.de/).

- **API Version**: OpenGL 4.6
- **Profile**: Core
- **Extensions**: None

In this project, `glad` is included by directly adding its source file (`glad.c`) into the engine’s build process. No separate library or linking configuration is needed; simply including the source file and headers in the project is sufficient to load OpenGL functions up to version 4.6.


Had to include

```lua
   filter { "files:vendor/glad/src/glad.c" }
        flags { "NoPCH" }
```

in the premake5.lua file to get it to compile.