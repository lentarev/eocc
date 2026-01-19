#include <memory>
#include <GLFW/glfw3.h>
#include <vecthar/Engine.h>
#include <vecthar/base/logger/Logger.h>

// Scenes
#include "scenes/menu/Menu.h"
#include "scenes/level1/Level1.h"

int main() {
    // 1. Global Initialization (GLFW)
    if (!glfwInit()) {
        return -1;
    }

    try {
        const auto engine = std::make_unique<vecthar::Engine>();
        engine->setCurrentScene(std::make_unique<Menu>());
        engine->run();

    } catch (const std::exception& e) {
        vecthar::Logger::log(1, "Fatal error: %s\n", e.what());
        return -1;
    }

    // Freeing up all resources associated with GLFW
    glfwTerminate();

    return 0;
}