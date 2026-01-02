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
    bool init(int width, int height, const char* title);

    void loop() const;

    void cleanup() const;

private:
    GLFWwindow* mWindow = nullptr;
};

#endif  // EOCC_WINDOW_H