#!/bin/bash

set -e

# Default action
ACTION="--run"

# Parse parameter
if [ "$#" -ge 1 ]; then
    case $1 in
        --build|-b)
            ACTION="--build"
            ;;
        --rebuild|-r)
            ACTION="--rebuild"
            ;;
        --run|-R)
            ACTION="--run"
            ;;
        *)
            echo "Invalid option: $1"
            echo "Usage: ./unix.sh [--build|-b|--rebuild|-r|--run|-R]"
            exit 1
            ;;
    esac
fi

# Function to build the project
build_project() {
    if [ "$1" == "--rebuild" ]; then
        echo "Performing full rebuild..."
        rm -rf build
    fi

    mkdir -p build
    cd build || exit

    if [ -f CMakeCache.txt ]; then
        echo "Detected existing CMake cache. Running cmake .."
        cmake ..
    else
        echo "No CMake cache found. Running cmake with generator."
        cmake .. -G "Unix Makefiles"
    fi

    if ! cmake --build .; then
        echo "Build failed. Check the errors above."
        exit 1
    fi

    cd ..
}

# Function to run the project
run_project() {
    if cd build/sandbox; then
        ./Sandbox
        cd ../..
    else
        echo "Error: Could not find Sandbox directory. Make sure the build is complete."
        exit 1
    fi
}

# Main script logic
case $ACTION in
    --build)
        build_project
        ;;
    --rebuild)
        build_project "--rebuild"
        ;;
    --run)
        run_project
        ;;
    *)
        echo "Invalid option: $ACTION"
        echo "Usage: ./unix.sh [--build|-b|--rebuild|-r|--run|-R]"
        exit 1
        ;;
esac
