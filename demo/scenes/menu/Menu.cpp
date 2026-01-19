#include "Menu.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vecthar/Engine.h>
#include <vecthar/assets/mesh/structures/MeshData.h>
#include <vecthar/assets/mesh/primitives/Primitive.h>
#include <vecthar/assets/mesh/Mesh.h>
#include <vecthar/renderer/Renderer.h>
#include <vecthar/assets/shader/Shader.h>

#include "scenes/level1/Level1.h"

Menu::Menu() {
    _shader = std::make_unique<vecthar::Shader>();
    _shader->createProgram(_shader->read("./shaders/basic.vert"), _shader->read("./shaders/basic.frag"));

    vecthar::MeshData cubeData = vecthar::Primitive::createCube();

    _cubeMesh = std::make_unique<vecthar::Mesh>(cubeData);
    _cubeMaterial.baseColor = {1.0f, 0.0f, 0.0f};
}

Menu::~Menu() {}

/**
 * Input
 */
void Menu::onKey(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        // Transition to another scene
        this->getEngine()->setCurrentScene(std::make_unique<Level1>());
    }
}

/**
 * Update - logic update
 */
void Menu::update(float deltaTime, float totalTime) {
    _transform.rotation.y = glm::radians(45.0f) * totalTime;
}

void Menu::draw(vecthar::Renderer& renderer) {
    renderer.useShaderProgram(_shader->getProgram());
    // Drawing a cube using a renderer
    renderer.drawMesh(*_cubeMesh, _cubeMaterial, _transform.getModelMatrix());
}