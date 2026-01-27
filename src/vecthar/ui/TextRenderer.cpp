//
// Created by Egor Lentarev on 24.01.2026.
//

#include <vecthar/ui/TextRenderer.h>
#include <vecthar/assets/shader/Shader.h>

#include <SOIL2/SOIL2.h>
#include <glad/glad.h>

#include <iostream>

namespace vecthar::ui {

/**
 * Constructor
 */
TextRenderer::TextRenderer() {
    _shader = std::make_unique<vecthar::Shader>();
    _shader->createProgram(_shader->read("./sys_shaders/ui/text.vert"), _shader->read("./sys_shaders/ui/text.frag"));

    if (_shader->getProgram() == 0) {
        std::cerr << "Shader failed to load!\n";
        return;
    }

    // // Create VAO/VBO
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(4 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

/**
 * Destructor
 */
TextRenderer::~TextRenderer() {
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);

    if (_texture)
        glDeleteTextures(1, &_texture);
}

/**
 * Load font atlas
 */
void TextRenderer::loadFontAtlas(const char* path) {
    int width, height, channels;
    unsigned char* data = SOIL_load_image(path, &width, &height, &channels, 1);  // 1 канал

    if (!data) {
        std::cerr << "Failed to load image: " << path << "\n";
        return;
    }

    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

    // Используем GL_RED (Core Profile совместимый)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(data);
}

/**
 * Begin frame
 */
void TextRenderer::beginFrame(const glm::mat4& projMatrix) {
    _projMatrix = projMatrix;
    _buffer.clear();
    _isRendering = true;
}

/**
 * Text rendere
 */
void TextRenderer::renderText(const std::string& text, float x, float y, float scale, const glm::vec3& color) {
    if (!_isRendering || !_texture || !_shader)
        return;

    float cursorX = x;
    const float charWidth = 8.0f * scale;
    const float charHeight = 8.0f * scale;
    const float yOffset = 2.0f * scale;

    for (unsigned char c : text) {
        // std::cout << "Char: '" << c << "' (code=" << (int)c << ")\n";

        if (c < 0 || c >= 128)
            // std::cout << "  → skipped\n";
            continue;

        // UV в атласе 1024x8
        float u0 = (c * 8.0f) / 1024.0f;
        float u1 = ((c + 1) * 8.0f) / 1024.0f;
        float v0 = 1.0f;
        float v1 = 0.0f;

        // Позиции
        float x0 = cursorX;
        float y0 = y - yOffset;
        float x1 = cursorX + charWidth;
        float y1 = y - yOffset + charHeight;

        // Добавляем 6 вершин (2 треугольника)
        _buffer.insert(_buffer.end(), {
                                          {x0, y0, u0, v1, color.r, color.g, color.b},  // BL
                                          {x1, y0, u1, v1, color.r, color.g, color.b},  // BR
                                          {x1, y1, u1, v0, color.r, color.g, color.b},  // TR

                                          {x0, y0, u0, v1, color.r, color.g, color.b},  // BL
                                          {x1, y1, u1, v0, color.r, color.g, color.b},  // TR
                                          {x0, y1, u0, v0, color.r, color.g, color.b}   // TL
                                      });

        cursorX += charWidth;

        if (_buffer.size() >= MAX_VERTICES - 6) {
            flush();
            _buffer.clear();
        }
    }
}

/**
 * End frame
 */
void TextRenderer::endFrame() {
    if (_isRendering && !_buffer.empty()) {
        flush();
    }
    _isRendering = false;
}

/**
 * Flush
 */
void TextRenderer::flush() {
    if (_buffer.empty())
        return;

    glUseProgram(_shader->getProgram());
    glUniformMatrix4fv(glGetUniformLocation(_shader->getProgram(), "u_Proj"), 1, GL_FALSE, &_projMatrix[0][0]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, _buffer.size() * sizeof(Vertex), _buffer.data());
    glDrawArrays(GL_TRIANGLES, 0, _buffer.size());
    // glDrawArrays(GL_POINTS, 0, _buffer.size());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

}  // namespace vecthar::ui
