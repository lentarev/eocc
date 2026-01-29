//
// Created by Egor Lentarev on 03.01.2026.
//

#include <vecthar/renderer/Renderer.h>
#include <vecthar/assets/mesh/Mesh.h>
#include <vecthar/camera/Camera.h>
#include <vecthar/ui/TextRenderer.h>

#include <glad/glad.h>
#include <iostream>

namespace vecthar {

/**
 * Constructor
 */
Renderer::Renderer() {
    _textRenderer = std::make_unique<ui::TextRenderer>();
    _textRenderer->loadFontAtlas("./sys_assets/fonts/font8x8_atlas_1024x8.png");
}

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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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

    if (mesh.hasIndices()) {
        glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, mesh.getVertexCount());
    }

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
    // Save the current state
    GLboolean depthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
    GLboolean cullFaceEnabled = glIsEnabled(GL_CULL_FACE);
    GLboolean blendEnabled = glIsEnabled(GL_BLEND);

    _prevDepthTest = depthTestEnabled;
    _prevCullFace = cullFaceEnabled;
    _prevBlend = blendEnabled;

    // Setting up UI state
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

    // Restoring the previous state
    if (_prevDepthTest)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
    if (_prevCullFace)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);
    if (_prevBlend)
        glEnable(GL_BLEND);
    else
        glDisable(GL_BLEND);
}

}  // namespace vecthar