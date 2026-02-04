//
// Created by Egor Lentarev on 03.01.2026.
//

#include <vecthar/renderer/Renderer.h>
#include <vecthar/renderer/ShadowMap.h>
#include <vecthar/assets/mesh/Mesh.h>
#include <vecthar/camera/Camera.h>
#include <vecthar/ui/TextRenderer.h>

#include <glad/glad.h>
#include <iostream>

namespace vecthar {

/**
 * Constructor
 */
Renderer::Renderer(int width, int height) : _windowWidth(width), _windowHeight(height) {
    _textRenderer = std::make_unique<ui::TextRenderer>();
    _textRenderer->loadFontAtlas("./core_assets/fonts/font8x8_atlas_1024x8.png");

    _shadowMap = std::make_unique<ShadowMap>(2048, 2048);
}

/**
 * Destructor
 */
Renderer::~Renderer() = default;

/**
 * Use shader program
 */
void Renderer::useShaderProgram(GLuint program) {
    _program = program;
    glUseProgram(program);
}

/**
 * Begin shadow pass
 */
void Renderer::beginShadowPass() {
    _shadowMap->bindForWriting();
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
}

/**
 * End shadow pass
 */
void Renderer::endShadowPass() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, _windowWidth, _windowHeight);
    glDepthFunc(GL_LESS);
}

/**
 * Draw shadow mesh
 */
void Renderer::drawShadowMesh(const Mesh& mesh, const glm::mat4& modelMatrix) {
    // We pass the model matrix
    GLint modelLoc = glGetUniformLocation(_program, "u_Model");
    if (modelLoc != -1) {
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &modelMatrix[0][0]);
    }

    // Drawing a mesh
    glBindVertexArray(mesh.getVAO());

    if (mesh.hasIndices()) {
        glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, nullptr);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, mesh.getVertexCount());
    }

    GLenum err = glGetError();
    if (err)
        std::cout << "OpenGL error: " << err << "\n";

    glBindVertexArray(0);
}

/**
 * Begin frame
 */
void Renderer::beginFrame(const Camera& camera, int width, int height) {
    _windowWidth = width;
    _windowHeight = height;

    float aspectRatio = static_cast<float>(width) / height;

    glViewport(0, 0, _windowWidth, _windowHeight);

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

    // Matrix
    GLuint modelLoc = glGetUniformLocation(_program, "u_Model");
    GLuint viewLoc = glGetUniformLocation(_program, "u_View");
    GLuint projLoc = glGetUniformLocation(_program, "u_Proj");

    // Directional light
    GLuint lightDirLoc = glGetUniformLocation(_program, "u_LightDir");
    GLuint lightColor = glGetUniformLocation(_program, "u_LightColor");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &modelMatrix[0][0]);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &_viewMatrix[0][0]);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &_projectionMatrix[0][0]);

    // For directional light
    glUniform3fv(lightDirLoc, 1, &_directionalLight.direction[0]);
    glUniform3fv(lightColor, 1, &(_directionalLight.color * _directionalLight.intensity)[0]);

    // Shadow mapping

    GLint shadowMapLoc = glGetUniformLocation(_program, "u_ShadowMap");
    GLint lightSpaceLoc = glGetUniformLocation(_program, "u_LightSpaceMatrix");

    if (shadowMapLoc != -1) {
        _shadowMap->bindForReading(GL_TEXTURE1);
        glUniform1i(shadowMapLoc, 1);  // 1 = GL_TEXTURE1
    }

    if (lightSpaceLoc != -1) {
        glUniformMatrix4fv(lightSpaceLoc, 1, GL_FALSE, &_lightSpaceMatrix[0][0]);
    }

    // Material: base color (RGBA)
    GLuint colorLoc = glGetUniformLocation(_program, "u_BaseColor");
    glUniform4f(colorLoc, material.baseColor.r, material.baseColor.g, material.baseColor.b, material.baseColor.a);

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

/**
 * Set directional light
 */
void Renderer::setDirectionalLight(const DirectionalLight& light) {
    _directionalLight = light;
}

/**
 * Get directional light
 */
const DirectionalLight& Renderer::getDirectionalLight() const {
    return _directionalLight;
}

/**
 * Set light space matrix
 */
void Renderer::setLightSpaceMatrix(const glm::mat4& matrix) {
    _lightSpaceMatrix = matrix;
}

}  // namespace vecthar