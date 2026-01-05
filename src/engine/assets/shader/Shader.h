//
// Created by Egor Lentarev on 05.01.2026.
//

#ifndef EOCC_SHADER_H
#define EOCC_SHADER_H

#include <glad/glad.h>
#include <iostream>
#include <string>

class Shader {
private:
    /* data */
public:
    // Constructor
    Shader();

    // Запрещаем копирование
    Shader(const Shader&) = delete;

    // Запрещаем присваивания
    Shader& operator=(const Shader&) = delete;

    // Destructor
    ~Shader();

    // Чтение исходного кода GLSL из файла
    std::string read(const char* filePath);

    // Создает шейдерную программу
    GLuint createProgram(std::string vertShaderStr, std::string fragShaderStr);

    GLuint getProgram() const;

protected:
    // Ошибки компиляции (compilation) GLSL
    void logCompilation(GLuint shader);

    // Ошибки связывания (linking) GLSL
    void logProgramLink(GLuint prog);

    // Проверяет флаг на наличие ошибки OpenGL
    bool checkOpenGLError();

    GLuint _vfProgram;
};

#endif  // EOCC_SHADER_H