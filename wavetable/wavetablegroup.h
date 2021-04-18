#include "wavetable.h"


typedef std::vector<float> Page;
typedef std::vector<Page> PageGroup;

class WaveTableGroup
{
public:
    WaveTableGroup() {}
    void setup(int waveTableSize, float sampleRate) {
     position_ = 0.;
     sampleRate_ = sampleRate;
     waveTableSize_ = waveTableSize;
    };
    void addWaveTable(Page& page);
    void addWaveTables(PageGroup& pages);
    void setPosition(float position, float minPosition, float maxPosition);
    float process();
    void setFrequency(float frequency);
private:
    float interpolate_();
    std::vector<Wavetable> wavetables_;
    float position_;
    float sampleRate_;
    unsigned int waveTableSize_;

};
