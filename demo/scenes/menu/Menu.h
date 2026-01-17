//
// Created by Egor Lentarev on 06.01.2026.
//

#ifndef EOCC_MENU_H
#define EOCC_MENU_H

#include <memory>
#include <string>

#include <eocc/scene/base/SceneBase.h>
#include <eocc/assets/material/Material.h>
#include <eocc/base/structures/Transform.h>

// Forward declaration of classes
namespace eocc {

class Mesh;
class Renderer;
class Shader;

}  // namespace eocc

class Menu : public eocc::SceneBase {
public:
    Menu();
    ~Menu();

    void update(float deltaTime, float totalTime) override;
    void draw(eocc::Renderer& renderer) override;
    void onKey(int key, int scancode, int action, int mods) override;

private:
    std::unique_ptr<eocc::Mesh> _cubeMesh;
    std::unique_ptr<eocc::Shader> _shader;
    eocc::Material _cubeMaterial;
    eocc::Transform _transform;
};

#endif  // EOCC_MENU_H