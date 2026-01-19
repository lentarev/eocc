//
// Created by Egor Lentarev on 02.01.2026.
//

#include <vecthar/system/window/Window.h>
#include <stdexcept>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vecthar/base/logger/Logger.h>

namespace vecthar {

/**
 * Constructor
 */
Window::Window(const int width, const int height, const char* title) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int framebufferWidth;
    int framebufferHeight;

    _window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!_window) {
        throw std::runtime_error("Failed to create GLFW window");
    }

    // glfwDestroyWindow(_window);  // ← сначала уберём окно (чтобы не утекало)
    // throw std::runtime_error("Тест: имитация ошибки в конструкторе Window");

    glfwGetFramebufferSize(_window, &framebufferWidth, &framebufferHeight);
    glfwMakeContextCurrent(_window);

    // 2. Init GLAD
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        glfwDestroyWindow(_window);  // убираем часть ресурса
        throw std::runtime_error("Failed to initialize GLAD");
    }

    // Set viewport size
    glViewport(0, 0, framebufferWidth, framebufferHeight);

    // VSYNC
    glfwSwapInterval(1);

    // Set a callback to update when resizing
    glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* w, int fbW, int fbH) { glViewport(0, 0, fbW, fbH); });

    Logger::log(1, "%s: Window successfully initialized\n", __FUNCTION__);
}

/**
 * Desctructor
 */
Window::~Window() {
    Logger::log(1, "%s: Terminating Window\n", __FUNCTION__);
    glfwDestroyWindow(_window);
}

/**
 * Returns a pointer to GLFWwindow
 */
// GLFWwindow* Window::getGLFWWindow() const {
//     return _window;
// }

int Window::getWidth() const {
    int w, h;
    glfwGetFramebufferSize(_window, &w, &h);
    return w;
}

int Window::getHeight() const {
    int w, h;
    glfwGetFramebufferSize(_window, &w, &h);
    return h;
}

}  // namespace vecthar