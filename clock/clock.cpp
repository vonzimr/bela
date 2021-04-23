//
// Created by robert on 4/18/21.
//

#include "clock.h"
#include<algorithm>

void Clock::setup(float sampleRate) {
    sampleRate_ = sampleRate;
}

void Clock::tick() {
    ticks_= (ticks_ + 1) % UINTMAX_MAX;
    executeFuncs_();
    cleanup_();

}

void Clock::executeFuncs_() {
    for (TimedFunc &funcSpec: funcs_) {
        if (funcSpec.ticksToNextCall <= 0) {
            funcSpec.func();
            if (!funcSpec.isInterval) {
                funcSpec.markDelete = true;
            }

            funcSpec.ticksToNextCall = funcSpec.tickDelta;
        }
        funcSpec.ticksToNextCall--;
    }
}

void Clock::cleanup_() {
    auto pend = remove_if(funcs_.begin(), funcs_.end(), [](const  TimedFunc &elem) {
        return elem.markDelete;
    });
    funcs_.erase(pend, funcs_.end());
}

float Clock::getTime() {
    if (ticks_ == 0) {
        return 0;
    }
    return (float) ticks_ / (float) sampleRate_;
}


void Clock::triggerOnInterval(std::function<void()> const &func, float interval) {
    TimedFunc timedFunc{
            timeInTicks(interval),
            timeInTicks(interval),
            func,
            true,
            false
    };
    funcs_.push_back(timedFunc);
}

void Clock::triggerOnTimeout(const std::function<void()> &func, float timeout) {
    TimedFunc timedFunc{
            timeInTicks(timeout),
            timeInTicks(timeout),
            func,
            false,
            false,
    };
    funcs_.push_back(timedFunc);
}
