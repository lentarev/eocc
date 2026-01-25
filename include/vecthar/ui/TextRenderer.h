//
// Created by Egor Lentarev on 24.01.2026.
//

#ifndef VECTHAR_TEXT_RENDERER_H
#define VECTHAR_TEXT_RENDERER_H

#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <string>
#include <vecthar/base/OpenGLTypes.h>

// Forward declaration of classes
namespace vecthar {

class Shader;

}  // namespace vecthar

namespace vecthar::ui {

class TextRenderer {
public:
    TextRenderer();
    ~TextRenderer();

    void loadFontAtlas(const char* path);
    void beginFrame(const glm::mat4& projMatrix);
    void renderText(const std::string& text, float x, float y, float scale = 1.0f, const glm::vec3& color = glm::vec3(1.0f));
    void endFrame();

private:
    struct Vertex {
        float x, y;     // position
        float u, v;     // tex coord
        float r, g, b;  // color
    };

    void flush();

    GLuint _vao = 0;
    GLuint _vbo = 0;
    GLuint _texture = 0;
    GLuint _program = 0;

    std::vector<Vertex> _buffer;
    glm::mat4 _projMatrix;
    bool _isRendering = false;

    static constexpr size_t MAX_VERTICES = 6000;  // ~1000 symbols

    std::unique_ptr<vecthar::Shader> _shader;
};

}  // namespace vecthar::ui

#endif  // VECTHAR_TEXT_RENDERER_H