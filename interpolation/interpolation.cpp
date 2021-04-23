#include "interpolation.h"



float Interpolation::linear(float v0, float v1, float t){
    return (1 - (float)t ) * (float)v0 + (float)t * (float)v1;
}
