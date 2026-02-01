//
// Created by Egor Lentarev on 06.01.2026.
//

#ifndef VECTHAR_LEVEL1_H
#define VECTHAR_LEVEL1_H

#include <memory>
#include <string>

#include <vecthar/scene/base/SceneBase.h>
#include <vecthar/assets/material/Material.h>
#include <vecthar/base/structures/Transform.h>

namespace vecthar {

// Forward declaration of classes
class Mesh;
class Renderer;
class Shader;
class FPSCounter;

}  // namespace vecthar

class Level1 : public vecthar::SceneBase {
public:
    Level1();
    ~Level1();

    void initialize() override;

    void update(float deltaTime, float totalTime) override;
    void draw(vecthar::Renderer& renderer) override;
    void drawUI(vecthar::Renderer& renderer, const vecthar::FPSCounter& fps) override;
    void onKey(int key, int scancode, int action, int mods) override;

private:
    float _uiScale;

    std::unique_ptr<vecthar::Mesh> _cubeMesh;
    std::unique_ptr<vecthar::Shader> _shader;
    vecthar::Material _cubeMaterial;
    vecthar::Transform _transform;
};

#endif  // VECTHAR_LEVEL1_H