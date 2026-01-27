//
// Created by Egor Lentarev on 26.01.2026.
//

#ifndef VECTHAR_BUTTON_H
#define VECTHAR_BUTTON_H

#include <string>

namespace vecthar {
class Renderer;
}

namespace vecthar::ui {

class Button {
public:
    Button(float x, float y, float width, float height, const std::string& text);
    ~Button();

    bool contains(float mouseX, float mouseY) const;

    void render(Renderer& renderer, float scale = 3.0f) const;

    // Getters for debugging (optional)
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;

    // Setters
    void setX(const float x);
    void setY(const float y);

private:
    float _x, _y, _width, _height;
    std::string _text;
};

}  // namespace vecthar::ui

#endif  // VECTHAR_BUTTON_H