//
// Created by Egor Lentarev on 05.02.2026.
//

#ifndef VECTHAR_GAME_OBJECT_H
#define VECTHAR_GAME_OBJECT_H

#include <vecthar/base/structures/Transform.h>

#include <memory>
#include <string>
#include <vector>

#include <vecthar/base/OpenGLTypes.h>

namespace vecthar {

struct Model;
class Renderer;

class GameObject {
public:
    GameObject();
    GameObject(std::string n);
    ~GameObject();

    std::string name;
    Transform transform;
    std::unique_ptr<Model> model;
    std::vector<std::unique_ptr<GameObject>> children;

    /// @brief Add child
    /// @param child
    /// @return
    GameObject* addChild(std::unique_ptr<GameObject> child);

    void render(vecthar::Renderer& renderer);
    void renderShadow(vecthar::Renderer& renderer, GLuint depthProgram);
    void markTransformHierarchyDirty();
};

}  // namespace vecthar

#endif  // VECTHAR_GAME_OBJECT_H