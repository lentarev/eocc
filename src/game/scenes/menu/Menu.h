//
// Created by Egor Lentarev on 06.01.2026.
//

#ifndef EOCC_MENU_H
#define EOCC_MENU_H

#include <engine/scene/base/SceneBase.h>

class Menu : public SceneBase {
public:
    Menu();
    ~Menu();

    void update() override;
    void draw(Renderer& renderer) override;
};

#endif  // EOCC_MENU_H