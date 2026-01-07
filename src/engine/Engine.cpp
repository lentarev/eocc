//
// Created by Egor Lentarev on 03.01.2026.
//

#include "Engine.h"
#include <engine/system/window/Window.h>
#include <engine/assets/shader/Shader.h>
#include <engine/renderer/Renderer.h>
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
            // game->update(FIXED_DELTA_TIME);
            accumulator -= FIXED_DELTA_TIME;
        }

        // --- Рендер (переменный FPS) ---
        // renderer->draw(game->getScene());

        // swap buffers
        glfwSwapBuffers(_window->getGLFWWindow());

        // Позже перенести в рендерер
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        lastTime = currentTime;
    }
}
