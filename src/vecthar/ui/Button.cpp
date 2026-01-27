//
// Created by Egor Lentarev on 26.01.2026.
//

#include <vecthar/ui/Button.h>

#include <vecthar/renderer/Renderer.h>

namespace vecthar::ui {

/**
 * Constructor
 */
Button::Button() = default;

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

// Getters
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

std::string Button::getLabel() const {
    return _text;
}

// Setters
void Button::setX(const float x) {
    _x = x;
}

void Button::setY(const float y) {
    _y = y;
}

void Button::setWidth(const float width) {
    _width = width;
}

void Button::setHeight(const float height) {
    _height = height;
}

void Button::setLabel(const std::string& text) {
    _text = text;
}

}  // namespace vecthar::ui