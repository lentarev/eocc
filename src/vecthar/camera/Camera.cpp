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
    if (_projectionType == ProjectionType::Perspective) {
        return glm::perspective(_fov, aspectRatio, _near, _far);
    } else {
        // Для ортографии aspectRatio не нужен — границы заданы явно
        return glm::ortho(_orthoLeft, _orthoRight, _orthoBottom, _orthoTop, _near, _far);
    }
}

void Camera::setOrthographic(float left, float right, float bottom, float top, float near, float far) {
    _orthoLeft = left;
    _orthoRight = right;
    _orthoBottom = bottom;
    _orthoTop = top;
    _near = near;
    _far = far;
}

}  // namespace vecthar