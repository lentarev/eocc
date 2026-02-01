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
#include "scenes/level2/Level2.h"

Menu::Menu() {}

Menu::~Menu() = default;

void Menu::initialize() {
    _uiScale = getEngine()->getWindow().getContentScale();

    // Define buttons
    _startLevel1Button = std::make_unique<vecthar::ui::Button>();
    _startLevel2Button = std::make_unique<vecthar::ui::Button>();

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

    // Button - Start Level 1
    _startLevel1Button->setLabel("Start Level 1");
    _startLevel1Button->setX(w * _uiScale);
    _startLevel1Button->setY(h * _uiScale);
    _startLevel1Button->setWidth(200 * _uiScale);
    _startLevel1Button->setHeight(40 * _uiScale);

    // Button - Start Level 2
    _startLevel2Button->setLabel("Start Level 2");
    _startLevel2Button->setX(w * _uiScale);
    _startLevel2Button->setY((h + 50) * _uiScale);
    _startLevel2Button->setWidth(200 * _uiScale);
    _startLevel2Button->setHeight(40 * _uiScale);
}

/**
 * Input
 */
void Menu::onKey(int key, int scancode, int action, int mods) {
    std::cout << "key: " << key << std::endl;

    if (key == vecthar::KEY_ESCAPE && action == 1) {
        // Request to close the application.
        this->getEngine()->requestClose();
    }
}

/**
 * Update - logic update
 */
void Menu::update(float deltaTime, float totalTime) {
    vecthar::Engine* engine = this->getEngine();

    if (engine->isMousePressed()) {
        float mx = engine->getMouseX();
        float my = engine->getMouseY();

        if (_startLevel1Button->contains(mx, my)) {
            // Transition to another scene
            engine->setCurrentScene(std::make_unique<Level1>());
        }

        if (_startLevel2Button->contains(mx, my)) {
            // Transition to another scene
            engine->setCurrentScene(std::make_unique<Level2>());
        }
    }
}

/**
 * Draw 3D
 */
void Menu::draw(vecthar::Renderer& renderer) {}

/**
 * Draw UI
 */
void Menu::drawUI(vecthar::Renderer& renderer, const vecthar::FPSCounter& fps) {
    float UI_TEXT_SCALE = _uiScale * 2.0f;

    _startLevel1Button->render(renderer, UI_TEXT_SCALE);
    _startLevel2Button->render(renderer, UI_TEXT_SCALE);

    std::string text = "FPS: " + std::to_string(fps.getFPS());
    renderer.drawText(text, 10, 10, UI_TEXT_SCALE, {1.0f, 0.2f, 0.4f});
}