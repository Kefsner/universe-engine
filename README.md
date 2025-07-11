# Universe Engine

A simple game engine prototype built with C++, Premake5, and third-party libraries like GLFW and stb.

## 🚀 Getting Started

These instructions will help you set up and build the project on Windows using MinGW and Premake.

## ✅ Prerequisites

### 1. Clone the repository

```bash
git clone https://github.com/your-username/universe-engine.git
cd universe-engine
```

### 2. Initialize submodules

```bash
git submodule update --init --recursive
```

## 🔧 Install MinGW

To compile the project using GCC, you'll need to install MinGW-w64.

1. Go to: [https://www.mingw-w64.org/downloads/](https://www.mingw-w64.org/downloads/)
2. You'll be redirected to the GitHub release page:
   [niXman/mingw-builds-binaries](https://github.com/niXman/mingw-builds-binaries/releases)
3. Download this build (tested and working):

   ```
   x86_64-15.1.0-release-posix-seh-ucrt-rt_v12-rev0
   ```
4. Extract it and move the folder to:

   ```
   C:\mingw64
   ```
5. Add the following to your system `PATH`:

   ```
   C:\mingw64\bin
   ```

To verify:

```powershell
gcc --version
```

## 🛠️ Build Steps

### 1. Run `devtool.bat` to generate project files

```bash
devtool.bat --glfw    # Generate GLFW project files
devtool.bat --stb     # Generate stb project files
```

> On Linux/macOS, use `devtool.sh` (may not work yet due to Windows-only Premake binary)

### 2. Build the project

```bash
devtool.bat --build
# or
devtool.bat -b
```

## 📂 Output

The compiled binary will be located in:

```
build/bin/Debug/Sandbox/Sandbox.exe
```

## 🧪 Run the project

Once built, you can run the engine with:

```bash
devtool.bat --run
```

## 📌 Notes

* Currently uses the `gmake` backend for Premake (Visual Studio generation is not yet configured).
* For full cross-platform support, consider integrating the Linux-compatible Premake binary later.
