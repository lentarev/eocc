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
#include <vecthar/lighting/shadow_utils.h>

#include "scenes/menu/Menu.h"

#include <glad/glad.h>

Level2::Level2() = default;

Level2::~Level2() = default;

void Level2::initialize(vecthar::Renderer& renderer) {
    // Depth shader
    _depthShader = std::make_unique<vecthar::Shader>();
    _depthShader->createProgram(_depthShader->read("./assets/shaders/depth.vert"), _depthShader->read("./assets/shaders/depth.frag"));

    // Main hsader
    _shader = std::make_unique<vecthar::Shader>();
    _shader->createProgram(_shader->read("./assets/shaders/basic.vert"), _shader->read("./assets/shaders/basic.frag"));

    // Tower
    auto tower = vecthar::ModelLoader::loadFromFile("./assets/models/tower.glb");
    _towerModel = std::make_unique<vecthar::Model>(std::move(tower));
    _towerTransform.scale = glm::vec3(0.5f, 0.5f, 0.5f);
    _towerTransform.position = glm::vec3(0.0f, 1.5f, 0.0f);

    // Ground
    auto ground = vecthar::ModelLoader::loadFromFile("./assets/models/ground.glb");
    _groundModel = std::make_unique<vecthar::Model>(std::move(ground));
    _groundTransform.position = glm::vec3(0.0f, 0.0f, 0.0f);

    _uiScale = getEngine()->getWindow().getContentScale();

    renderer.setDirectionalLight({.direction = glm::normalize(glm::vec3(-1.0f, -1.0f, -1.0f)), .color = glm::vec3(1.0f, 0.95f, 0.8f), .intensity = 1.2f});
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
    _towerTransform.rotation.y = glm::radians(45.0f) * totalTime;
}

/**
 * Draw shadow
 */
void Level2::drawShadow(vecthar::Renderer& renderer) {
    GLint program = _depthShader->getProgram();

    renderer.useShaderProgram(program);

    glm::mat4 lightSpaceMatrix = vecthar::calculate_light_space_matrix(renderer.getDirectionalLight(), glm::vec3(0.0f), 50.0f, 1.0f, 100.0f);
    renderer.setLightSpaceMatrix(lightSpaceMatrix);

    GLuint lightSpaceLoc = glGetUniformLocation(program, "u_LightSpaceMatrix");
    glUniformMatrix4fv(lightSpaceLoc, 1, GL_FALSE, &lightSpaceMatrix[0][0]);

    // Tower
    for (const auto& mesh : _towerModel->meshes) {
        renderer.drawShadowMesh(*mesh, _towerTransform.getModelMatrix());
    }

    // Ground
    for (const auto& mesh : _groundModel->meshes) {
        renderer.drawShadowMesh(*mesh, _groundTransform.getModelMatrix());
    }
}

/**
 * Draw 3D
 */
void Level2::draw(vecthar::Renderer& renderer) {
    renderer.useShaderProgram(_shader->getProgram());

    // Tower
    for (const auto& mesh : _towerModel->meshes) {
        renderer.drawMesh(*mesh, mesh->getMaterial(), _towerTransform.getModelMatrix());
    }

    // Ground
    for (const auto& mesh : _groundModel->meshes) {
        renderer.drawMesh(*mesh, mesh->getMaterial(), _groundTransform.getModelMatrix());
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