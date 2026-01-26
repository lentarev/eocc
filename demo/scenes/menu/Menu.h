//
// Created by Egor Lentarev on 06.01.2026.
//

#ifndef VECTHAR_MENU_H
#define VECTHAR_MENU_H

#include <memory>
#include <string>

#include <vecthar/scene/base/SceneBase.h>
#include <vecthar/assets/material/Material.h>
#include <vecthar/base/structures/Transform.h>

// Forward declaration of classes
// namespace vecthar::ui {
// class Button;
//}

// Forward declaration of classes
namespace vecthar {

class Mesh;
class Renderer;
class Shader;
class FPSCounter;

}  // namespace vecthar

class Menu : public vecthar::SceneBase {
public:
    Menu();
    ~Menu();

    void update(float deltaTime, float totalTime) override;
    void draw(vecthar::Renderer& renderer) override;
    void drawUI(vecthar::Renderer& renderer, const vecthar::FPSCounter& fps) override;
    void onKey(int key, int scancode, int action, int mods) override;

private:
    std::unique_ptr<vecthar::Mesh> _cubeMesh;
    std::unique_ptr<vecthar::Shader> _shader;
    vecthar::Material _cubeMaterial;
    vecthar::Transform _transform;

    // vecthar::ui::Button _startButton;

    // std::vector<glm::vec3> _positions;
    // float _rotation = 0.0f;
};

#endif  // VECTHAR_MENU_H