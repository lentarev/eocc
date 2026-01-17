[🇷🇺 Русский](../ru/) | [🇬🇧 English](./)

# eocc engine

A lightweight, clear, and C++-centric 3D game engine for developers who value **control**, **understanding**, and **simplicity**.

eocc is not a black box. It’s a tool built to be read, understood, and extended — from shaders to scene management, all in modern C++.

## ✨ Key Features

- **Pure C++20** with RAII and smart pointers
- **Modular scene system** (`SceneBase`, `Menu`, `Level1`)
- **Shader resource management** per scene
- **OpenGL core profile** (no legacy code)
- **No external dependencies** beyond GLFW, GLAD, and GLM
- **Header-only compatible** public API

## 🚀 Getting Started

```bash
git clone https://github.com/egorlentarev/eocc.git
cd eocc
cmake -B build -G Ninja
cmake --build build
./build/eocc_demo