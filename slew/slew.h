#pragma once
#include "clock.h"

class Slew {
public:
    Slew()= default;
    void setup(float sampleRate){
        sampleRate_ = sampleRate;
    };
    float process(float in, float velocity);
    float process(float in, float rise, float fall);
private:
    float ticksPerSecond(float v);
    float value_ = 0;
    float sampleRate_;
};