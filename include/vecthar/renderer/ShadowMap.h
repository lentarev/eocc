//
// Created by Egor Lentarev on 03.02.2026.
//

#ifndef VECTHAR_SHADOW_MAP_H
#define VECTHAR_SHADOW_MAP_H

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vecthar/base/OpenGLTypes.h>

namespace vecthar {

class ShadowMap {
public:
    /// @brief Creates and initializes a shadow map with given resolution.
    /// @param width Shadow map width (default: 2048)
    /// @param height Shadow map height (default: 2048)
    explicit ShadowMap(int width = 2048, int height = 2048);

    ~ShadowMap();

    // Non-copyable
    ShadowMap(const ShadowMap&) = delete;
    ShadowMap& operator=(const ShadowMap&) = delete;

    // Move support (optional but recommended)
    ShadowMap(ShadowMap&& other) noexcept;
    ShadowMap& operator=(ShadowMap&& other) noexcept;

    /// @brief Binds the framebuffer for depth rendering.
    void bindForWriting() const;

    /// @brief Binds the depth texture for sampling in shaders.
    /// @param textureUnit GL_TEXTURE0, GL_TEXTURE1, etc.
    void bindForReading(GLenum textureUnit) const;

    /// @brief Returns the orthographic projection matrix used for shadow mapping.
    glm::mat4 getProjectionMatrix() const { return _lightProjection; }

    /// @brief Returns the depth texture ID.
    GLuint getTexture() const { return _depthTexture; }

    /// @brief Returns the framebuffer object ID.
    GLuint getFBO() const { return _fbo; }

    int getWidth() const { return _width; }
    int getHeight() const { return _height; }

private:
    void _cleanup();

    int _width;
    int _height;

    GLuint _fbo = 0;
    GLuint _depthTexture = 0;

    glm::mat4 _lightProjection;

    static constexpr float DEFAULT_NEAR = 1.0f;
    static constexpr float DEFAULT_FAR = 100.0f;
    static constexpr float DEFAULT_ORTHO_SIZE = 50.0f;
};

}  // namespace vecthar

#endif  // VECTHAR_SHADOW_MAP_H