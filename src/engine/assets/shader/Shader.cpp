#include "Shader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

/**
 * Constructor
 */
Shader::Shader() {
    _vfProgram = 0;
}

/**
 * Destructor
 */
Shader::~Shader() {
    if (_vfProgram) {
        glDeleteProgram(_vfProgram);
    }
}

/**
 * Чтение исходного кода GLSL из файла
 */
std::string Shader::read(const char* filePath) {
    std::ifstream fileStream(filePath, std::ios::binary);
    if (!fileStream) {
        throw std::runtime_error(std::string("Shader::read: Cannot open file: ") + filePath);
    }
    std::ostringstream ss;
    ss << fileStream.rdbuf();
    return ss.str();
}

/**
 * Создает шейдерную программу
 */
GLuint Shader::createProgram(std::string vertShaderStr, std::string fragShaderStr) {
    GLint vertCompiled;
    GLint fragCompiled;
    GLint linkStatus;

    const char* vertShaderSrc = vertShaderStr.c_str();
    const char* fragShaderSrc = fragShaderStr.c_str();

    // Создает объекты шейдеров. Изначально пустые.
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Загружаем код GLSL из строк в пустые объекты шейдеров
    glShaderSource(vShader, 1, &vertShaderSrc, NULL);
    glShaderSource(fShader, 1, &fragShaderSrc, NULL);

    // *******************************************
    // Компиляция вершинного шейдера
    glCompileShader(vShader);
    checkOpenGLError();

    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
    if (vertCompiled != GL_TRUE) {
        std::cerr << "Vertex shader compilation failed!" << std::endl;
        logCompilation(vShader);
    }
    // -------------------------------------------

    // *******************************************
    // Компиляция фрагментного шейдера
    glCompileShader(fShader);
    checkOpenGLError();

    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
    if (fragCompiled != GL_TRUE) {
        std::cerr << "Fragment shader compilation failed!" << std::endl;
        logCompilation(fShader);
    }
    // -------------------------------------------

    // Создаем пустой объект шейдерной программы
    _vfProgram = glCreateProgram();

    glAttachShader(_vfProgram, vShader);
    glAttachShader(_vfProgram, fShader);

    // *******************************************
    // Linking shaders
    glLinkProgram(_vfProgram);
    checkOpenGLError();

    glGetProgramiv(_vfProgram, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE) {
        std::cerr << "Program link failed!" << std::endl;
        logProgramLink(_vfProgram);
    }
    // -------------------------------------------

    // Очистим ресурсы GPU

    // Когда шейдерная программа готова, удаляем исходные шейдеры

    if (vShader) {
        glDeleteShader(vShader);
    }

    if (fShader) {
        glDeleteShader(fShader);
    }

    return _vfProgram;
}

/**
 * Ошибки компиляции (compilation) GLSL
 */
void Shader::logCompilation(GLuint shader) {
    int len = 0;
    int chWritten = 0;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

    if (len > 0) {
        char* log = static_cast<char*>(malloc(len));

        glGetShaderInfoLog(shader, len, &chWritten, log);
        std::cout << "Shader Info Log: " << log << std::endl;

        free(log);
    }
}

/**
 * Ошибки связывания (linking) GLSL
 */
void Shader::logProgramLink(GLuint prog) {
    int len = 0;
    int chWritten = 0;

    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);

    if (len > 0) {
        char* log = static_cast<char*>(malloc(len));

        glGetProgramInfoLog(prog, len, &chWritten, log);
        std::cout << "Program Info Log: " << log << std::endl;

        free(log);
    }
}

/**
 * Проверяет флаг на наличие ошибки OpenGL
 */
bool Shader::checkOpenGLError() {
    bool foundError = false;
    unsigned int glErr = glGetError();

    while (glErr != GL_NO_ERROR) {
        std::cout << "glError: " << glErr << std::endl;
        foundError = true;
        glErr = glGetError();
    }

    return foundError;
}

// Возвращает шейдерную программу
GLuint Shader::getProgram() const {
    return _vfProgram;
}