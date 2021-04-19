#include "firstorderlpf.h"

float FirstOrderLPF::process(float input, float a){
     float sample = a*lastSample_ + (1-a)*input;
     lastSample_ = sample;
     return sample;
}
