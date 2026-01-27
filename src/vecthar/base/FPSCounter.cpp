#include <vecthar/base/FPSCounter.h>

#include <GLFW/glfw3.h>

namespace vecthar {

FPSCounter::FPSCounter() = default;

FPSCounter::~FPSCounter() = default;

void FPSCounter::update() {
    const double currentTime = glfwGetTime();
    _frameTime = currentTime - _lastTime;
    _lastTime = currentTime;

    _frameCount++;
    _elapsedTime += _frameTime;

    if (_elapsedTime >= 1.0) {
        _fps = static_cast<int>(_frameCount / _elapsedTime + 0.5f);
        _frameCount = 0;
        _elapsedTime = 0.0;
    }
}

int FPSCounter::getFPS() const {
    return _fps;
}

float FPSCounter::getFrameTimeMs() const {
    return static_cast<float>(_frameTime * 1000.0);
}

}  // namespace vecthar