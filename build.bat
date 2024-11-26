@echo off

rmdir /s /q build
mkdir build
cd build
cmake ..
cmake --build .
cd ..
