//
// Created by Egor Lentarev on 03.01.2026.
//

#ifndef EOCC_ENGINE_H
#define EOCC_ENGINE_H

#include <memory>
#include <engine/scene/base/SceneBase.h>

// Предварительное объявление классов
class Window;
class Shader;
class Renderer;

class Engine {
public:
    Engine();
    ~Engine();

    // Запуск главного цикла
    void run();

    // Обработчик клавиш (будет вызываться GLFW)
    void onKey(int key, int scancode, int action, int mods);

private:
    const double TARGET_FPS = 60.0;
    const double FIXED_DELTA_TIME = 1.0 / TARGET_FPS;  // 60 UPS (updates per second)

    // Объявляем подсистемы движка

    // 1. Оконная подсистема
    std::unique_ptr<Window> _window;

    // 2. Подиситема Shader
    std::unique_ptr<Shader> _shader;

    // 3. Подиситема Renderer
    std::unique_ptr<Renderer> _renderer;

    // 4. Подсистема сцен
    std::unique_ptr<SceneBase> _currentScene;
};

#endif  // EOCC_ENGINE_H