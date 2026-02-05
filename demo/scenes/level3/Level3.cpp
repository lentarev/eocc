//
// Created by Egor Lentarev on 05.02.2026.
//

#include "scenes/level3/Level3.h"
#include <vecthar/Engine.h>
#include <vecthar/assets/model/structures/Model.h>
#include <vecthar/renderer/Renderer.h>
#include <vecthar/assets/shader/Shader.h>
#include <vecthar/input/Key.h>
#include <vecthar/base/FPSCounter.h>
#include <vecthar/system/window/Window.h>
#include <vecthar/assets/model/ModelLoader.h>
#include <vecthar/lighting/shadow_utils.h>
#include <vecthar/core/GameObject.h>

#include "scenes/menu/Menu.h"

#include <glad/glad.h>

/**
 * Constructor
 */
Level3::Level3() = default;

/**
 * Destructor
 */
Level3::~Level3() = default;

/**
 * Initialize
 */
void Level3::initialize(vecthar::Renderer& renderer) {
    // Depth shader
    _depthShader = std::make_unique<vecthar::Shader>();
    _depthShader->createProgram(_depthShader->read("./assets/shaders/depth.vert"), _depthShader->read("./assets/shaders/depth.frag"));

    // Main shader
    _shader = std::make_unique<vecthar::Shader>();
    _shader->createProgram(_shader->read("./assets/shaders/basic.vert"), _shader->read("./assets/shaders/basic.frag"));

    // Tower Model
    auto towerModel = std::make_unique<vecthar::Model>(vecthar::ModelLoader::loadFromFile("./assets/models/tower.glb"));

    // Platform Model
    auto platformModel = std::make_unique<vecthar::Model>(vecthar::ModelLoader::loadFromFile("./assets/models/platform.glb"));

    // Gun Model
    auto gunModel = std::make_unique<vecthar::Model>(vecthar::ModelLoader::loadFromFile("./assets/models/gun.glb"));

    // >>>>>>>>>>>>>>>>>>>>>>>>>>
    // Create root object - Turret
    _turret = std::make_unique<vecthar::GameObject>("Turret");
    _turret->model = std::move(towerModel);
    _turret->transform.position = glm::vec3(0.0f, 0.8f, 0.0f);
    _turret->transform.scale = glm::vec3(0.5f);

    // >>>>>>>>>>>>>>>>>>>>>>>>>>
    // We create a platform and add it to the Tower.
    auto platform = std::make_unique<vecthar::GameObject>("Platform");
    platform->model = std::move(platformModel);
    platform->transform.scale = glm::vec3(0.6f);
    platform->transform.position = glm::vec3(0.0f, 2.0f, 0.0f);  // local
    _platformPtr = _turret->addChild(std::move(platform));

    // >>>>>>>>>>>>>>>>>>>>>>>>>>
    // Create a gun and add it to the platform
    auto gun = std::make_unique<vecthar::GameObject>("Gun");
    gun->model = std::move(gunModel);
    gun->transform.position = glm::vec3(0.0f, 1.5f, 0.0f);  // local
    gun->transform.scale = glm::vec3(1.8f);
    _platformPtr->addChild(std::move(gun));

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
void Level3::onKey(int key, int scancode, int action, int mods) {
    std::cout << "key: " << key << std::endl;

    if (key == vecthar::KEY_ESCAPE && action == 1) {
        // Transition to another scene
        this->getEngine()->setCurrentScene(std::make_unique<Menu>());
    }
}

/**
 * Update - logic update
 */
void Level3::update(float deltaTime, float totalTime) {
    // _turret->transform.rotation.y = glm::radians(25.0f) * totalTime;

    _platformPtr->transform.rotation.y = glm::radians(25.0f) * totalTime;
    _turret->markTransformHierarchyDirty();
}

/**
 * Draw shadow
 */
void Level3::drawShadow(vecthar::Renderer& renderer) {
    GLint program = _depthShader->getProgram();

    renderer.useShaderProgram(program);

    glm::mat4 lightSpaceMatrix = vecthar::calculate_light_space_matrix(renderer.getDirectionalLight(), glm::vec3(0.0f), 50.0f, 1.0f, 100.0f);
    renderer.setLightSpaceMatrix(lightSpaceMatrix);

    GLuint lightSpaceLoc = glGetUniformLocation(program, "u_LightSpaceMatrix");
    glUniformMatrix4fv(lightSpaceLoc, 1, GL_FALSE, &lightSpaceMatrix[0][0]);

    // Turret
    _turret->renderShadow(renderer, program);

    // Ground
    for (const auto& mesh : _groundModel->meshes) {
        renderer.drawShadowMesh(*mesh, _groundTransform.getModelMatrix());
    }
}

/**
 * Draw 3D
 */
void Level3::draw(vecthar::Renderer& renderer) {
    renderer.useShaderProgram(_shader->getProgram());

    // Turret
    _turret->render(renderer);

    // Ground
    for (const auto& mesh : _groundModel->meshes) {
        renderer.drawMesh(*mesh, mesh->getMaterial(), _groundTransform.getModelMatrix());
    }
}

/**
 * Draw UI
 */
void Level3::drawUI(vecthar::Renderer& renderer, const vecthar::FPSCounter& fps) {
    float UI_TEXT_SCALE = _uiScale * 2.0f;

    std::string text = "FPS: " + std::to_string(fps.getFPS());
    renderer.drawText(text, 10, 10, UI_TEXT_SCALE, {1.0f, 0.2f, 0.4f});
}