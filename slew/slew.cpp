#include "slew.h"
#include "interpolation.h"
#include <math.h>

float Slew::process(float in, float velocity) {
    if(value_ - in > 0) value_ = fmax(in, value_ - ticksPerSecond(velocity));
    if(value_ - in < 0) value_ = fmin(value_ + ticksPerSecond(velocity), in);
    return value_;
}

float Slew::ticksPerSecond(float v) {
    return v / sampleRate_;
}

float Slew::process(float in, float rise, float fall) {
    if(value_ - in > 0) value_ = fmax(in, - ticksPerSecond(fall));
    if(value_ - in < 0) value_ = fmin(value_ + ticksPerSecond(rise), in);
    return value_;
}
