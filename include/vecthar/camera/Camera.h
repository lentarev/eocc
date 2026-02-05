//
// Created by Egor Lentarev on 13.01.2026.
//

#ifndef VECTHAR_CAMERA_H
#define VECTHAR_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace vecthar {

class Camera {
public:
    enum class ProjectionType { Perspective, Orthographic };

    Camera();

    // view matrix
    glm::mat4 getViewMatrix() const;

    // perspective matrix
    glm::mat4 getProjectionMatrix(float aspectRatio) const;

    // Set the camera position
    void setPosition(const glm::vec3& pos) { _position = pos; }

    // Set the point the camera is looking at
    void setTarget(const glm::vec3& target) { _target = target; }

    // For orthographic
    void setOrthographic(float left, float right, float bottom, float top, float near = 0.1f, float far = 100.0f);
    void setProjectionType(ProjectionType type) { _projectionType = type; }
    void setUp(const glm::vec3& up) { _up = up; }

private:
    glm::vec3 _position = glm::vec3(0.0f, 0.0f, 5.0f);  // slightly offset from the center
    glm::vec3 _target = glm::vec3(0.0f, 0.0f, 0.0f);    // looks at the center
    glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f);        // up

    // Перспектива
    float _fov = glm::radians(60.0f);  // field of view
    float _near = 0.1f;
    float _far = 100.0f;

    // Ортография
    float _orthoLeft = -10.0f;
    float _orthoRight = 10.0f;
    float _orthoBottom = -10.0f;
    float _orthoTop = 10.0f;

    ProjectionType _projectionType = ProjectionType::Perspective;
};

}  // namespace vecthar

#endif  // VECTHAR_CAMERA_H