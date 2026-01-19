//
// Created by Egor Lentarev on 09.01.2026.
//

#ifndef VECTHAR_CUBE_GEOMETRY_H
#define VECTHAR_CUBE_GEOMETRY_H

#include <vector>
#include <vecthar/base/OpenGLTypes.h>

/**
 * @brief Static cube geometry data (unit cube centered at origin).
 *
 * Provides vertices, indices, normals, and texture coordinates
 * for a 1x1x1 cube aligned with axes, centered at (0,0,0).
 */

namespace vecthar {

class CubeGeometry {
private:
    CubeGeometry() = delete;  //  Disable creation of instances.

    static std::vector<float> _vertices;
    static std::vector<unsigned int> _indices;
    static std::vector<float> _texCoords;
    static std::vector<float> _normals;

public:
    // Vertex
    static const std::vector<float>& getVertices();

    // Indices
    static const std::vector<unsigned int>& getIndices();

    // Texture coordinates
    static const std::vector<float>& getTexCoords();

    // Normals
    static const std::vector<float>& getNormals();
};

}  // namespace vecthar

#endif  // VECTHAR_CUBE_GEOMETRY_H