# EOCC Engine

A minimal, educational C++/OpenGL game engine built from scratch.  
Designed for learning graphics programming, engine architecture, and real-time simulation.

## 🚀 Features

- **Scene management** – switch between scenes (e.g., Menu → Level)
- **Mesh & Material system** – data-driven rendering with PBR-ready structure
- **Fixed timestep game loop** – deterministic physics and animations
- **Camera with perspective projection** – proper 3D view and aspect ratio handling
- **GLFW + GLAD backend** – cross-platform windowing and OpenGL context
- **Modern C++** – RAII, smart pointers, no raw `new`/`delete`

## 📂 Project Structure

```text
src/
├── engine/
│   ├── base/          # Logger, Transform, etc.
│   ├── camera/        # Camera class
│   ├── renderer/      # Graphics conductor
│   ├── scene/         # SceneBase and managers
│   └── system/        # Window, Input
├── game/
│   └── scenes/        # Menu, Level1
└── main.cpp
```

## 🛠️ Build

Prerequisites:
- CMake ≥ 3.28
- Ninja (recommended)
- C++20 compiler (GCC 10+, Clang 12+)
- OpenGL development headers

On Ubuntu 24.04:
```bash
sudo apt install cmake ninja-build libgl1-mesa-dev xorg-dev
```

```bash
git clone https://github.com/lentarev/eocc.git
cd eocc
mkdir build && cd build
cmake .. -G Ninja
ninja
./eocc
```

## 📜 License

Copyright (c) 2026 Egor Lentarev.  
Released under the [MIT License](LICENSE).