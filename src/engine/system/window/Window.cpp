//
// Created by Egor Lentarev on 02.01.2026.
//

#include "Window.h"

bool Window::init(const int width, const int height, const char* title) {
    int actualScreenWidth;
    int actualScreenHeight;

    // 1. Инициализация GLFW
    if (!glfwInit()) {
        Logger::log(1, "%s: glfwInit() error\n", __FUNCTION__);
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!mWindow) {
        Logger::log(1, "%s: Could not create window\n", __FUNCTION__);
        glfwTerminate();
        return false;
    }

    glfwGetFramebufferSize(mWindow, &actualScreenWidth, &actualScreenHeight);
    glfwMakeContextCurrent(mWindow);

    // 2. Инициализация GLAD
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        Logger::log(1, "%s: Failed to initialize GLAD\n", __FUNCTION__);
        return false;
    }

    // Set viewport size
    glViewport(0, 0, actualScreenWidth, actualScreenHeight);

    Logger::log(1, "%s: Window successfully initialized\n", __FUNCTION__);
    return true;
}

/**
 * Main Loop
 */
void Window::loop() const {
    // VSYNC
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(mWindow)) {
        glClearColor(0.2f, 1.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // swap buffers
        glfwSwapBuffers(mWindow);

        // poll events in a loop
        glfwPollEvents();
    }
}

/**
 * Cleanup
 */
void Window::cleanup() const {
    Logger::log(1, "%s: Terminating Window\n", __FUNCTION__);
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}