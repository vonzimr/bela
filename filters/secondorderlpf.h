#include <vector>
#include <cmath>
#include <assert.h>


struct Coeffs {
    float A1;
    float A2;
    float B0;
    float B1;
    float B2;
};

class SecondOrderLPF {

public:
    SecondOrderLPF() {
        x_.resize(2);
        y_.resize(2);
    };

    void setup(float sampleRate){
        sampleRate_ = sampleRate;
    }

    float process(float in, float q, float frequency);


private:
    float pop_(std::vector<float>& vec) {
        float v = vec.back();
        vec.pop_back();
        return v;
    }

    Coeffs calculateCoefficients_(float frequency, float q) {
        assert(q > 0);
        float k = tanf(M_PI * frequency / sampleRate_);
        float norm = 1.0 / (1 + k / q + k * k);

        float B0 = k * k * norm;
        float B1 = 2.0 * B0;
        float B2 = B0;
        float A1 = 2 * (k * k - 1) * norm;
        float A2 = (1 - k / q + k * k) * norm;

        auto coeffs = Coeffs {
                A1, A2, B0, B1, B2
        };

        return coeffs;

    }

    std::vector<float> y_;
    std::vector<float> x_;
    float sampleRate_;
};
