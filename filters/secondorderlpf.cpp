#include "secondorderlpf.h"
#include <cstdio>

float SecondOrderLPF::process(float in, float q, float frequency) {
    float x2 = pop_(x_);
    float x1 = x_.back();
    x_.insert(x_.begin(), in);

    float y2 = pop_(y_);
    float y1 = y_.back();

    auto [A1, A2, B0, B1, B2] = calculateCoefficients_(frequency, q);

    float y0 = B0 * in + B1 * x1 + B2 * x2 -
               A1 * y1 - A2 * y2;

    y_.insert(y_.begin(), y0);

    return y0;


}
