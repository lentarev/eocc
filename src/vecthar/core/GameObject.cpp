#include <vecthar/core/GameObject.h>

#include <vecthar/assets/model/structures/Model.h>
#include <vecthar/renderer/Renderer.h>

namespace vecthar {

GameObject::GameObject() = default;

GameObject::GameObject(std::string n) : name(std::move(n)) {}

GameObject::~GameObject() = default;

/**
 * Add child
 */
GameObject* GameObject::addChild(std::unique_ptr<GameObject> child) {
    GameObject* ptr = child.get();
    ptr->transform.setParent(&transform);
    children.push_back(std::move(child));
    return ptr;
}

/**
 * Render 3D
 */
void GameObject::render(vecthar::Renderer& renderer) {
    if (model) {
        for (const auto& mesh : model->meshes) {
            renderer.drawMesh(*mesh, mesh->getMaterial(), transform.getWorldMatrix());
        }
    }
    for (auto& child : children) {
        child->render(renderer);
    }
}

/**
 * Render shadow
 */
void GameObject::renderShadow(vecthar::Renderer& renderer, GLuint depthProgram) {
    if (model) {
        for (const auto& mesh : model->meshes) {
            renderer.drawShadowMesh(*mesh, transform.getWorldMatrix());
        }
    }
    for (auto& child : children) {
        child->renderShadow(renderer, depthProgram);
    }
}

void GameObject::markTransformHierarchyDirty() {
    transform._worldDirty = true;
    for (auto& child : children) {
        child->markTransformHierarchyDirty();
    }
}

}  // namespace vecthar