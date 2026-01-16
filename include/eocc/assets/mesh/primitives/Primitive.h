//
// Created by Egor Lentarev on 09.01.2026.
//

#ifndef EOCC_PRIMITIVE_H
#define EOCC_PRIMITIVE_H

#include <eocc/assets/mesh/structures/MeshData.h>

class Primitive {
public:
    Primitive();

    static MeshData createCube();
};

#endif  // EOCC_PRIMITIVE_H