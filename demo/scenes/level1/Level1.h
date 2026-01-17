//
// Created by Egor Lentarev on 06.01.2026.
//

#ifndef EOCC_LEVEL1_H
#define EOCC_LEVEL1_H

#include <memory>
#include <string>

#include <eocc/scene/base/SceneBase.h>
#include <eocc/assets/material/Material.h>
#include <eocc/base/structures/Transform.h>

// Forward declaration of classes
class Mesh;
class Renderer;
class Shader;

class Level1 : public SceneBase {
public:
    Level1();
    ~Level1();

    void update(float deltaTime, float totalTime) override;
    void draw(Renderer& renderer) override;
    void onKey(int key, int scancode, int action, int mods) override;

private:
    std::unique_ptr<Mesh> _cubeMesh;
    std::unique_ptr<Shader> _shader;
    Material _cubeMaterial;
    Transform _transform;
};

#endif  // EOCC_LEVEL1_H