//
// Created by Egor Lentarev on 03.01.2026.
//

#ifndef VECTHAR_ENGINE_H
#define VECTHAR_ENGINE_H

#include <memory>
#include <vecthar/scene/base/SceneBase.h>

namespace vecthar {

// Forward declaration of classes
class Window;
class Renderer;

class Engine {
public:
    Engine();
    ~Engine();

    // Starts and runs the main application loop.
    void run();

    // Handles keyboard input (called via GLFW callback).
    void onKey(int key, int scancode, int action, int mods);

    // Set current scene
    void setCurrentScene(std::unique_ptr<SceneBase> scene);

private:
    const double TARGET_FPS = 60.0;
    const double FIXED_DELTA_TIME = 1.0 / TARGET_FPS;  // Fixed timestep: 60 updates/sec

    // Subsystems

    std::unique_ptr<Window> _window;  ///< Manages the application window and input.

    std::unique_ptr<Renderer> _renderer;  ///< Handles graphics rendering.

    std::unique_ptr<SceneBase> _currentScene;  ///< Active game scene.
};

}  // namespace vecthar

#endif  // VECTHAR_ENGINE_H