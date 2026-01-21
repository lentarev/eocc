#include "Level1.h"

#include <vecthar/Engine.h>
#include <vecthar/assets/mesh/structures/MeshData.h>
#include <vecthar/assets/mesh/primitives/Primitive.h>
#include <vecthar/assets/mesh/Mesh.h>
#include <vecthar/renderer/Renderer.h>
#include <vecthar/assets/shader/Shader.h>
#include <vecthar/input/Key.h>

#include "scenes/menu/Menu.h"

// Constructor
Level1::Level1() {
    _shader = std::make_unique<vecthar::Shader>();
    _shader->createProgram(_shader->read("./shaders/basic.vert"), _shader->read("./shaders/basic.frag"));

    vecthar::MeshData cubeData = vecthar::Primitive::createCube();

    _cubeMesh = std::make_unique<vecthar::Mesh>(cubeData);
    _cubeMaterial.baseColor = {1.0f, 1.0f, 0.0f};
}

// Destructor
Level1::~Level1() {}

/**
 * Input
 */
void Level1::onKey(int key, int scancode, int action, int mods) {
    if (key == vecthar::KEY_SPACE && action == 1) {
        // Transition to another scene
        this->getEngine()->setCurrentScene(std::make_unique<Menu>());
    }
}

/**
 * Update - logic update
 */
void Level1::update(float deltaTime, float totalTime) {
    _transform.rotation.y = glm::radians(45.0f) * totalTime;
}

void Level1::draw(vecthar::Renderer& renderer) {
    renderer.useShaderProgram(_shader->getProgram());

    // Drawing a cube using a renderer
    renderer.drawMesh(*_cubeMesh, _cubeMaterial, _transform.getModelMatrix());
}