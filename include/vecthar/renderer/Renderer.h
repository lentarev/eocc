//
// Created by Egor Lentarev on 03.01.2026.
//

#ifndef VECTHAR_RENDERER_H
#define VECTHAR_RENDERER_H

#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <vecthar/assets/material/Material.h>

#include <vecthar/base/OpenGLTypes.h>

// Forward declaration of classes
namespace vecthar::ui {

class TextRenderer;

}

namespace vecthar {

// Forward declaration of classes
class Mesh;
class Camera;

class Renderer {
public:
    Renderer();
    ~Renderer();

    /// @brief Use shader program
    /// @param program
    void useShaderProgram(GLuint program);

    // 3D
    /// Begin frame
    void beginFrame(const Camera& camera, float aspectRatio);

    /// End frame (optional)
    void endFrame();

    /// @brief Draw mesh
    /// @param mesh
    /// @param material
    /// @param modelMatrix
    void drawMesh(const Mesh& mesh, const Material& material, const glm::mat4& modelMatrix);

    // 2D
    /// @brief Begin UI frame
    /// @param windowWidth
    /// @param windowHeight
    void beginUIFrame(int windowWidth, int windowHeight);

    /// @brief End UI frame
    void endUIFrame();

    // Optional: Method for rendering text

    /// @brief Draw text
    /// @param text
    /// @param x
    /// @param y
    /// @param color
    void drawText(const std::string& text, float x, float y, float scale = 1.0f, const glm::vec3& color = {1.0f, 1.0f, 1.0f});

private:
    GLuint _program = 0;

    glm::mat4 _viewMatrix;
    glm::mat4 _projectionMatrix;

    bool _frameBegun = false;

    // Text renderer
    std::unique_ptr<vecthar::ui::TextRenderer> _textRenderer;

    GLboolean _prevDepthTest, _prevCullFace, _prevBlend;
};

}  // namespace vecthar

#endif  // VECTHAR_RENDERER_H