//
// Created by Egor Lentarev on 09.01.2026.
//

#ifndef VECTHAR_MESH_H
#define VECTHAR_MESH_H

#include <vector>
#include <vecthar/assets/mesh/structures/MeshData.h>

#include <vecthar/base/OpenGLTypes.h>

namespace vecthar {

class Mesh {
public:
    explicit Mesh(const MeshData& data);
    ~Mesh();

    // Indices
    GLsizei getIndexCount() const;

    bool hasIndices() const;

    size_t getVertexCount() const;

    // Return VAO
    GLuint getVAO() const;

private:
    GLuint _vao = 0;
    GLuint _vbo = 0;
    GLuint _ebo = 0;
    GLuint _nbo = 0;
    GLuint _tbo = 0;

    std::vector<unsigned int> _indices;

    size_t _vertexCount = 0;

    bool _hasIndices = false;

    void uploadToGPU(const MeshData& data);
};

}  // namespace vecthar

#endif  // VECTHAR_MESH_H