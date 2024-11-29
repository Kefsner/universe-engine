@echo off

REM Default action
set ACTION=--run

REM Check for parameter
if not "%1"=="" (
    if "%1"=="-b" set ACTION=--build
    if "%1"=="-r" set ACTION=--rebuild
    if "%1"=="-R" set ACTION=--run
    if not "%ACTION%"=="--run" if not "%ACTION%"=="--build" if not "%ACTION%"=="--rebuild" (
        echo Invalid option: %1
        echo Usage: win.bat [--build|-b|--rebuild|-r|--run|-R]
        exit /b 1
    )
)

REM Handle "rebuild"
if "%ACTION%"=="--rebuild" (
    echo Performing full rebuild...
    rmdir /s /q build
    mkdir build
    goto :build
)

REM Handle "build"
if "%ACTION%"=="--build" (
    if not exist build (
        mkdir build
    )
    goto :build
)

REM Handle "run"
if "%ACTION%"=="--run" (
    if not exist build\sandbox\Sandbox.exe (
        echo Sandbox.exe not found. Running build process...
        goto :build
    )
    cd build\sandbox
    Sandbox.exe
    cd ..\..
    exit /b 0
)

:build
REM Check if vendor submodules are properly initialized
set VENDOR_DIR=universe/vendor
if not exist %VENDOR_DIR%\spdlog\CMakeLists.txt (
    echo Missing spdlog submodule. Please run: git submodule update --init --recursive
    exit /b 1
)
if not exist %VENDOR_DIR%\glfw\CMakeLists.txt (
    echo Missing glfw submodule. Please run: git submodule update --init --recursive
    exit /b 1
)

REM Navigate to the build directory
cd build

REM Configure with CMake
if exist CMakeCache.txt (
    echo Detected existing CMake cache. Running cmake ..
    cmake ..
) else (
    echo No CMake cache found. Running cmake with generator MinGW Makefiles.
    cmake .. -G "MinGW Makefiles"
)

REM Check for CMake errors
if errorlevel 1 (
    echo CMake configuration failed. Ensure all dependencies are properly initialized.
    exit /b 1
)

REM Build the project
cmake --build .

REM Check for build errors
if errorlevel 1 (
    echo Build failed. Check the errors above.
    exit /b 1
)

REM Return to the parent directory
cd ..
if "%ACTION%"=="--run" (
    goto :run
)
exit /b 0
