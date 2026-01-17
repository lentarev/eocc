# eocc engine

A minimal, educational C++/OpenGL game engine built from scratch.  
Designed for learning graphics programming, engine architecture, and real-time simulation.

You might wonder: why the name "eocc"?  
It stands for **"Epoch of Clashes Client"** — the title of the game I originally started (and continue to develop).  

Initially, the project was structured as the client-side component of that game. However, as the codebase grew, I made a deliberate decision to separate the core engine functionality from the game-specific logic.  

Thus, **eocc** evolved into a standalone engine — while still carrying the legacy of its origins.

## 🚀 Features

- **Scene management** – switch between scenes (e.g., Menu → Level)
- **Mesh & Material system** – data-driven rendering with PBR-ready structure
- **Fixed timestep game loop** – deterministic physics and animations
- **Camera with perspective projection** – proper 3D view and aspect ratio handling
- **GLFW + GLAD backend** – cross-platform windowing and OpenGL context
- **Modern C++** – RAII, smart pointers, no raw `new`/`delete`

## 📂 Project Structure

The engine is structured as a header-only compatible C++ library with a clear separation between the core engine and the demo application:

```text
eocc/
├── demo/                 # Demo application (game example)
│   ├── main.cpp          # Entry point
│   ├── scenes/           # Game-specific scenes (Menu, Level1, etc.)
│   └── shaders/          # GLSL shaders for the demo
│
├── include/eocc/         # Public API headers (installable)
│   ├── Engine.h
│   ├── base/
│   ├── camera/
│   ├── renderer/
│   ├── scene/
│   └── system/
│
└── src/eocc/             # Engine implementation
    ├── Engine.cpp
    ├── base/
    ├── camera/
    ├── renderer/
    └── system/
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