//
// Created by robert on 4/18/21.
//

#include "clock.h"

void Clock::setup(float sampleRate){
    sampleRate_ = sampleRate;
}

void Clock::tick(){
    ticks_++;

    for(TimedFunc& funcSpec: funcs_){
        if(ticks_ - funcSpec.timeStamp >= funcSpec.ticks){
            funcSpec.func();
            funcSpec.timeStamp = ticks_;
        }
    }
}

float Clock::timeInTicks(float seconds) {
    return sampleRate_/seconds;
}



float Clock::getTime(){
    if(ticks_ == 0){
        return 0;
    }
    return sampleRate_/ticks_;
}


void Clock::tickOnInterval(std::function<void()> const& func, float interval){
    TimedFunc timedFunc {
            timeInTicks(interval),
            getTicks(),
            func,
            true
    };
    funcs_.push_back(timedFunc);
}

