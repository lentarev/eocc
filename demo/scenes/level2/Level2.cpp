//
// Created by Egor Lentarev on 01.02.2026.
//

#include "scenes/level2/Level2.h"
#include <vecthar/Engine.h>
#include <vecthar/assets/model/structures/Model.h>
#include <vecthar/renderer/Renderer.h>
#include <vecthar/assets/shader/Shader.h>
#include <vecthar/input/Key.h>
#include <vecthar/base/FPSCounter.h>
#include <vecthar/system/window/Window.h>
#include <vecthar/assets/model/ModelLoader.h>

#include "scenes/menu/Menu.h"

Level2::Level2() = default;

Level2::~Level2() = default;

void Level2::initialize() {
    _shader = std::make_unique<vecthar::Shader>();
    _shader->createProgram(_shader->read("./assets/shaders/basic.vert"), _shader->read("./assets/shaders/basic.frag"));

    auto tower = vecthar::ModelLoader::loadFromFile("./assets/models/tower.glb");
    _towerModel = std::make_unique<vecthar::Model>(std::move(tower));

    _transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);
    _transform.position = glm::vec3(0.0f, 0.0f, 0.0f);

    _uiScale = getEngine()->getWindow().getContentScale();
}

/**
 * Input
 */
void Level2::onKey(int key, int scancode, int action, int mods) {
    std::cout << "key: " << key << std::endl;

    if (key == vecthar::KEY_ESCAPE && action == 1) {
        // Transition to another scene
        this->getEngine()->setCurrentScene(std::make_unique<Menu>());
    }
}

/**
 * Update - logic update
 */
void Level2::update(float deltaTime, float totalTime) {
    _transform.rotation.y = glm::radians(45.0f) * totalTime;
}

/**
 * Draw 3D
 */
void Level2::draw(vecthar::Renderer& renderer) {
    renderer.useShaderProgram(_shader->getProgram());

    for (const auto& mesh : _towerModel->meshes) {
        renderer.drawMesh(*mesh, mesh->getMaterial(), _transform.getModelMatrix());
    }
}

/**
 * Draw UI
 */
void Level2::drawUI(vecthar::Renderer& renderer, const vecthar::FPSCounter& fps) {
    float UI_TEXT_SCALE = _uiScale * 2.0f;

    std::string text = "FPS: " + std::to_string(fps.getFPS());
    renderer.drawText(text, 10, 10, UI_TEXT_SCALE, {1.0f, 0.2f, 0.4f});
}