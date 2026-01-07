#include "Menu.h"
#include <glad/glad.h>

Menu::Menu() {}

Menu::~Menu() {}

/**
 * Update - обновление логики
 */
void Menu::update() {
    // Пока аустой
}

void Menu::draw(Renderer& renderer) {
    glClearColor(0.8f, 0.2f, 0.2f, 1.0f);  // красный
    glClear(GL_COLOR_BUFFER_BIT);
}