#include "Menu.h"
#include <vecthar/Engine.h>
#include <vecthar/assets/mesh/structures/MeshData.h>
#include <vecthar/assets/mesh/primitives/Primitive.h>
#include <vecthar/assets/mesh/Mesh.h>
#include <vecthar/renderer/Renderer.h>
#include <vecthar/assets/shader/Shader.h>
#include <vecthar/input/Key.h>
#include <vecthar/base/FPSCounter.h>
#include <vecthar/ui/Button.h>

#include <iostream>

#include "scenes/level1/Level1.h"

Menu::Menu() {
    _shader = std::make_unique<vecthar::Shader>();
    _shader->createProgram(_shader->read("./shaders/basic.vert"), _shader->read("./shaders/basic.frag"));

    vecthar::MeshData cubeData = vecthar::Primitive::createCube();

    _cubeMesh = std::make_unique<vecthar::Mesh>(cubeData);
    _cubeMaterial.baseColor = {1.0f, 0.0f, 0.0f};
}

Menu::~Menu() = default;

/**
 * Input
 */
void Menu::onKey(int key, int scancode, int action, int mods) {
    if (key == vecthar::KEY_SPACE && action == 1) {
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

/**
 * Draw 3D
 */
void Menu::draw(vecthar::Renderer& renderer) {
    renderer.useShaderProgram(_shader->getProgram());
    // Drawing a cube using a renderer
    renderer.drawMesh(*_cubeMesh, _cubeMaterial, _transform.getModelMatrix());
}

/**
 * Draw UI
 */
void Menu::drawUI(vecthar::Renderer& renderer, const vecthar::FPSCounter& fps) {
    float UI_TEXT_SCALE = 8.0f / 8.0f;

    std::string text = "FPS: " + std::to_string(fps.getFPS());
    renderer.drawText(text, 10, 10, UI_TEXT_SCALE, {0.2f, 0.5f, 0.0f});
}