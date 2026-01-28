//
// Created by Egor Lentarev on 09.01.2026.
//

#include <vecthar/assets/mesh/Mesh.h>
#include <cstddef>

#include <glad/glad.h>

namespace vecthar {

Mesh::Mesh(const MeshData& data) : _indices(data.indices), _vertexCount(data.positions.size() / 3), _hasIndices(!data.indices.empty()) {
    uploadToGPU(data);
}

/**
 * Destructor
 */
Mesh::~Mesh() {
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
    if (_nbo) {
        glDeleteBuffers(1, &_nbo);
        _nbo = 0;
    }
    if (_tbo) {
        glDeleteBuffers(1, &_tbo);
        _tbo = 0;
    }
}

void Mesh::uploadToGPU(const MeshData& data) {
    // Generate VAO
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    // Vertex (location = 0)
    if (!data.positions.empty()) {
        const size_t positionsByteSize = data.positions.size() * sizeof(data.positions[0]);

        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, positionsByteSize, data.positions.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    // Textute (location = 1)
    if (!data.texCoords.empty()) {
        const size_t textureByteSize = data.texCoords.size() * sizeof(data.texCoords[0]);

        glGenBuffers(1, &_tbo);
        glBindBuffer(GL_ARRAY_BUFFER, _tbo);
        glBufferData(GL_ARRAY_BUFFER, textureByteSize, data.texCoords.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
    }

    // Normals (location = 2)
    if (!data.normals.empty()) {
        const size_t normalsByteSize = data.normals.size() * sizeof(data.normals[0]);

        glGenBuffers(1, &_nbo);
        glBindBuffer(GL_ARRAY_BUFFER, _nbo);
        glBufferData(GL_ARRAY_BUFFER, normalsByteSize, data.normals.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(2);
    }

    // Index buffer (EBO)
    if (_hasIndices) {
        const GLsizei indicesByteSize = data.indices.size() * sizeof(data.indices[0]);

        glGenBuffers(1, &_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesByteSize, data.indices.data(), GL_STATIC_DRAW);
    }

    glBindVertexArray(0);
}

/**
 * Return VAO
 */
GLuint Mesh::getVAO() const {
    return _vao;
}

// Returns the number of indices
GLsizei Mesh::getIndexCount() const {
    return _indices.size();
}

bool Mesh::hasIndices() const {
    return _hasIndices;
}

// Returns the number of vertices
size_t Mesh::getVertexCount() const {
    return _vertexCount;
}

}  // namespace vecthar