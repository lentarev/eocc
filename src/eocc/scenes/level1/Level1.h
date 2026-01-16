//
// Created by Egor Lentarev on 06.01.2026.
//

#ifndef EOCC_LEVEL1_H
#define EOCC_LEVEL1_H

#include <eocc/scene/base/SceneBase.h>

class Level1 : public SceneBase {
public:
    Level1();
    ~Level1();

    void update(float deltaTime, float totalTime) override;
    void draw(Renderer& renderer) override;
};

#endif  // EOCC_LEVEL1_H