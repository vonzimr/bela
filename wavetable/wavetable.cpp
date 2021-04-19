#include <cmath>
#include "wavetable.h"
#include "interpolation.h"

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

   return Interpolation::linear(
               table_[indexBelow],
               table_[indexAbove],
               readPointer_);

}

float Wavetable::getSample(){
    return sample_;
}

float Wavetable::process() {
    if(table_.size() == 0){
        return 0;
    }

    readPointer_ += table_.size() * frequency_ * inverseSampleRate_;

    while(readPointer_ >= table_.size()){
        readPointer_ -= table_.size();
    }

    sample_  = useInterpolation_ ? interpolate_() : table_[(int)readPointer_];

    return sample_;
}

