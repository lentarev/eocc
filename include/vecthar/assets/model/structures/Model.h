//
// Created by Egor Lentarev on 28.01.2026.
//

#ifndef VECTHAR_MODEL_H
#define VECTHAR_MODEL_H

#include <vector>
#include <vecthar/assets/mesh/structures/MeshData.h>

namespace vecthar {

struct Model {
    std::vector<MeshData> meshes;
};

}  // namespace vecthar

#endif  // VECTHAR_MODEL_STRUCT_H