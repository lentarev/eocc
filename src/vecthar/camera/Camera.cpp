//
// Created by Egor Lentarev on 13.01.2026.
//

#include <vecthar/camera/Camera.h>

namespace vecthar {

Camera::Camera() = default;

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(_position, _target, _up);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
    return glm::perspective(_fov, aspectRatio, _near, _far);
}

}  // namespace vecthar