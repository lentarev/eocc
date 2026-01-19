//
// Created by Egor Lentarev on 05.01.2026.
//

#ifndef VECTHAR_SHADER_H
#define VECTHAR_SHADER_H

#include <iostream>
#include <string>
#include <vecthar/base/OpenGLTypes.h>

/**
 * @brief Manages an OpenGL shader program (vertex + fragment).
 *
 * Loads, compiles, and links GLSL shaders from files.
 * Non-copyable due to GPU resource ownership.
 */

namespace vecthar {

class Shader {
public:
    // Constructor
    Shader();

    // Non-copyable: OpenGL resources cannot be shared by copy.
    Shader(const Shader&) = delete;

    // Non-copyable and non-movable (OpenGL program objects are unique)
    Shader& operator=(const Shader&) = delete;

    // Destructor
    ~Shader();

    // Reading GLSL source code from a file
    std::string read(const char* filePath);

    // Creates a shader program
    GLuint createProgram(std::string vertShaderStr, std::string fragShaderStr);

    // Returns the shader program
    GLuint getProgram() const;

protected:
    // GLSL compilation errors
    void logCompilation(GLuint shader);

    // GLSL linking errors
    void logProgramLink(GLuint prog);

    // Checks the flag for an OpenGL error.
    bool checkOpenGLError();

    GLuint _vfProgram;
};

}  // namespace vecthar

#endif  // VECTHAR_SHADER_H