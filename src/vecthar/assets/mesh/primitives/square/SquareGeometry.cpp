#include <vecthar/assets/mesh/primitives/square/SquareGeometry.h>

namespace vecthar {

std::vector<float> SquareGeometry::_vertices = {
    -0.5f, -0.5f, 0.0f,  // 0: bottom left
    0.5f,  -0.5f, 0.0f,  // 1: bottom right
    0.5f,  0.5f,  0.0f,  // 2: top right
    -0.5f, 0.5f,  0.0f   // 3: top left
};

std::vector<unsigned int> SquareGeometry::_indices = {
    0, 1, 3,  // first triangle: BL, BR, TL
    1, 2, 3   // second triangle: BR, TR, TL
};

std::vector<float> SquareGeometry::_texCoords = {
    0.0f, 1.0f,  // BL → (0,1) — if the atlas uses OpenGL orientation
    1.0f, 1.0f,  // BR → (1,1)
    1.0f, 0.0f,  // TR → (1,0)
    0.0f, 0.0f   // TL → (0,0)
};

// Vertex ======================================
const std::vector<float>& SquareGeometry::getVertices() {
    return _vertices;
}

// Indices ======================================
const std::vector<unsigned int>& SquareGeometry::getIndices() {
    return _indices;
}

// Texture coordinates =============================
const std::vector<float>& SquareGeometry::getTexCoords() {
    return _texCoords;
}

}  // namespace vecthar