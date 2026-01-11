//
// Created by Egor Lentarev on 09.01.2026.
//

#ifndef EOCC_MESH_H
#define EOCC_MESH_H

#include <glad/glad.h>
#include <vector>
#include <engine/assets/mesh/structures/MeshData.h>

class Mesh {
public:
    explicit Mesh(const MeshData& data);
    ~Mesh();

    // Vertex
    size_t getVertexFloatCount();
    size_t getVertexByteSize();

    // Indices
    GLsizei getIndexCount();
    size_t getIndexByteSize();

    // Texture coordinates
    size_t getTexCoordCount();
    size_t getTexCoordByteSize();

    // Normals
    size_t getNormalCount();
    size_t getNormalByteSize();

    GLuint getVAO();

private:
    GLuint _vao = 0;
    GLuint _vbo = 0;
    GLuint _ebo = 0;
    GLuint _nbo = 0;
    GLuint _tbo = 0;

    std::vector<float> _vertices;
    std::vector<unsigned int> _indices;
    std::vector<float> _texCoords;
    std::vector<float> _normals;

    void uploadToGPU();
};

#endif  // EOCC_MESH_H