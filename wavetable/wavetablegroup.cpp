#include "wavetablegroup.h"
#include "wavetable.h"
#include <math.h>
#include <assert.h>
#include "interpolation.h"

void WaveTableGroup::addWaveTable(Wavetable wavetable)
{
     wavetables_.push_back(wavetable);
};

void WaveTableGroup::setPosition(float position){
    assert(position < wavetables_.size());
    position_ = position;
}

void WaveTableGroup::setFrequency(float frequency){
    for(auto table : wavetables_){
        table.setFrequency(frequency);
    }
}

float WaveTableGroup::process() {
    for(auto table : wavetables_){
        table.process();
    }

    float firstTable = wavetables_[(int)position_].getSample();
    float secondTable = wavetables_[(int)position_ + 1].getSample();


    float result =  Interpolation::linear(firstTable, secondTable, position_ - firstTable);
    return result;

}
