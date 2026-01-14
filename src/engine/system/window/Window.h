//
// Created by Egor Lentarev on 02.01.2026.
//

#ifndef EOCC_WINDOW_H
#define EOCC_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <engine/base/logger/Logger.h>

class Window {
public:
    // Constructor
    Window(const int width, const int height, const char* title);

    // Destructor
    ~Window();

    // Возвращает указатель на GLFWwindow
    GLFWwindow* getGLFWWindow() const;

    // Возвращает текущую ширину окна (в пикселях)
    int getWidth() const;

    // Возвращает текущую высоту окна (в пикселях)
    int getHeight() const;

private:
    GLFWwindow* _window = nullptr;
};

#endif  // EOCC_WINDOW_H