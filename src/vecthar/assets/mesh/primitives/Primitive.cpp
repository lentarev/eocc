#include <vecthar/assets/mesh/primitives/Primitive.h>
#include <vecthar/assets/mesh/primitives/cube/CubeGeometry.h>

namespace vecthar {

Primitive::Primitive() = default;

MeshData Primitive::createCube() {
    MeshData data;

    data.positions = CubeGeometry::getVertices();
    data.indices = CubeGeometry::getIndices();
    data.texCoords = CubeGeometry::getTexCoords();
    data.normals = CubeGeometry::getNormals();

    return data;
}

}  // namespace vecthar