//
// Created by Egor Lentarev on 03.02.2026.
//

#include <vecthar/lighting/shadow_utils.h>
#include <glm/gtc/matrix_transform.hpp>

namespace vecthar {
/**
 * Calculate light space matrix for directional shadow mapping.
 */
glm::mat4 calculate_light_space_matrix(const DirectionalLight& light, const glm::vec3& sceneCenter, float sceneSize, float near, float far) {
    glm::mat4 lightProjection = glm::ortho(-sceneSize, sceneSize, -sceneSize, sceneSize, near, far);

    glm::vec3 lightPos = sceneCenter - light.direction * (far - near) * 0.5f;
    glm::mat4 lightView = glm::lookAt(lightPos, sceneCenter, glm::vec3(0.0f, 1.0f, 0.0f));

    return lightProjection * lightView;
}
}  // namespace vecthar