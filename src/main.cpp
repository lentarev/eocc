#include <memory>
#include <engine/system/window/Window.h>
#include <engine/base/logger/Logger.h>

int main() {
    const auto w = std::make_unique<Window>();

    if (!w->init(640, 480, "OpenGL Test Window")) {
        Logger::log(1, "%s error: Window init error\n", __FUNCTION__);
        return -1;
    }

    w->loop();

    w->cleanup();

    return 0;
}