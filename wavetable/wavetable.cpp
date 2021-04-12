#include <cmath>
#include "wavetable.h"

Wavetable::Wavetable(float sampleRate, std::vector<float>& table, bool useInterpolation) {
    setup(sampleRate, table, useInterpolation);
}

void Wavetable::setup(float sampleRate, std::vector<float>& table, bool useInterpolation) {
    inverseSampleRate_ = 1.0 / sampleRate;
    table_ = table;
    useInterpolation_= useInterpolation;
    readPointer_ = 0;
}

void Wavetable::setFrequency(float f) {
    frequency_ = f;
}

float Wavetable::getFrequency() { 
    return frequency_;
}

float Wavetable::interpolate_() {
    int indexBelow = floorf(readPointer_);
    int indexAbove =  (indexBelow + 1) % table_.size();
    float fractionAbove = readPointer_ - indexBelow;
    float fractionBelow = 1.0 - fractionAbove;

    return fractionBelow * table_[indexBelow] + fractionAbove * table_[indexAbove];
}

float Wavetable::process() {
    if(table_.size() == 0){
        return 0;
    }

    readPointer_ += table_.size() * frequency_ * inverseSampleRate_;

    while(readPointer_ >= table_.size()){
        readPointer_ -= table_.size();
    }

    return useInterpolation_ ? interpolate_() : table_[(int)readPointer_];
}

