//
// Created by Egor Lentarev on 08.01.2026.
//

#ifndef EOCC_CUBE_MESH_H
#define EOCC_CUBE_MESH_H

#include <glad/glad.h>
#include <cstddef>

class CubePrimitive {
private:
    CubePrimitive() = delete;  //  Disable creation of instances.

    static const float vertices[72];
    static const unsigned int indices[36];
    static const float texCoords[48];
    static const float normals[108];

public:
    static const float* getVertexArray();
    static const unsigned int* getIndexArray();
    static const float* getTexCoordArray();
    static const float* getNormalArray();

    // Vertex
    static size_t getVertexFloatCount();
    static size_t getVertexByteSize();

    // Indices
    static GLsizei getIndexCount();
    static size_t getIndexByteSize();

    // Texture coordinates
    static size_t getTexCoordCount();
    static size_t getTexCoordByteSize();

    // Normals
    static size_t getNormalCount();
    static size_t getNormalByteSize();
};

#endif  // EOCC_CUBE_MESH_H