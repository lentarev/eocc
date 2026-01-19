//
// Created by Egor Lentarev on 09.01.2026.
//

#ifndef VECTHAR_PRIMITIVE_H
#define VECTHAR_PRIMITIVE_H

#include <vecthar/assets/mesh/structures/MeshData.h>

namespace vecthar {

class Primitive {
public:
    Primitive();

    static MeshData createCube();
};

}  // namespace vecthar

#endif  // VECTHAR_PRIMITIVE_H