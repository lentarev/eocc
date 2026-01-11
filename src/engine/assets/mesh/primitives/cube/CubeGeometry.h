//
// Created by Egor Lentarev on 09.01.2026.
//

#ifndef EOCC_CUBE_GEOMETRY_H
#define EOCC_CUBE_GEOMETRY_H

#include <glad/glad.h>
#include <vector>

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

#endif  // EOCC_CUBE_GEOMETRY_H