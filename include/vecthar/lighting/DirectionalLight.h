//
// Created by Egor Lentarev on 02.02.2026.
//

#ifndef VECTHAR_DIRECTIONAL_LIGHT_H
#define VECTHAR_DIRECTIONAL_LIGHT_H

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

namespace vecthar {

struct DirectionalLight {
    glm::vec3 direction = glm::normalize(glm::vec3(-0.7f, -1.0f, -0.7f));
    glm::vec3 color = glm::vec3(1.0f);
    float intensity = 1.0f;
};

}  // namespace vecthar

#endif  // VECTHAR_DIRECTIONAL_LIGHT_H
