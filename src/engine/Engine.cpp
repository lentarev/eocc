//
// Created by Egor Lentarev on 03.01.2026.
//

#include "Engine.h"

#include <engine/system/window/Window.h>
#include <engine/assets/shader/Shader.h>
#include <engine/renderer/Renderer.h>
#include <game/scenes/menu/Menu.h>
#include <game/scenes/level1/Level1.h>

#include <GLFW/glfw3.h>
#include <iostream>

// --- Статический коллбэк (только здесь, только в .cpp) ---
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    if (engine) {
        engine->onKey(key, scancode, action, mods);
    }
}

/**
 * Constructor
 */
Engine::Engine() {
    // 1. Оконная подсистема
    _window = std::make_unique<Window>(1280, 1024, "OpenGL Test Window");

    // 2. Подиситема Shader
    _shader = std::make_unique<Shader>();

    // 3. Подиситема Renderer
    _renderer = std::make_unique<Renderer>();

    // Передаём указатель на этот Engine в окно GLFW
    glfwSetWindowUserPointer(_window->getGLFWWindow(), this);

    // Устанавливаем callback
    glfwSetKeyCallback(_window->getGLFWWindow(), keyCallback);

    // Начинаем с меню
    _currentScene = std::make_unique<Menu>();
}

/**
 * Destructor
 */
Engine::~Engine() {}

/**
 * Обработчик клавиш
 */
void Engine::onKey(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        std::cout << "KEY_SPACE" << std::endl;

        // Переключаем на игровую сцену
        _currentScene = std::make_unique<Level1>();
    }
}

/**
 * Запуск главного цикла
 */
void Engine::run() {
    double lastTime = glfwGetTime();
    double accumulator = 0.0;

    // LOOP
    while (!glfwWindowShouldClose(_window->getGLFWWindow())) {
        const double currentTime = glfwGetTime();
        double frameTime = currentTime - lastTime;

        if (frameTime > 0.25) {
            frameTime = 0.25;
        }

        accumulator += frameTime;

        glfwPollEvents();

        // --- Логика (фиксированный timestep) ---
        while (accumulator >= FIXED_DELTA_TIME) {
            if (_currentScene) {
                _currentScene->update(static_cast<float>(FIXED_DELTA_TIME));
            }

            accumulator -= FIXED_DELTA_TIME;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // --- Рендер (переменный FPS) ---
        if (_currentScene) {
            _currentScene->draw(*_renderer);
        }

        // swap buffers
        glfwSwapBuffers(_window->getGLFWWindow());

        lastTime = currentTime;
    }
}
