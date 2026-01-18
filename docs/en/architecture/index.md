[<= Back](../) 

# Architecture

The **eocc** engine is built around three core principles:

1. **Transparency** — no hidden systems; everything can be read and understood.
2. **Modularity** — every component (scene, renderer, camera) is replaceable.
3. **Control** — the developer decides what and how to render, with no "magic".

## Core Components

### `Engine`
The central coordinator that:
- Creates a window via GLFW,
- Manages the current scene,
- Runs the main loop with a fixed timestep (`fixed timestep`),
- Provides access to subsystems (input, rendering).

### `SceneBase`
An abstract base class for all scenes.  
Each scene (menu, level, settings) inherits from it and implements:
- `init()` — one-time initialization,
- `update(float dt, float time)` — game logic and physics,
- `render()` — drawing via the `Renderer`.

> Scenes are fully isolated: resources (shaders, meshes) are loaded and released within them.

### `Renderer`
Responsible for:
- Clearing the framebuffer,
- Binding shaders,
- Submitting geometry to the GPU.

> eocc has no render graph or complex pipelines — only direct OpenGL calls. This gives you full control.

### `Camera`
Implements:
- Perspective projection,
- View matrix,
- Automatic adaptation to window resize events.

## Application Lifecycle

1. `main()` creates an `Engine` instance.
2. `Engine` initializes GLFW, GLAD, and the window.
3. The initial scene is set (e.g., `Menu`).
4. The main loop starts:
   - Input handling,
   - Fixed-step `update` (for physics),
   - Variable-rate `render` (for graphics).
5. When switching scenes, the old one releases its resources, and the new one initializes.

## Project Structure

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

To use eocc in your own project:
1. Copy `include/eocc/` into your project,
2. Link against `libeocc_engine.a` (or include the source files directly),
3. Inherit from `SceneBase` and pass an instance to `Engine::setCurrentScene()`.

## Example: Creating a Scene

```cpp
class MyScene : public eocc::SceneBase {
public:
    void init(eocc::Engine* engine) override {
        // Load shaders, meshes, etc.
    }

    void update(float dt, float t) override {
        // Game logic
    }

    void render() override {
        engine->getRenderer().submit(mesh, shader);
    }
};

// В main.cpp:

int main() {
    // 1. Global Initialization (GLFW)
    if (!glfwInit()) {
        return -1;
    }

    try {
        const auto engine = std::make_unique<eocc::Engine>();
        engine->setCurrentScene(std::make_unique<Menu>());
        engine->run();

    } catch (const std::exception& e) {
        eocc::Logger::log(1, "Fatal error: %s\n", e.what());
        return -1;
    }

    // Freeing up all resources associated with GLFW
    glfwTerminate();

    return 0;
}
```