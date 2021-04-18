#include "wavetablegroup.h"
#include "wavetable.h"
#include <math.h>
#include <assert.h>
#include "interpolation.h"
#include "Utilities.h"


typedef std::vector<std::vector<float>> TableData;


void WaveTableGroup::setPosition(float position, float minPosition, float maxPosition){
    position_ = map(position, minPosition, maxPosition, 0, wavetables_.size()-1);
}

void WaveTableGroup::setFrequency(float frequency){
    for(auto& table : wavetables_){
        table.setFrequency(frequency);
    }
}

void WaveTableGroup::addWaveTable(Page& page) {
    Wavetable wavetable = Wavetable();
    wavetable.setup(sampleRate_, page);
    wavetables_.push_back(wavetable);
}

void WaveTableGroup::addWaveTables(PageGroup &pages) {
    for(auto &page: pages){
        addWaveTable(page);
    }
}


float WaveTableGroup::process() {
    for(auto& table : wavetables_){
        table.process();
    }

    int firstTableIndex = (int) position_;
    int secondTableIndex = (int) position_ + 1 % wavetables_.size();
    float firstTable = wavetables_[firstTableIndex].getSample();
    float secondTable = wavetables_[secondTableIndex].getSample();


    float result =  Interpolation::linear(firstTable, secondTable, position_ - firstTableIndex);
    return result;

}
