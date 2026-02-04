//
// Created by Egor Lentarev on 03.02.2026.
//

#include <vecthar/renderer/ShadowMap.h>
#include <glad/glad.h>
#include <iostream>

namespace vecthar {

ShadowMap::ShadowMap(int width, int height) : _width(width), _height(height) {
    // Create depth texture
    glGenTextures(1, &_depthTexture);
    glBindTexture(GL_TEXTURE_2D, _depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, _width, _height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Create framebuffer
    glGenFramebuffers(1, &_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthTexture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Error: Shadow FBO is not complete!\n";
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Setup projection matrix
    _lightProjection = glm::ortho(-DEFAULT_ORTHO_SIZE, DEFAULT_ORTHO_SIZE, -DEFAULT_ORTHO_SIZE, DEFAULT_ORTHO_SIZE, DEFAULT_NEAR, DEFAULT_FAR);
}

ShadowMap::~ShadowMap() {
    _cleanup();
}

void ShadowMap::_cleanup() {
    if (_fbo) {
        glDeleteFramebuffers(1, &_fbo);
        _fbo = 0;
    }
    if (_depthTexture) {
        glDeleteTextures(1, &_depthTexture);
        _depthTexture = 0;
    }
}

// Move semantics
ShadowMap::ShadowMap(ShadowMap&& other) noexcept
    : _width(other._width), _height(other._height), _fbo(other._fbo), _depthTexture(other._depthTexture), _lightProjection(other._lightProjection) {
    other._fbo = 0;
    other._depthTexture = 0;
}

ShadowMap& ShadowMap::operator=(ShadowMap&& other) noexcept {
    if (this != &other) {
        _cleanup();
        _width = other._width;
        _height = other._height;
        _fbo = other._fbo;
        _depthTexture = other._depthTexture;
        _lightProjection = other._lightProjection;
        other._fbo = 0;
        other._depthTexture = 0;
    }
    return *this;
}

void ShadowMap::bindForWriting() const {
    glViewport(0, 0, _width, _height);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void ShadowMap::bindForReading(GLenum textureUnit) const {
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, _depthTexture);
}

}  // namespace vecthar