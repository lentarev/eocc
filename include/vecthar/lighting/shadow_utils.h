//
// Created by Egor Lentarev on 03.02.2026.
//

#ifndef VECTHAR_SHADOW_UTILS_H
#define VECTHAR_SHADOW_UTILS_H

#include <glm/mat4x4.hpp>
#include <vecthar/lighting/DirectionalLight.h>

namespace vecthar {

/// @brief Calculate light space matrix for directional shadow mapping.
/// @param light
/// @param sceneCenter
/// @param sceneSize
/// @param
/// @param
/// @return
glm::mat4 calculate_light_space_matrix(const DirectionalLight& light,
                                       const glm::vec3& sceneCenter = glm::vec3(0.0f),
                                       float sceneSize = 15.0f,
                                       float near = 1.0f,
                                       float far = 50.0f);

}  // namespace vecthar

#endif  // VECTHAR_SHADOW_UTILS_H