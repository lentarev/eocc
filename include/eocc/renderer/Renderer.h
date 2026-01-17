//
// Created by Egor Lentarev on 03.01.2026.
//

#ifndef EOCC_RENDERER_H
#define EOCC_RENDERER_H

#include <glad/glad.h>
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <eocc/assets/material/Material.h>

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

#endif  // EOCC_RENDERER_H