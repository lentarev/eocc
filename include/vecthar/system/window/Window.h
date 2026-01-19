//
// Created by Egor Lentarev on 02.01.2026.
//

#ifndef VECTHAR_WINDOW_H
#define VECTHAR_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vecthar/base/logger/Logger.h>

// #include <vecthar/base/OpenGLTypes.h>

namespace vecthar {

class Window {
public:
    // Constructor
    Window(const int width, const int height, const char* title);

    // Destructor
    ~Window();

    // Returns a pointer to GLFWwindow
    GLFWwindow* getGLFWWindow() const;

    // Returns the current window width (in pixels)
    int getWidth() const;

    // Returns the current window height (in pixels)
    int getHeight() const;

private:
    GLFWwindow* _window = nullptr;
};

}  // namespace vecthar

#endif  // VECTHAR_WINDOW_H