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
#include <vecthar/system/window/Window.h>
#include <vecthar/assets/model/ModelLoader.h>

#include <iostream>

#include "scenes/level1/Level1.h"

Menu::Menu() {}

Menu::~Menu() = default;

void Menu::initialize() {
    _shader = std::make_unique<vecthar::Shader>();
    _shader->createProgram(_shader->read("./assets/shaders/basic.vert"), _shader->read("./assets/shaders/basic.frag"));

    // vecthar::MeshData cubeData = vecthar::Primitive::createCube();
    // _cubeMesh = std::make_unique<vecthar::Mesh>(cubeData);
    // _cubeMaterial.baseColor = {1.0f, 0.0f, 0.0f};
    // _transform.position = glm::vec3(-2.0f, 0.0f, 0.0f);

    auto tower = vecthar::ModelLoader::loadFromFile("./assets/models/tower.glb");
    _towerMesh = std::make_unique<vecthar::Mesh>(tower.meshes[0]);

    _cubeMaterial.baseColor = {0.3f, 0.0f, 0.0f};
    _transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);
    _transform.position = glm::vec3(0.0f, 0.0f, 0.0f);

    _uiScale = getEngine()->getWindow().getContentScale();
    _startButton = std::make_unique<vecthar::ui::Button>();

    onResizeWindow();
}

/**
 * Handles on resize window event
 */
void Menu::onResizeWindow() {
    int winW = getEngine()->getWindow().getWidth();
    int winH = getEngine()->getWindow().getHeight();

    int logicalW = static_cast<int>(winW / _uiScale);  // 1600 / 2 = 800
    int logicalH = static_cast<int>(winH / _uiScale);  // 1200 / 2 = 600

    int w = (logicalW / 2) - 100;  // 400 - 100 = 300
    int h = (logicalH / 2) - 20;   // 300 - 20 = 280

    _startButton->setLabel("Start Game");
    _startButton->setX(w * _uiScale);
    _startButton->setY(h * _uiScale);
    _startButton->setWidth(200 * _uiScale);
    _startButton->setHeight(40 * _uiScale);
}

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

    vecthar::Engine* engine = this->getEngine();

    if (engine->isMousePressed()) {
        float mx = engine->getMouseX();
        float my = engine->getMouseY();

        if (_startButton->contains(mx, my)) {
            // Transition to another scene
            engine->setCurrentScene(std::make_unique<Level1>());
        }
    }
}

/**
 * Draw 3D
 */
void Menu::draw(vecthar::Renderer& renderer) {
    renderer.useShaderProgram(_shader->getProgram());
    // Drawing a cube using a renderer
    // renderer.drawMesh(*_cubeMesh, _cubeMaterial, _transform.getModelMatrix());
    renderer.drawMesh(*_towerMesh, _cubeMaterial, _transform.getModelMatrix());
}

/**
 * Draw UI
 */
void Menu::drawUI(vecthar::Renderer& renderer, const vecthar::FPSCounter& fps) {
    float UI_TEXT_SCALE = _uiScale * 2.0f;

    _startButton->render(renderer, UI_TEXT_SCALE);

    std::string text = "FPS: " + std::to_string(fps.getFPS());
    renderer.drawText(text, 10, 10, UI_TEXT_SCALE, {1.0f, 0.2f, 0.4f});
}