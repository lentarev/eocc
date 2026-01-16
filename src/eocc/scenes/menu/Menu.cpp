#include "Menu.h"
#include <glad/glad.h>
#include <eocc/assets/mesh/structures/MeshData.h>
#include <eocc/assets/mesh/primitives/Primitive.h>
#include <eocc/assets/mesh/Mesh.h>
#include <eocc/renderer/Renderer.h>

Menu::Menu() {
    MeshData cubeData = Primitive::createCube();

    _cubeMesh = std::make_unique<Mesh>(cubeData);
    _cubeMaterial.baseColor = {1.0f, 0.0f, 0.0f};
}

Menu::~Menu() {}

/**
 * Update - logic update
 */
void Menu::update(float deltaTime, float totalTime) {
    _transform.rotation.y = glm::radians(45.0f) * totalTime;
}

void Menu::draw(Renderer& renderer) {
    // Drawing a cube using a renderer
    renderer.drawMesh(*_cubeMesh, _cubeMaterial, _transform.getModelMatrix());
}