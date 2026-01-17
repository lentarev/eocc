//
// Created by Egor Lentarev on 12.01.2026.
//

#ifndef EOCC_TRANSFORM_H
#define EOCC_TRANSFORM_H

#include <glm/gtc/matrix_transform.hpp>

struct Transform {
    glm::vec3 position = {0, 0, 0};
    glm::vec3 rotation = {0, 0, 0};  // в радианах или через quat
    glm::vec3 scale = {1, 1, 1};

    glm::mat4 getModelMatrix() const {
        glm::mat4 mat = glm::mat4(1.0f);
        mat = glm::translate(mat, position);
        mat = glm::rotate(mat, rotation.z, {0, 0, 1});
        mat = glm::rotate(mat, rotation.y, {0, 1, 0});
        mat = glm::rotate(mat, rotation.x, {1, 0, 0});
        mat = glm::scale(mat, scale);

        return mat;
    }
};

#endif  // EOCC_TRANSFORM_H