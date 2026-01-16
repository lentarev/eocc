//
// Created by Egor Lentarev on 06.01.2026.
//

#ifndef EOCC_MENU_H
#define EOCC_MENU_H

#include <memory>
#include <eocc/scene/base/SceneBase.h>
#include <eocc/assets/material/Material.h>
#include <eocc/base/structures/Transform.h>

// Forward declaration of classes
class Mesh;
class Renderer;

class Menu : public SceneBase {
public:
    Menu();
    ~Menu();

    void update(float deltaTime, float totalTime) override;
    void draw(Renderer& renderer) override;

private:
    std::unique_ptr<Mesh> _cubeMesh;
    Material _cubeMaterial;
    Transform _transform;
};

#endif  // EOCC_MENU_H