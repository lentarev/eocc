//
// Created by Egor Lentarev on 09.01.2026.
//

#include "Mesh.h"

Mesh::Mesh(const MeshData& data) {
    _vertices = data.positions;
    _indices = data.indices;
    _texCoords = data.texCoords;
    _normals = data.normals;
}

Mesh::~Mesh() {}

void Mesh::uploadToGPU() {
    // Generate VAO
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    // Vertex (location = 0)
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, getVertexByteSize(), &_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Textute (location = 1)
    glGenBuffers(1, &_tbo);
    glBindBuffer(GL_ARRAY_BUFFER, _tbo);
    glBufferData(GL_ARRAY_BUFFER, getTexCoordByteSize(), &_texCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    // Нормали (location = 2)
    glGenBuffers(1, &_nbo);
    glBindBuffer(GL_ARRAY_BUFFER, _nbo);
    glBufferData(GL_ARRAY_BUFFER, getNormalByteSize(), &_normals, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    // Indices
    glGenBuffers(1, &_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, getIndexByteSize(), &_indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

/**
 * Return VAO
 */
GLuint Mesh::getVAO() {
    return _vao;
}

// Vertex ======================================
//
// Returns the number of vertices
size_t Mesh::getVertexFloatCount() {
    return _vertices.size();
}

// Returns the size in bytes
size_t Mesh::getVertexByteSize() {
    if (_vertices.empty())
        return 0;

    return _vertices.size() * sizeof(_vertices[0]);
}

// Indices ======================================
//
// Returns the number of indices
GLsizei Mesh::getIndexCount() {
    return _indices.size();
}

// Returns the size in bytes
size_t Mesh::getIndexByteSize() {
    if (_indices.empty())
        return 0;

    return _indices.size() * sizeof(_indices[0]);
}

// Texture coordinates =============================
//
// Returns the number of texture coordinates
size_t Mesh::getTexCoordCount() {
    return _texCoords.size();
}

// Returns the size in bytes
size_t Mesh::getTexCoordByteSize() {
    if (_texCoords.empty())
        return 0;

    return _texCoords.size() * sizeof(_texCoords[0]);
}

// Normals =========================================
//
// Returns the number of normals
size_t Mesh::getNormalCount() {
    return _normals.size();
}

// Returns the size in bytes
size_t Mesh::getNormalByteSize() {
    if (_normals.empty())
        return 0;

    return _normals.size() * sizeof(_normals[0]);
}
