#include <memory>
#include <GLFW/glfw3.h>
#include <engine/Engine.h>
#include <engine/base/logger/Logger.h>

int main() {
    // 1. Global Initialization (GLFW)
    if (!glfwInit()) {
        return -1;
    }

    try {
        const auto engine = std::make_unique<Engine>();
        engine->run();

    } catch (const std::exception& e) {
        Logger::log(1, "Fatal error: %s\n", e.what());
        return -1;
    }

    // Freeing up all resources associated with GLFW
    glfwTerminate();

    return 0;
}