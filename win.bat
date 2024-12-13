@echo off

set "ACTION=--run"

echo %1

if not "%1"=="" (
    if "%1"=="-b" (
        set "ACTION=--build"
    ) else if "%1"=="--build" (
        set "ACTION=--build"
    ) else if "%1"=="-br" (
        set "ACTION=--build-run"
    ) else if "%1"=="--build-run" (
        set "ACTION=--build-run"
    ) else if "%1"=="-R" (
        set "ACTION=--rebuild"
    ) else if "%1"=="--rebuild" (
        set "ACTION=--rebuild"
    ) else if "%1"=="-rr" (
        set "ACTION=--rebuild-run"
    ) else if "%1"=="--rebuild-run" (
        set "ACTION=--rebuild-run"
    ) else if "%1"=="-r" (
        set "ACTION=--run"
    ) else if "%1"=="--run" (
        set "ACTION=--run"
    ) else if "%1"=="-h" (
        set "ACTION=--help"
    ) else if "%1"=="--help" (
        set "ACTION=--help"
    ) else (
        echo Unknown option: %1
        call :help
        exit /b 1
    )
)

REM Handle actions
if "%ACTION%"=="--rebuild" (
    echo Performing full rebuild...
    rmdir /s /q build
    mkdir build
    call :build
    exit /b %ERRORLEVEL%
)

if "%ACTION%"=="--rebuild-run" (
    echo Performing full rebuild...
    rmdir /s /q build
    mkdir build
    call :build
    if errorlevel 1 exit /b %ERRORLEVEL%
    call :run
    exit /b %ERRORLEVEL%
)

if "%ACTION%"=="--build" (
    if not exist build mkdir build
    call :build
    exit /b %ERRORLEVEL%
)

if "%ACTION%"=="--build-run" (
    if not exist build mkdir build
    call :build
    if errorlevel 1 exit /b %ERRORLEVEL%
    call :run
    exit /b %ERRORLEVEL%
)

if "%ACTION%"=="--run" (
    if not exist build\sandbox\Sandbox.exe (
        echo Sandbox.exe not found. Build the project first.
        exit /b 1
    )
    call :run
    exit /b %ERRORLEVEL%
)

REM Subroutines

:build
set "VENDOR_DIR=universe/vendor"
if not exist "%VENDOR_DIR%\spdlog\CMakeLists.txt" (
    echo Missing spdlog submodule. Please run: git submodule update --init --recursive
    exit /b 1
)
if not exist "%VENDOR_DIR%\glfw\CMakeLists.txt" (
    echo Missing glfw submodule. Please run: git submodule update --init --recursive
    exit /b 1
)

cd build
cmake .. -G "MinGW Makefiles"
if errorlevel 1 (
    echo CMake configuration failed. Ensure all dependencies are properly initialized.
    cd ..
    exit /b 1
)

cmake --build .
if errorlevel 1 (
    echo Build failed. Check the errors above.
    cd ..
    exit /b 1
)

cd ..
exit /b 0

:run
.\build\editor\Editor.exe
exit /b 0

:help
echo Usage: win.bat [option]
echo Options:
echo   -b or --build       Build the project
echo   -br or --build-run  Build the project and run
echo   -r or --rebuild     Rebuild the project
echo   -rr or --rebuild-run Rebuild the project and run
echo   -R or --run         Run the project
echo   -h or --help        Display this help message
exit /b 0