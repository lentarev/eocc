#include <eocc/assets/mesh/primitives/Primitive.h>
#include <eocc/assets/mesh/primitives/cube/CubeGeometry.h>

Primitive::Primitive() = default;

MeshData Primitive::createCube() {
    MeshData data;

    data.positions = CubeGeometry::getVertices();
    data.indices = CubeGeometry::getIndices();
    data.texCoords = CubeGeometry::getTexCoords();
    data.normals = CubeGeometry::getNormals();

    return data;
}