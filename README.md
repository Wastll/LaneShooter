# LaneShooter

A Raylib C semi-3D pixel art shooter game

## Requirements
- [Raylib 5.5](https://www.raylib.com/)
- [CMake](https://cmake.org/)
- C compiler (GCC/Clang on Linux, MSVC on Windows)

## Build
### Windows
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
build/lane_shooter.exe
```
### Linux
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
build/lane_shooter
```
