//
// Created by Egor Lentarev on 24.01.2026.
//

#ifndef VECTHAR_SQUARE_GEOMETRY_H
#define VECTHAR_SQUARE_GEOMETRY_H

#include <vector>

namespace vecthar {

class SquareGeometry {
private:
    SquareGeometry() = delete;  //  Disable creation of instances.

    static std::vector<float> _vertices;
    static std::vector<unsigned int> _indices;
    static std::vector<float> _texCoords;

public:
    // Vertex
    static const std::vector<float>& getVertices();

    // Indices
    static const std::vector<unsigned int>& getIndices();

    // Texture coordinates
    static const std::vector<float>& getTexCoords();
};

}  // namespace vecthar

#endif  // VECTHAR_SQUARE_GEOMETRY_H