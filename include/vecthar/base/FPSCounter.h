//
// Created by Egor Lentarev on 25.01.2026.
//

#ifndef VECTHAR_FPS_COUNTER_H
#define VECTHAR_FPS_COUNTER_H

namespace vecthar {

class FPSCounter {
public:
    FPSCounter();
    ~FPSCounter();

    void update();

    int getFPS() const;

    float getFrameTimeMs() const;

private:
    double _lastTime = 0.0;
    double _frameTime = 0.0;
    double _elapsedTime = 0.0;
    int _frameCount = 0;
    int _fps = 0;
};

}  // namespace vecthar

#endif  // VECTHAR_FPS_COUNTER_H