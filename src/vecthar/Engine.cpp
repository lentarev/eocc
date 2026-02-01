//
// Created by Egor Lentarev on 03.01.2026.
//

#include "vecthar/Engine.h"

#include <vecthar/system/window/Window.h>
#include <vecthar/renderer/Renderer.h>
#include <vecthar/camera/Camera.h>
#include <vecthar/base/FPSCounter.h>

#include <GLFW/glfw3.h>
#include <iostream>

// --- static callback ---
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    vecthar::Engine* engine = static_cast<vecthar::Engine*>(glfwGetWindowUserPointer(window));
    if (engine) {
        engine->onKey(key, scancode, action, mods);
    }
}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    vecthar::Engine* engine = static_cast<vecthar::Engine*>(glfwGetWindowUserPointer(window));
    if (engine) {
        engine->onMouseButton(button, action, xpos, ypos);
    }
}

static void framebufferSizeCallback(GLFWwindow* window, const int width, const int height) {
    vecthar::Engine* engine = static_cast<vecthar::Engine*>(glfwGetWindowUserPointer(window));
    if (engine) {
        // engine->onMouseButton(button, action, xpos, ypos);
        engine->onResizeWindow(width, height);
    }
}

namespace vecthar {

/// Constructor
Engine::Engine() {
    // Initialization (GLFW)
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    // 1. Window subsystem
    _window = std::make_unique<Window>(800, 600, "OpenGL Test Window");

    std::cout << "GL Version: " << glGetString(GL_VERSION) << "\n";
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "OpenGL error after Window init: " << err << "\n";
    }

    // 2. Renderer subsystem
    _renderer = std::make_unique<Renderer>();

    // Passing a pointer to Engine to the GLFW window
    glfwSetWindowUserPointer(_window->getGLFWWindow(), this);

    // Set callbacks
    glfwSetKeyCallback(_window->getGLFWWindow(), keyCallback);
    glfwSetMouseButtonCallback(_window->getGLFWWindow(), mouseButtonCallback);
    glfwSetFramebufferSizeCallback(_window->getGLFWWindow(), framebufferSizeCallback);
}

/// Destructor
Engine::~Engine() {
    // Freeing up all resources associated with GLFW
    glfwTerminate();
}

/// Handles keyboard input events.
void Engine::onKey(int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (_currentScene) {
            // Call the onKey method from the scene
            _currentScene->onKey(key, scancode, action, mods);
        }
    }
}

/// @brief Handles mouse events.
/// @param button
/// @param action
/// @param xpos
/// @param ypos
void Engine::onMouseButton(int button, int action, double xpos, double ypos) {
    _mouseX = xpos;
    _mouseY = ypos;

    // Преобразуем координаты мыши в framebuffer-пространство
    int winW, winH, fbW, fbH;
    glfwGetWindowSize(_window->getGLFWWindow(), &winW, &winH);
    glfwGetFramebufferSize(_window->getGLFWWindow(), &fbW, &fbH);

    float scaleX = static_cast<float>(fbW) / winW;
    float scaleY = static_cast<float>(fbH) / winH;

    _mouseX *= scaleX;
    _mouseY *= scaleY;

    _mousePressed = (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS);
}

/// @brief Set current scene
/// @param scene
void Engine::setCurrentScene(std::unique_ptr<SceneBase> scene) {
    _pendingScene = std::move(scene);
}

/// @brief Handles framebuffer size event
/// @param width
/// @param height
void Engine::onResizeWindow(const int width, const int height) {
    // Update viewport
    glViewport(0, 0, width, height);
    if (_currentScene) {
        _currentScene->onResizeWindow();
    }
}

bool Engine::isMousePressed() const {
    return _mousePressed;
}

float Engine::getMouseX() const {
    return static_cast<float>(_mouseX);
}

float Engine::getMouseY() const {
    return static_cast<float>(_mouseY);
}

/// @brief return a reference to the window
/// @return
Window& Engine::getWindow() const {
    return *_window;
}

/// @brief Request to close the application.
void Engine::requestClose() {
    glfwSetWindowShouldClose(_window->getGLFWWindow(), GLFW_TRUE);
}

/// @brief Starting the main loop
void Engine::run() {
    double lastTime = glfwGetTime();
    double totalTime = 0.0;  // absolute time of logic
    double accumulator = 0.0;

    FPSCounter fpsCounter;

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

        if (frameTime > 0.1) {
            frameTime = 0.1;
        }

        accumulator += frameTime;

        glfwPollEvents();

        float aspect = static_cast<float>(_window->getWidth()) / _window->getHeight();

        // std::cout << "w: " << _window->getWidth() << " h: " << _window->getHeight() << std::endl;

        // --- Logic (fixed timestep) ---
        while (accumulator >= FIXED_DELTA_TIME) {
            if (_currentScene) {
                _currentScene->update(static_cast<float>(FIXED_DELTA_TIME), static_cast<float>(totalTime));
            }

            // Проверка отложенной смены сцены
            if (_pendingScene) {
                _currentScene = std::move(_pendingScene);
                _currentScene->setEngine(this);
                _currentScene->initialize();
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

        // --- Render UI ---
        if (_currentScene) {
            _renderer->beginUIFrame(_window->getWidth(), _window->getHeight());

            fpsCounter.update();  // Updating FPS before rendering
            _currentScene->drawUI(*_renderer, fpsCounter);
            _renderer->endUIFrame();
        }

        // swap buffers
        glfwSwapBuffers(_window->getGLFWWindow());

        lastTime = currentTime;
    }
}

}  // namespace vecthar