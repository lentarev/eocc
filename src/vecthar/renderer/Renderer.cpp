//
// Created by Egor Lentarev on 03.01.2026.
//

#include <vecthar/renderer/Renderer.h>
#include <vecthar/assets/mesh/Mesh.h>
#include <vecthar/camera/Camera.h>
#include <vecthar/ui/TextRenderer.h>

#include <glad/glad.h>

namespace vecthar {

Renderer::Renderer() {}

Renderer::~Renderer() = default;

void Renderer::useShaderProgram(GLuint program) {
    _program = program;
}

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
 * End frame
 */
void Renderer::endFrame() {
    _frameBegun = false;
}

/**
 * Renderer
 */
void Renderer::drawMesh(const Mesh& mesh, const Material& material, const glm::mat4& modelMatrix) {
    if (!_frameBegun)
        return;

    glUseProgram(_program);

    // Matrix
    GLuint modelLoc = glGetUniformLocation(_program, "u_Model");
    GLuint viewLoc = glGetUniformLocation(_program, "u_View");
    GLuint projLoc = glGetUniformLocation(_program, "u_Proj");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &modelMatrix[0][0]);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &_viewMatrix[0][0]);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &_projectionMatrix[0][0]);

    // Material: color
    GLuint colorLoc = glGetUniformLocation(_program, "u_BaseColor");
    glUniform3fv(colorLoc, 1, &material.baseColor[0]);

    // Draw
    glBindVertexArray(mesh.getVAO());
    glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

/**
 * Draw text
 */
void Renderer::drawText(const std::string& text, float x, float y, float scale, const glm::vec3& color) {
    if (_textRenderer) {
        _textRenderer->renderText(text, x, y, scale, color);
    }
}

/**
 * Begin ui frame
 */
void Renderer::beginUIFrame(int width, int height) {
    glm::mat4 ortho = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
    if (_textRenderer) {
        _textRenderer->beginFrame(ortho);
    }
}

/**
 * End ui frame
 */
void Renderer::endUIFrame() {
    if (_textRenderer) {
        _textRenderer->endFrame();
    }
}

}  // namespace vecthar