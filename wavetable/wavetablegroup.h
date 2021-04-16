#include "wavetable.h"

class WaveTableGroup
{
public:
    WaveTableGroup() {
     position_ = 0.;
    };
    void addWaveTable(Wavetable wavetable);
    void setPosition(float position);
    float process();
    void setFrequency(float frequency);
private:
    float interpolate_();
    std::vector<Wavetable> wavetables_;
    float position_;

};
