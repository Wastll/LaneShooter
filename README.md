# LaneShooter - Baseline

This branch contains the most generic, genre-agnostic version of the core game.
No shooter-specific mechanics are implemented here.

It serves as a stable baseline for future forks, experiments, or as a recovery point
before major gameplay decisions were introduced.

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
