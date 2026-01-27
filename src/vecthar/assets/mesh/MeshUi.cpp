//
// Created by Egor Lentarev on 25.01.2026.
//

#include <vecthar/assets/mesh/MeshUi.h>
#include <cstddef>

#include <glad/glad.h>

namespace vecthar {

/**
 * Constructor
 */
MeshUi::MeshUi(const MeshUiData& data) : _indices(data.indices) {
    uploadToGPU(data);
}

/**
 * Destructor
 */
MeshUi::~MeshUi() {
    // 1. Delete VAO
    if (_vao) {
        glDeleteVertexArrays(1, &_vao);
        _vao = 0;
    }

    // 2. Delete all buffers
    if (_vbo) {
        glDeleteBuffers(1, &_vbo);
        _vbo = 0;
    }

    if (_ebo) {
        glDeleteBuffers(1, &_ebo);
        _ebo = 0;
    }

    if (_tbo) {
        glDeleteBuffers(1, &_tbo);
        _tbo = 0;
    }
}

void MeshUi::uploadToGPU(const MeshUiData& data) {
    const size_t vertexByteSize = data.positions.empty() ? 0 : data.positions.size() * sizeof(data.positions[0]);
    const GLsizei indicesByteSize = data.indices.empty() ? 0 : data.indices.size() * sizeof(data.indices[0]);

    // Generate VAO
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    // Vertex (location = 0)
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexByteSize, data.positions.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Textute (location = 1)
    if (!data.texCoords.empty()) {
        const size_t textureByteSize = data.texCoords.size() * sizeof(data.texCoords[0]);

        glGenBuffers(1, &_tbo);
        glBindBuffer(GL_ARRAY_BUFFER, _tbo);
        glBufferData(GL_ARRAY_BUFFER, textureByteSize, data.texCoords.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
    }

    // Indices
    glGenBuffers(1, &_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesByteSize, data.indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

/**
 * Return VAO
 */
GLuint MeshUi::getVAO() const {
    return _vao;
}

// Returns the number of indices
GLsizei MeshUi::getIndexCount() const {
    return _indices.size();
}

}  // namespace vecthar