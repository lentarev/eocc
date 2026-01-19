//
// Created by Egor Lentarev on 03.01.2026.
//

#ifndef VECTHAR_RENDERER_H
#define VECTHAR_RENDERER_H

#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <vecthar/assets/material/Material.h>

#include <vecthar/base/OpenGLTypes.h>

namespace vecthar {

// Forward declaration of classes
class Mesh;
class Camera;

class Renderer {
public:
    Renderer();
    ~Renderer();

    /// Begin frame
    void beginFrame(const Camera& camera, float aspectRatio);

    /// @brief Draw mesh
    /// @param mesh
    /// @param material
    /// @param modelMatrix
    void drawMesh(const Mesh& mesh, const Material& material, const glm::mat4& modelMatrix);

    /// End frame (optional)
    void endFrame();

    void useShaderProgram(GLuint program);

private:
    GLuint _program = 0;

    glm::mat4 _viewMatrix;
    glm::mat4 _projectionMatrix;

    bool _frameBegun = false;
};

}  // namespace vecthar

#endif  // VECTHAR_RENDERER_H