#include "Level1.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <eocc/Engine.h>
#include <eocc/assets/mesh/structures/MeshData.h>
#include <eocc/assets/mesh/primitives/Primitive.h>
#include <eocc/assets/mesh/Mesh.h>
#include <eocc/renderer/Renderer.h>

#include "scenes/menu/Menu.h"

// Constructor
Level1::Level1() {
    MeshData cubeData = Primitive::createCube();

    _cubeMesh = std::make_unique<Mesh>(cubeData);
    _cubeMaterial.baseColor = {1.0f, 1.0f, 0.0f};
}

// Destructor
Level1::~Level1() {}

/**
 * Input
 */
void Level1::onKey(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        // Transition to another scene
        this->getEngine()->setCurrentScene(std::make_unique<Menu>());
    }
}

/**
 * Update - logic update
 */
void Level1::update(float deltaTime, float totalTime) {
    _transform.rotation.y = glm::radians(45.0f) * totalTime;
}

void Level1::draw(Renderer& renderer) {
    // Drawing a cube using a renderer
    renderer.drawMesh(*_cubeMesh, _cubeMaterial, _transform.getModelMatrix());
}