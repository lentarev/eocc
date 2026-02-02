//
// Created by Egor Lentarev on 06.01.2026.
//

#ifndef VECTHAR_MENU_H
#define VECTHAR_MENU_H

#include <memory>
#include <string>

#include <vecthar/scene/base/SceneBase.h>

// Forward declaration of classes
namespace vecthar::ui {

class Button;

}

// Forward declaration of classes
namespace vecthar {

class Renderer;
class FPSCounter;

}  // namespace vecthar

class Menu : public vecthar::SceneBase {
public:
    Menu();
    ~Menu();

    void initialize(vecthar::Renderer& renderer) override;

    void update(float deltaTime, float totalTime) override;
    void draw(vecthar::Renderer& renderer) override;
    void drawUI(vecthar::Renderer& renderer, const vecthar::FPSCounter& fps) override;
    void onKey(int key, int scancode, int action, int mods) override;
    void onResizeWindow() override;

private:
    float _uiScale;

    std::unique_ptr<vecthar::ui::Button> _startLevel1Button;
    std::unique_ptr<vecthar::ui::Button> _startLevel2Button;
};

#endif  // VECTHAR_MENU_H