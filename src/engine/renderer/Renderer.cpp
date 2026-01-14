//
// Created by Egor Lentarev on 03.01.2026.
//

#include "Renderer.h"
#include <engine/assets/shader/Shader.h>
#include <engine/assets/mesh/Mesh.h>
#include <engine/camera/Camera.h>

Renderer::Renderer() {
    _shader = std::make_unique<Shader>();

    _shader->createProgram(_shader->read("./src/engine/assets/shaders/basic.vert"), _shader->read("./src/engine/assets/shaders/basic.frag"));
}

Renderer::~Renderer() {}

/**
 * Begin frame
 */
void Renderer::beginFrame(const Camera& camera, float aspectRatio) {
    _viewMatrix = camera.getViewMatrix();
    _projectionMatrix = camera.getProjectionMatrix(aspectRatio);
    _frameBegun = true;

    // Очистка
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * Renderer
 */
void Renderer::drawMesh(const Mesh& mesh, const Material& material, const glm::mat4& modelMatrix) {
    if (!_frameBegun)
        return;

    glUseProgram(_shader->getProgram());

    // Matrix
    GLuint modelLoc = glGetUniformLocation(_shader->getProgram(), "u_Model");
    GLuint viewLoc = glGetUniformLocation(_shader->getProgram(), "u_View");
    GLuint projLoc = glGetUniformLocation(_shader->getProgram(), "u_Proj");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &modelMatrix[0][0]);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &_viewMatrix[0][0]);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &_projectionMatrix[0][0]);

    // Material: color
    GLuint colorLoc = glGetUniformLocation(_shader->getProgram(), "u_BaseColor");
    glUniform3fv(colorLoc, 1, &material.baseColor[0]);

    // Draw
    glBindVertexArray(mesh.getVAO());
    glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

/**
 * End frame
 */
void Renderer::endFrame() {
    _frameBegun = false;
}