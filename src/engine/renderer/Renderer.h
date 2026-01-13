//
// Created by Egor Lentarev on 03.01.2026.
//

#ifndef EOCC_RENDERER_H
#define EOCC_RENDERER_H

#include <glad/glad.h>
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <engine/assets/material/Material.h>

// Forward declaration of classes
class Shader;
class Mesh;

class Renderer {
public:
    Renderer();
    ~Renderer();

    void drawMesh(const Mesh& mesh, const Material& material, const glm::mat4& modelMatrix);

private:
    std::unique_ptr<Shader> _shader;

    // Shader programs
    GLuint _mainShaderProgram;
};

#endif  // EOCC_RENDERER_H