//
// Created by Egor Lentarev on 09.01.2026.
//

#include <vecthar/assets/mesh/primitives/cube/CubeGeometry.h>

#include <glad/glad.h>

namespace vecthar {

std::vector<float> CubeGeometry::_vertices = {
    // Back face (Z = -0.5)
    -0.5f, -0.5f, -0.5f,  // 0
    -0.5f, 0.5f, -0.5f,   // 1
    0.5f, 0.5f, -0.5f,    // 2
    0.5f, -0.5f, -0.5f,   // 3

    // Front face (Z = +0.5)
    -0.5f, -0.5f, 0.5f,  // 4
    0.5f, -0.5f, 0.5f,   // 5
    0.5f, 0.5f, 0.5f,    // 6
    -0.5f, 0.5f, 0.5f,   // 7

    // Left side (X = -0.5)
    -0.5f, -0.5f, 0.5f,   // 8
    -0.5f, 0.5f, 0.5f,    // 9
    -0.5f, 0.5f, -0.5f,   // 10
    -0.5f, -0.5f, -0.5f,  // 11

    // Right side (X = +0.5)
    0.5f, -0.5f, -0.5f,  // 12
    0.5f, 0.5f, -0.5f,   // 13
    0.5f, 0.5f, 0.5f,    // 14
    0.5f, -0.5f, 0.5f,   // 15

    // Bottom face (Y = -0.5)
    -0.5f, -0.5f, -0.5f,  // 16
    0.5f, -0.5f, -0.5f,   // 17
    0.5f, -0.5f, 0.5f,    // 18
    -0.5f, -0.5f, 0.5f,   // 19

    // Top face (Y = +0.5)
    -0.5f, 0.5f, -0.5f,  // 20
    -0.5f, 0.5f, 0.5f,   // 21
    0.5f, 0.5f, 0.5f,    // 22
    0.5f, 0.5f, -0.5f    // 23
};

std::vector<unsigned int> CubeGeometry::_indices = {
    // Back
    0, 1, 2, 0, 2, 3,
    // Front
    4, 5, 6, 4, 6, 7,
    // Left
    8, 9, 10, 8, 10, 11,
    // Right
    12, 13, 14, 12, 14, 15,
    // Lower
    16, 17, 18, 16, 18, 19,
    // Upper
    20, 21, 22, 20, 22, 23
    //
};

std::vector<float> CubeGeometry::_texCoords = {
    // Back face
    0.0f, 0.0f,  // 0
    0.0f, 1.0f,  // 1
    1.0f, 1.0f,  // 2
    1.0f, 0.0f,  // 3

    // Front face
    0.0f, 0.0f,  // 4
    1.0f, 0.0f,  // 5
    1.0f, 1.0f,  // 6
    0.0f, 1.0f,  // 7

    // Left side
    0.0f, 0.0f,  // 8
    0.0f, 1.0f,  // 9
    1.0f, 1.0f,  // 10
    1.0f, 0.0f,  // 11

    // Right side
    0.0f, 0.0f,  // 12
    0.0f, 1.0f,  // 13
    1.0f, 1.0f,  // 14
    1.0f, 0.0f,  // 15

    // Bottom face
    0.0f, 0.0f,  // 16
    1.0f, 0.0f,  // 17
    1.0f, 1.0f,  // 18
    0.0f, 1.0f,  // 19

    // Upper face
    0.0f, 0.0f,  // 20
    0.0f, 1.0f,  // 21
    1.0f, 1.0f,  // 22
    1.0f, 0.0f   // 23
};

std::vector<float> CubeGeometry::_normals = {
    // Back face (Z = -0.5) - vertices 0-3
    // Normal: (0, 0, -1)
    0.0f, 0.0f, -1.0f,  // 0
    0.0f, 0.0f, -1.0f,  // 1
    0.0f, 0.0f, -1.0f,  // 2
    0.0f, 0.0f, -1.0f,  // 3

    // Front face (Z = +0.5) - vertices 4-7
    // Normal: (0, 0, 1)
    0.0f, 0.0f, 1.0f,  // 4
    0.0f, 0.0f, 1.0f,  // 5
    0.0f, 0.0f, 1.0f,  // 6
    0.0f, 0.0f, 1.0f,  // 7

    // Left side (X = -0.5) - vertices 8-11
    // Normal: (-1, 0, 0)
    -1.0f, 0.0f, 0.0f,  // 8
    -1.0f, 0.0f, 0.0f,  // 9
    -1.0f, 0.0f, 0.0f,  // 10
    -1.0f, 0.0f, 0.0f,  // 11

    // Right side (X = +0.5) - vertices 12-15
    // Normal: (1, 0, 0)
    1.0f, 0.0f, 0.0f,  // 12
    1.0f, 0.0f, 0.0f,  // 13
    1.0f, 0.0f, 0.0f,  // 14
    1.0f, 0.0f, 0.0f,  // 15

    // Bottom face (Y = -0.5) - vertices 16-19
    // Normal: (0, -1, 0)
    0.0f, -1.0f, 0.0f,  // 16
    0.0f, -1.0f, 0.0f,  // 17
    0.0f, -1.0f, 0.0f,  // 18
    0.0f, -1.0f, 0.0f,  // 19

    // Top face (Y = +0.5) - vertices 20-23
    // Normal: (0, 1, 0)
    0.0f, 1.0f, 0.0f,  // 20
    0.0f, 1.0f, 0.0f,  // 21
    0.0f, 1.0f, 0.0f,  // 22
    0.0f, 1.0f, 0.0f   // 23
};

// Vertex ======================================
const std::vector<float>& CubeGeometry::getVertices() {
    return _vertices;
}

// Indices ======================================
const std::vector<unsigned int>& CubeGeometry::getIndices() {
    return _indices;
}

// Texture coordinates =============================
const std::vector<float>& CubeGeometry::getTexCoords() {
    return _texCoords;
}

// Normals =========================================
const std::vector<float>& CubeGeometry::getNormals() {
    return _normals;
}

}  // namespace vecthar