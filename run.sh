#!/bin/bash

if cd build/sandbox; then
    ./Sandbox
    cd ../..
else
    echo "Error: Could not find Sandbox directory. Make sure the build is complete."
    exit 1
fi
