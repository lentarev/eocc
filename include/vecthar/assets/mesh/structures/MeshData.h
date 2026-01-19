//
// Created by Egor Lentarev on 05.01.2026.
//

#ifndef VECTHAR_MESH_DATA_H
#define VECTHAR_MESH_DATA_H

#include <vector>

namespace vecthar {

struct MeshData {
    std::vector<float> positions;       // x, y, z, ...
    std::vector<float> normals;         // x, y, z, ... (optional)
    std::vector<float> texCoords;       // u, v, ... (optional)
    std::vector<unsigned int> indices;  // triangles
};

}  // namespace vecthar

#endif  // VECTHAR_MESH_DATA_H