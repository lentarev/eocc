//
// Created by Egor Lentarev on 07.01.2026.
//

#ifndef VECTHAR_SCENE_BASE_H
#define VECTHAR_SCENE_BASE_H

#include <vecthar/scene/base/SceneBase.h>

namespace vecthar {

// forward declaration
class Engine;
class Renderer;

class SceneBase {
public:
    virtual ~SceneBase() = default;

    /// @brief Returns a pointer to the Engine
    /// @return
    Engine* getEngine() const { return _engine; }

    /// @brief Set the pointer to Engine
    /// @param engine
    void setEngine(Engine* engine) { _engine = engine; }

    /// @brief Logic
    /// @param deltaTime
    /// @param totalTime
    virtual void update(float deltaTime, float totalTime) = 0;

    /// @brief Render
    /// @param renderer
    virtual void draw(Renderer& renderer) = 0;

    /// @brief Input
    /// @param key
    /// @param scancode
    /// @param action
    /// @param mods
    virtual void onKey(int key, int scancode, int action, int mods) {}

protected:
    Engine* _engine = nullptr;
};

}  // namespace vecthar

#endif  // VECTHAR_SCENE_BASE_H