//
// Created by robert on 4/18/21.
//

#include "clock.h"
#include<algorithm>

void Clock::setup(float sampleRate) {
    sampleRate_ = sampleRate;
}

void Clock::tick() {
    ticks_++;
    executeFuncs_();
    cleanup_();

}

void Clock::executeFuncs_() {
    for (TimedFunc &funcSpec: funcs_) {
        if (ticks_ - funcSpec.timeStamp >= funcSpec.ticks) {
            funcSpec.func();
            if (!funcSpec.isInterval) {
                funcSpec.markDelete = true;
            } else {
                funcSpec.timeStamp = ticks_;
            }
        }
    }
}

void Clock::cleanup_() {
    auto pend = remove_if(funcs_.begin(), funcs_.end(), [](const  TimedFunc &elem) {
        return elem.markDelete;
    });
    funcs_.erase(pend, funcs_.end());
}

float Clock::timeInTicks(float seconds) {
    return sampleRate_ / seconds;
}


float Clock::getTime() {
    if (ticks_ == 0) {
        return 0;
    }
    return sampleRate_ / ticks_;
}


void Clock::triggerOnInterval(std::function<void()> const &func, float interval) {
    TimedFunc timedFunc{
            timeInTicks(interval),
            getTicks(),
            func,
            true,
            false
    };
    funcs_.push_back(timedFunc);
}

void Clock::triggerOnTimeout(const std::function<void()> &func, float timeout) {
    TimedFunc timedFunc{
            timeInTicks(timeout),
            getTicks(),
            func,
            false,
            false,
    };
    funcs_.push_back(timedFunc);
}
