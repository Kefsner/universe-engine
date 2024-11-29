#!/bin/bash

ACTION=""

# Parse command-line argument
if [ -n "$1" ]; then
    case "$1" in
        -b|--build)
            ACTION="--build"
            ;;
        -br|--build-run)
            ACTION="--build-run"
            ;;
        -r|--rebuild)
            ACTION="--rebuild"
            ;;
        -rr|--rebuild-run)
            ACTION="--rebuild-run"
            ;;
        -R|--run)
            ACTION="--run"
            ;;
        -h|--help)
            ACTION="--help"
            ;;
        *)
            echo "Unknown option: $1"
            show_help
            exit 1
            ;;
    esac
else
    ACTION="--help"
fi

# Handle actions
case "$ACTION" in
    --rebuild)
        echo "Performing full rebuild..."
        rm -rf build
        mkdir build
        build_project || exit $?
        ;;
    --rebuild-run)
        echo "Performing full rebuild..."
        rm -rf build
        mkdir build
        build_project || exit $?
        run_project || exit $?
        ;;
    --build)
        [ ! -d build ] && mkdir build
        build_project || exit $?
        ;;
    --build-run)
        [ ! -d build ] && mkdir build
        build_project || exit $?
        run_project || exit $?
        ;;
    --run)
        if [ ! -f build/sandbox/Sandbox ]; then
            echo "Sandbox executable not found. Build the project first."
            exit 1
        fi
        run_project || exit $?
        ;;
    --help)
        show_help
        ;;
esac

exit 0

# Subroutines

build_project() {
    VENDOR_DIR="universe/vendor"

    if [ ! -f "$VENDOR_DIR/spdlog/CMakeLists.txt" ]; then
        echo "Missing spdlog submodule. Please run: git submodule update --init --recursive"
        return 1
    fi
    if [ ! -f "$VENDOR_DIR/glfw/CMakeLists.txt" ]; then
        echo "Missing glfw submodule. Please run: git submodule update --init --recursive"
        return 1
    fi

    cd build || return 1
    cmake .. -G "Unix Makefiles"
    if [ $? -ne 0 ]; then
        echo "CMake configuration failed. Ensure all dependencies are properly initialized."
        cd ..
        return 1
    fi

    cmake --build .
    if [ $? -ne 0 ]; then
        echo "Build failed. Check the errors above."
        cd ..
        return 1
    fi

    cd ..
    return 0
}

run_project() {
    cd build/sandbox || return 1
    ./Sandbox
    cd ../..
    return 0
}

show_help() {
    echo "Usage: $(basename "$0") [option]"
    echo "Options:"
    echo "  -b or --build       Build the project"
    echo "  -br or --build-run  Build the project and run"
    echo "  -r or --rebuild     Rebuild the project"
    echo "  -rr or --rebuild-run Rebuild the project and run"
    echo "  -R or --run         Run the project"
    echo "  -h or --help        Display this help message"
}
