//
// Created by Egor Lentarev on 07.01.2026.
//

#ifndef EOCC_SCENE_BASE_H
#define EOCC_SCENE_BASE_H

class Renderer;

class SceneBase {
public:
    virtual ~SceneBase() = default;
    virtual void update(float deltaTime, float totalTime) = 0;
    virtual void draw(Renderer& renderer) = 0;
};

#endif  // EOCC_SCENE_BASE_H