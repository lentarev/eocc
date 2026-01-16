//
// Created by Egor Lentarev on 03.01.2026.
//

#include "eocc/Engine.h"

#include <eocc/system/window/Window.h>
#include <eocc/renderer/Renderer.h>
#include <eocc/camera/Camera.h>

#include "scenes/menu/Menu.h"
#include "scenes/level1/Level1.h"

#include <GLFW/glfw3.h>
#include <iostream>

// --- static callback ---
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    if (engine) {
        engine->onKey(key, scancode, action, mods);
    }
}

/// Constructor
Engine::Engine() {
    // 1. Window subsystem
    _window = std::make_unique<Window>(800, 600, "OpenGL Test Window");

    // 2. Renderer subsystem
    _renderer = std::make_unique<Renderer>();

    // Passing a pointer to Engine to the GLFW window
    glfwSetWindowUserPointer(_window->getGLFWWindow(), this);

    // Set callback
    glfwSetKeyCallback(_window->getGLFWWindow(), keyCallback);

    // Let's start with the menu
    _currentScene = std::make_unique<Menu>();
}

/// Destructor
Engine::~Engine() {}

/// Handles keyboard input events.
void Engine::onKey(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        std::cout << "KEY_SPACE" << std::endl;

        // Switch to Level1 scene
        _currentScene = std::make_unique<Level1>();
    }
}

/// Starting the main loop
void Engine::run() {
    double lastTime = glfwGetTime();
    double totalTime = 0.0;  // absolute time of logic
    double accumulator = 0.0;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // Wireframe for testing

    Camera mainCamera;
    mainCamera.setPosition({0.0f, 0.0f, 5.0f});

    // LOOP
    while (!glfwWindowShouldClose(_window->getGLFWWindow())) {
        const double currentTime = glfwGetTime();
        double frameTime = currentTime - lastTime;

        if (frameTime > 0.25) {
            frameTime = 0.25;
        }

        accumulator += frameTime;

        glfwPollEvents();

        float aspect = static_cast<float>(_window->getWidth()) / _window->getHeight();

        // --- Logic (fixed timestep) ---
        while (accumulator >= FIXED_DELTA_TIME) {
            if (_currentScene) {
                _currentScene->update(static_cast<float>(FIXED_DELTA_TIME), static_cast<float>(totalTime));
            }

            totalTime += FIXED_DELTA_TIME;
            accumulator -= FIXED_DELTA_TIME;
        }

        // --- Render (variable FPS) ---
        if (_currentScene) {
            _renderer->beginFrame(mainCamera, aspect);
            _currentScene->draw(*_renderer);
            _renderer->endFrame();
        }

        // swap buffers
        glfwSwapBuffers(_window->getGLFWWindow());

        lastTime = currentTime;
    }
}
