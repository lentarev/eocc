//
// Created by Egor Lentarev on 28.01.2026.
//

#ifndef VECTHAR_MODEL_H
#define VECTHAR_MODEL_H

#include <memory>
#include <vector>
#include <vecthar/assets/mesh/Mesh.h>

namespace vecthar {

struct Model {
    std::vector<std::unique_ptr<Mesh>> meshes;
};

}  // namespace vecthar

#endif  // VECTHAR_MODEL_STRUCT_H