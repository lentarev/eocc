//
// Created by Egor Lentarev on 09.01.2026.
//

#ifndef VECTHAR_MESH_UI_H
#define VECTHAR_MESH_UI_H

#include <vector>
#include <vecthar/assets/mesh/structures/MeshUiData.h>

#include <vecthar/base/OpenGLTypes.h>

namespace vecthar {

class MeshUi {
public:
    explicit MeshUi(const MeshUiData& data);
    ~MeshUi();

    // Indices
    GLsizei getIndexCount() const;

    // Return VAO
    GLuint getVAO() const;

private:
    GLuint _vao = 0;
    GLuint _vbo = 0;
    GLuint _ebo = 0;
    GLuint _tbo = 0;

    std::vector<unsigned int> _indices;

    void uploadToGPU(const MeshUiData& data);
};

}  // namespace vecthar

#endif  // VECTHAR_MESH_UI_H