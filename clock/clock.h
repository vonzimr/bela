#pragma once
#include <functional>
#include <vector>

struct TimedFunc {
    float ticks;
    float timeStamp;
    std::function<void()> func;
    bool interval;
};

class Clock {
public:
    Clock() = default;
    void setup(float sampleRate);
    void tick();
    float getTime();
    float getTicks(){
        return ticks_;
    };
    float timeInTicks(float seconds);
    void reset(){
        ticks_ = 0;
    }
    bool pastInterval(float seconds){
        return ticks_ >= seconds * sampleRate_;
    }

    void tickOnInterval(std::function<void()> const& func, float interval);


private:
    float sampleRate_ = 0.;
    float ticks_ = 0;
    std::vector<TimedFunc> funcs_;


};