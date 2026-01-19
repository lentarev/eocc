//
// Created by Egor Lentarev on 12.01.2026.
//

#ifndef VECTHAR_MATERIAL_H
#define VECTHAR_MATERIAL_H

#include <glm/gtc/matrix_transform.hpp>

namespace vecthar {

struct Material {
    glm::vec3 baseColor = {1.0f, 1.0f, 1.0f};
    float roughness = 1.0f;
    // Later: enum Type { LIT, UNLIT, PBR, WIREFRAME };
};

}  // namespace vecthar

#endif  // VECTHAR_MATERIAL_H