#pragma once
#include <functional>
#include <vector>

struct TimedFunc {
    float ticksToNextCall;
    float tickDelta;
    std::function<void()> func;
    bool isInterval;
    bool markDelete;
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
    float timeInTicks(float seconds){
        return seconds * sampleRate_;
    };
    void reset(){
        ticks_ = 0;
    }

    void triggerOnInterval(std::function<void()> const& func, float interval);
    void triggerOnTimeout(std::function<void()> const& func, float timeout);


private:
    void executeFuncs_();
    void cleanup_();
    float sampleRate_ = 0.;
    uint ticks_ = 0;
    std::vector<TimedFunc> funcs_;


};