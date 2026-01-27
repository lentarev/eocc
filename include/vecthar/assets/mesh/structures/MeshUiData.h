//
// Created by Egor Lentarev on 24.01.2026.
//

#ifndef VECTHAR_MESH_UI_DATA_H
#define VECTHAR_MESH_UI_DATA_H

#include <vector>

namespace vecthar {

struct MeshUiData {
    std::vector<float> positions;  // x, y, z, ...
    std::vector<float> texCoords;
    std::vector<unsigned int> indices;  // triangles
};

}  // namespace vecthar

#endif  // VECTHAR_MESH_UI_DATA_H