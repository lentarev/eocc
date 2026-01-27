//
// Created by Egor Lentarev on 02.01.2026.
//

#ifndef VECTHAR_WINDOW_H
#define VECTHAR_WINDOW_H

struct GLFWwindow;  // ← forward declaration

namespace vecthar {

// forward declaration
class Engine;

class Window {
    friend class Engine;  // Engine can read _window

public:
    // Constructor
    Window(const int width, const int height, const char* title);

    // Destructor
    ~Window();

    // Returns the current window width (in pixels)
    int getWidth() const;

    // Returns the current window height (in pixels)
    int getHeight() const;

    float getContentScale() const;

private:
    GLFWwindow* _window = nullptr;
    GLFWwindow* getGLFWWindow() const { return _window; }
};

}  // namespace vecthar

#endif  // VECTHAR_WINDOW_H