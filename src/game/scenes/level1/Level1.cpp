#include "Level1.h"
#include <glad/glad.h>

Level1::Level1() {}

Level1::~Level1() {}

/**
 * Update - обновление логики
 */
void Level1::update(float deltaTime) {
    // Пока аустой
}

void Level1::draw(Renderer& renderer) {
    glClearColor(0.2f, 0.8f, 0.2f, 1.0f);  // green
}