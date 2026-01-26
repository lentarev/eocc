//
// Created by Egor Lentarev on 26.01.2026.
//

#include <vecthar/ui/Button.h>

#include <vecthar/renderer/Renderer.h>

namespace vecthar::ui {

/**
 * Constructor
 */
Button::Button(float x, float y, float width, float height, const std::string& text) : _x(x), _y(y), _width(width), _height(height), _text(text) {};

/**
 * Destructor
 */
Button::~Button() = default;

bool Button::contains(float mouseX, float mouseY) const {
    return mouseX >= _x && mouseX <= _x + _width && mouseY >= _y && mouseY <= _y + _height;
}

void Button::render(Renderer& renderer, float scale) const {
    renderer.drawText(_text, _x, _y, scale);
}

float Button::getX() const {
    return _x;
}

float Button::getY() const {
    return _y;
}

float Button::getWidth() const {
    return _width;
}

float Button::getHeight() const {
    return _height;
}

}  // namespace vecthar::ui