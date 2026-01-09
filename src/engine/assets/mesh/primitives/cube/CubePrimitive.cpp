#include "CubePrimitive.h"

const float CubePrimitive::vertices[72] = {
    // Задняя грань (Z = -0.5)
    -0.5f, -0.5f, -0.5f,  // 0
    -0.5f, 0.5f, -0.5f,   // 1
    0.5f, 0.5f, -0.5f,    // 2
    0.5f, -0.5f, -0.5f,   // 3

    // Передняя грань (Z = +0.5)
    -0.5f, -0.5f, 0.5f,  // 4
    0.5f, -0.5f, 0.5f,   // 5
    0.5f, 0.5f, 0.5f,    // 6
    -0.5f, 0.5f, 0.5f,   // 7

    // Левая грань (X = -0.5)
    -0.5f, -0.5f, 0.5f,   // 8
    -0.5f, 0.5f, 0.5f,    // 9
    -0.5f, 0.5f, -0.5f,   // 10
    -0.5f, -0.5f, -0.5f,  // 11

    // Правая грань (X = +0.5)
    0.5f, -0.5f, -0.5f,  // 12
    0.5f, 0.5f, -0.5f,   // 13
    0.5f, 0.5f, 0.5f,    // 14
    0.5f, -0.5f, 0.5f,   // 15

    // Нижняя грань (Y = -0.5)
    -0.5f, -0.5f, -0.5f,  // 16
    0.5f, -0.5f, -0.5f,   // 17
    0.5f, -0.5f, 0.5f,    // 18
    -0.5f, -0.5f, 0.5f,   // 19

    // Верхняя грань (Y = +0.5)
    -0.5f, 0.5f, -0.5f,  // 20
    -0.5f, 0.5f, 0.5f,   // 21
    0.5f, 0.5f, 0.5f,    // 22
    0.5f, 0.5f, -0.5f    // 23
};

const unsigned int CubePrimitive::indices[36] = {
    // Задняя
    0, 1, 2, 0, 2, 3,
    // Передняя
    4, 5, 6, 4, 6, 7,
    // Левая
    8, 9, 10, 8, 10, 11,
    // Правая
    12, 13, 14, 12, 14, 15,
    // Нижняя
    16, 17, 18, 16, 18, 19,
    // Верхняя
    20, 21, 22, 20, 22, 23

};

const float CubePrimitive::texCoords[48] = {
    // Задняя грань
    0.0f, 0.0f,  // 0
    0.0f, 1.0f,  // 1
    1.0f, 1.0f,  // 2
    1.0f, 0.0f,  // 3

    // Передняя грань
    0.0f, 0.0f,  // 4
    1.0f, 0.0f,  // 5
    1.0f, 1.0f,  // 6
    0.0f, 1.0f,  // 7

    // Левая грань
    0.0f, 0.0f,  // 8
    0.0f, 1.0f,  // 9
    1.0f, 1.0f,  // 10
    1.0f, 0.0f,  // 11

    // Правая грань
    0.0f, 0.0f,  // 12
    0.0f, 1.0f,  // 13
    1.0f, 1.0f,  // 14
    1.0f, 0.0f,  // 15

    // Нижняя грань
    0.0f, 0.0f,  // 16
    1.0f, 0.0f,  // 17
    1.0f, 1.0f,  // 18
    0.0f, 1.0f,  // 19

    // Верхняя грань
    0.0f, 0.0f,  // 20
    0.0f, 1.0f,  // 21
    1.0f, 1.0f,  // 22
    1.0f, 0.0f   // 23
};

const float CubePrimitive::normals[108] = {
    // Задняя грань (Z = -0.5) - вершины 0-3
    // Нормаль: (0, 0, -1)
    0.0f, 0.0f, -1.0f,  // 0
    0.0f, 0.0f, -1.0f,  // 1
    0.0f, 0.0f, -1.0f,  // 2
    0.0f, 0.0f, -1.0f,  // 3

    // Передняя грань (Z = +0.5) - вершины 4-7
    // Нормаль: (0, 0, 1)
    0.0f, 0.0f, 1.0f,  // 4
    0.0f, 0.0f, 1.0f,  // 5
    0.0f, 0.0f, 1.0f,  // 6
    0.0f, 0.0f, 1.0f,  // 7

    // Левая грань (X = -0.5) - вершины 8-11
    // Нормаль: (-1, 0, 0)
    -1.0f, 0.0f, 0.0f,  // 8
    -1.0f, 0.0f, 0.0f,  // 9
    -1.0f, 0.0f, 0.0f,  // 10
    -1.0f, 0.0f, 0.0f,  // 11

    // Правая грань (X = +0.5) - вершины 12-15
    // Нормаль: (1, 0, 0)
    1.0f, 0.0f, 0.0f,  // 12
    1.0f, 0.0f, 0.0f,  // 13
    1.0f, 0.0f, 0.0f,  // 14
    1.0f, 0.0f, 0.0f,  // 15

    // Нижняя грань (Y = -0.5) - вершины 16-19
    // Нормаль: (0, -1, 0)
    0.0f, -1.0f, 0.0f,  // 16
    0.0f, -1.0f, 0.0f,  // 17
    0.0f, -1.0f, 0.0f,  // 18
    0.0f, -1.0f, 0.0f,  // 19

    // Верхняя грань (Y = +0.5) - вершины 20-23
    // Нормаль: (0, 1, 0)
    0.0f, 1.0f, 0.0f,  // 20
    0.0f, 1.0f, 0.0f,  // 21
    0.0f, 1.0f, 0.0f,  // 22
    0.0f, 1.0f, 0.0f   // 23

};

// Возвращаем указатель на начало массива
const float* CubePrimitive::getVertexArray() {
    return vertices;
}

const unsigned int* CubePrimitive::getIndexArray() {
    return indices;
}

const float* CubePrimitive::getTexCoordArray() {
    return texCoords;
}

const float* CubePrimitive::getNormalArray() {
    return normals;
}

// Vertex -----------------------------------------
// Возвращает количество вершин
size_t CubePrimitive::getVertexFloatCount() {
    return sizeof(vertices) / sizeof(vertices[0]);
}

// Возвращает размер в байтах
size_t CubePrimitive::getVertexByteSize() {
    return sizeof(vertices);
}

// Indices -----------------------------------------
// Возвращает количество индексов
GLsizei CubePrimitive::getIndexCount() {
    return sizeof(indices) / sizeof(indices[0]);
}

// Возвращает размер в байтах
size_t CubePrimitive::getIndexByteSize() {
    return sizeof(indices);
}

// Texture coordinates ------------------------------
// Возвращает количество координат
size_t CubePrimitive::getTexCoordCount() {
    return sizeof(texCoords) / sizeof(texCoords[0]);
}
// Возвращает размер в байтах
size_t CubePrimitive::getTexCoordByteSize() {
    return sizeof(texCoords);
}

// Normals ------------------------------------------
size_t CubePrimitive::getNormalCount() {
    return sizeof(normals) / sizeof(normals[0]);
}

size_t CubePrimitive::getNormalByteSize() {
    return sizeof(normals);
}