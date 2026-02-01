//
// Created by Egor Lentarev on 01.02.2026.
//

#ifndef VECTHAR_LEVEL2_H
#define VECTHAR_LEVEL2_H

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

}  // namespace vecthar

class Level2 : public vecthar::SceneBase {
public:
    Level2();
    ~Level2();

    void initialize() override;

    void update(float deltaTime, float totalTime) override;
    void draw(vecthar::Renderer& renderer) override;
    void drawUI(vecthar::Renderer& renderer, const vecthar::FPSCounter& fps) override;
    void onKey(int key, int scancode, int action, int mods) override;

private:
    float _uiScale;

    std::unique_ptr<vecthar::Model> _towerModel;
    std::unique_ptr<vecthar::Shader> _shader;
    vecthar::Transform _transform;
};

#endif  // VECTHAR_LEVEL2_H