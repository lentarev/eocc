//
// Created by Egor Lentarev on 09.01.2026.
//

#ifndef VECTHAR_PRIMITIVE_H
#define VECTHAR_PRIMITIVE_H

#include <vecthar/assets/mesh/structures/MeshData.h>
#include <vecthar/assets/mesh/structures/MeshUiData.h>

namespace vecthar {

class Primitive {
public:
    Primitive() = delete;  // Disable instantiation

    static MeshData createCube();

    /// @brief 2D UI Surface
    /// @return
    static MeshUiData createUiSquare();
};

}  // namespace vecthar

#endif  // VECTHAR_PRIMITIVE_H