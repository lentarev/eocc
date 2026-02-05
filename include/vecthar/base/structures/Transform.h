//
// Created by Egor Lentarev on 12.01.2026.
//

#ifndef VECTHAR_TRANSFORM_H
#define VECTHAR_TRANSFORM_H

#include <glm/gtc/matrix_transform.hpp>
#include <vector>

namespace vecthar {

struct Transform {
    glm::vec3 position = {0, 0, 0};
    glm::vec3 rotation = {0, 0, 0};  // в радианах или через quat
    glm::vec3 scale = {1, 1, 1};

    // Hierarchy
    Transform* parent = nullptr;

    // Caching the world matrix
    mutable bool _worldDirty = true;
    mutable glm::mat4 _worldMatrix = glm::mat4(1.0f);

    // Get the local matrix
    glm::mat4 getModelMatrix() const {
        glm::mat4 mat = glm::mat4(1.0f);
        mat = glm::translate(mat, position);
        mat = glm::rotate(mat, rotation.z, {0, 0, 1});
        mat = glm::rotate(mat, rotation.y, {0, 1, 0});
        mat = glm::rotate(mat, rotation.x, {1, 0, 0});
        mat = glm::scale(mat, scale);

        return mat;
    }

    // Получить мировую матрицу с учётом родителя
    glm::mat4 getWorldMatrix() const {
        if (!_worldDirty) {
            return _worldMatrix;
        }

        if (parent) {
            _worldMatrix = parent->getWorldMatrix() * getModelMatrix();
        } else {
            _worldMatrix = getModelMatrix();
        }

        _worldDirty = false;
        return _worldMatrix;
    }

    // Пометить себя и "потомков" как грязные
    void markWorldDirty() { _worldDirty = true; }

    // Set parent
    void setParent(Transform* newParent) {
        parent = newParent;
        markWorldDirty();
    }
};

}  // namespace vecthar

#endif  // VECTHAR_TRANSFORM_H