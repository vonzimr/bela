#pragma once

#include <vector>

class Wavetable {
    public:
        Wavetable() {}
        Wavetable(float sampleRate, std::vector<float>& table, bool useInterpolation = false);
        void setup(float sampleRate, std::vector<float>& table, bool useInterpolation = false);
        void setFrequency(float f);
        float getFrequency();
        float process();
        ~Wavetable() {}

    private:
        std::vector<float> table_;
        float inverseSampleRate_;
        float frequency_;
        float readPointer_;
        float useInterpolation_;
        float interpolate_();
};
