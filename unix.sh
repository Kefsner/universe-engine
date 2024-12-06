#!/bin/bash

ACTION="--run"

if [ "$1" != "" ]; then
    case "$1" in
        "-b" | "--build")
            ACTION="--build"
            ;;
        "-br" | "--build-run")
            ACTION="--build-run"
            ;;
        "-r" | "--rebuild")
            ACTION="--rebuild"
            ;;
        "-rr" | "--rebuild-run")
            ACTION="--rebuild-run"
            ;;
        "-R" | "--run")
            ACTION="--run"
            ;;
        "-h" | "--help")
            ACTION="--help"
            ;;
        *)
            echo "Invalid option: $1"
            exit 1
            ;;
    esac
fi

if [ "$ACTION" == "--help" ]; then
    echo "Usage: $0 [OPTION]"
    echo "Options:"
    echo "  -b, --build         Build the project"
    echo "  -br, --build-run    Build the project and run it"
    echo "  -r, --rebuild       Rebuild the project"
    echo "  -rr, --rebuild-run  Rebuild the project and run it"
    echo "  -R, --run           Run the project"
    echo "  -h, --help          Display this help message"
    exit 0
fi

function build() {
    echo "Building the project..."
    VENDOR_DIR="universe/vendor"
    if [ ! -f "$VENDOR_DIR/spdlog/CMakeLists.txt" ]; then
        echo "Missing spdlog submodule. Please run: git submodule update --init --recursive"
        exit 1
    fi
    if [ ! -f "$VENDOR_DIR/glfw/CMakeLists.txt" ]; then
        echo "Missing glfw submodule. Please run: git submodule update --init --recursive"
        exit 1
    fi

    cd build
    cmake .. -G "Unix Makefiles"
    if [ $? -ne 0 ]; then
        echo "CMake configuration failed. Ensure all dependencies are properly initialized."
        exit 1
    fi

    cmake --build .
    if [ $? -ne 0 ]; then
        echo "Build failed."
        exit 1
    fi

    cd ..
}

function rebuild() {
    echo "Rebuilding the project..."
    rm -rf build
    mkdir build
    build
}

function run() {
    echo "Running the project..."
    cd build/sandbox
    ./Sandbox
    cd ../..
}


case "$ACTION" in
    "--build")
        build
        ;;
    "--build-run")
        build
        run
        ;;
    "--rebuild")
        rebuild
        ;;
    "--rebuild-run")
        rebuild
        run
        ;;
    "--run")
        run
        ;;
esac
