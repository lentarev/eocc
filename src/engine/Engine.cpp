//
// Created by Egor Lentarev on 03.01.2026.
//

#include "Engine.h"
#include <engine/system/window/Window.h>

/**
 * Constructor
 */
Engine::Engine() {
    // 1. Оконная подсистема
    _window = std::make_unique<Window>(1920, 1080, "OpenGL Test Window");
}

/**
 * Destructor
 */
Engine::~Engine() {}

/**
 * Запуск главного цикла
 */
void Engine::run() {
    // Запускаем цикл оконной подсистемы
    _window->loop();
}
