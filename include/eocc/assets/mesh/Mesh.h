//
// Created by Egor Lentarev on 09.01.2026.
//

#ifndef EOCC_MESH_H
#define EOCC_MESH_H

#include <vector>
#include <eocc/assets/mesh/structures/MeshData.h>

#include <eocc/base/OpenGLTypes.h>

namespace eocc {

class Mesh {
public:
    explicit Mesh(const MeshData& data);
    ~Mesh();

    // Indices
    GLsizei getIndexCount() const;

    // Return VAO
    GLuint getVAO() const;

private:
    GLuint _vao = 0;
    GLuint _vbo = 0;
    GLuint _ebo = 0;
    GLuint _nbo = 0;
    GLuint _tbo = 0;

    std::vector<unsigned int> _indices;

    void uploadToGPU(const MeshData& data);
};

}  // namespace eocc

#endif  // EOCC_MESH_H