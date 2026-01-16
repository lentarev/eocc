//
// Created by Egor Lentarev on 05.01.2026.
//

#ifndef EOCC_MESH_DATA_H
#define EOCC_MESH_DATA_H

#include <vector>

struct MeshData {
    std::vector<float> positions;       // x, y, z, ...
    std::vector<float> normals;         // x, y, z, ... (optional)
    std::vector<float> texCoords;       // u, v, ... (optional)
    std::vector<unsigned int> indices;  // triangles
};

#endif  // EOCC_MESH_DATA_H