//
// Created by Egor Lentarev on 05.02.2026.
//

#ifndef VECTHAR_LEVEL3_H
#define VECTHAR_LEVEL3_H

#include <memory>
#include <string>

#include <vecthar/scene/base/SceneBase.h>
#include <vecthar/assets/material/Material.h>
#include <vecthar/base/structures/Transform.h>

// Forward declaration of classes
namespace vecthar {

struct Model;
class Renderer;
class Shader;
class FPSCounter;
class GameObject;

}  // namespace vecthar

class Level3 : public vecthar::SceneBase {
public:
    Level3();
    ~Level3();

    void initialize(vecthar::Renderer& renderer) override;

    void update(float deltaTime, float totalTime) override;
    void drawShadow(vecthar::Renderer& renderer) override;
    void draw(vecthar::Renderer& renderer) override;
    void drawUI(vecthar::Renderer& renderer, const vecthar::FPSCounter& fps) override;
    void onKey(int key, int scancode, int action, int mods) override;

private:
    float _uiScale;

    // Ground
    std::unique_ptr<vecthar::Model> _groundModel;
    vecthar::Transform _groundTransform;

    // Turret
    std::unique_ptr<vecthar::GameObject> _turret;
    vecthar::GameObject* _platformPtr = nullptr;

    // Shaders
    std::unique_ptr<vecthar::Shader> _shader;
    std::unique_ptr<vecthar::Shader> _depthShader;
};

#endif  // VECTHAR_LEVEL3_H