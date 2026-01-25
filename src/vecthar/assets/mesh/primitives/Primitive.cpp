#include <vecthar/assets/mesh/primitives/Primitive.h>
#include <vecthar/assets/mesh/primitives/cube/CubeGeometry.h>
#include <vecthar/assets/mesh/primitives/square/SquareGeometry.h>

namespace vecthar {

MeshData Primitive::createCube() {
    MeshData data;

    data.positions = CubeGeometry::getVertices();
    data.indices = CubeGeometry::getIndices();
    data.texCoords = CubeGeometry::getTexCoords();
    data.normals = CubeGeometry::getNormals();

    return data;
}

MeshUiData Primitive::createUiSquare() {
    MeshUiData data;

    data.positions = SquareGeometry::getVertices();
    data.indices = SquareGeometry::getIndices();
    data.texCoords = SquareGeometry::getTexCoords();

    return data;
}

}  // namespace vecthar