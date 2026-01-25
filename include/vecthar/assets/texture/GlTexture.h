//
// Created by Egor Lentarev on 18.01.2026.
//

#ifndef VECTHAR_GL_TEXTURE_H
#define VECTHAR_GL_TEXTURE_H

#include <glad/glad.h>
#include <SOIL2/SOIL2.h>
#include <iostream>

namespace vecthar {
class GlTexture {
public:
    // Конструктор по умолчанию (пустая текстура)
    GlTexture() = default;

    // Конструктор из пути к файлу
    explicit GlTexture(const char* path) { load(path); }

    // Запрещаем копирование
    GlTexture(const GlTexture&) = delete;
    GlTexture& operator=(const GlTexture&) = delete;

    // Разрешаем перемещение
    GlTexture(GlTexture&& other) noexcept : _id(other._id) { other._id = 0; }
    GlTexture& operator=(GlTexture&& other) noexcept {
        if (this != &other) {
            if (_id)
                glDeleteTextures(1, &_id);
            _id = other._id;
            other._id = 0;
        }
        return *this;
    }

    // Деструктор
    ~GlTexture() {
        if (_id)
            glDeleteTextures(1, &_id);
    }

    // Загрузка текстуры
    bool load(const char* path) {
        if (_id)
            glDeleteTextures(1, &_id);

        // SOIL2 сам генерирует мипмапы при SOIL_FLAG_MIPMAPS
        _id = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB);

        if (!_id) {
            std::cout << "Ошибка загрузки текстуры: " << path << std::endl;
            return false;
        }

        glBindTexture(GL_TEXTURE_2D, _id);

        // Обязательно: проверим, что мипмапы есть
        GLint mipmaps = 0;
        glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, &mipmaps);
        if (mipmaps <= 0) {
            // Если SOIL2 не сгенерировал — сделаем сами
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        // Фильтрация
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);  // ← мипмапы!
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Anisotropic filtering (важно для земли под углом!)
        GLfloat maxAniso = 0.0f;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
        if (maxAniso > 0.0f) {
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAniso);
        }

        glBindTexture(GL_TEXTURE_2D, 0);
        return true;
    }

    GLuint id() const { return _id; }
    explicit operator bool() const { return _id != 0; }

private:
    GLuint _id = 0;
};
}  // namespace vecthar

#endif  // VECTHAR_GL_TEXTURE_H