//
// Created by Egor Lentarev on 13.01.2026.
//

#ifndef EOCC_CAMERA_H
#define EOCC_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera();

    // view matrix
    glm::mat4 getViewMatrix() const;

    // perspective matrix
    glm::mat4 getProjectionMatrix(float aspectRatio) const;

    // Set the camera position
    void setPosition(const glm::vec3& pos) { _position = pos; }

    // Set the point the camera is looking at
    void setTarget(const glm::vec3& target) { _target = target; }

private:
    glm::vec3 _position = glm::vec3(0.0f, 0.0f, 5.0f);  // slightly offset from the center
    glm::vec3 _target = glm::vec3(0.0f, 0.0f, 0.0f);    // looks at the center
    glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f);        // up

    float _fov = glm::radians(60.0f);  // field of view
    float _near = 0.1f;
    float _far = 100.0f;
};

#endif  // EOCC_CAMERA_H