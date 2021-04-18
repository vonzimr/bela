#include "functiongenerators.h"
#include <vector>
#include <algorithm>


float FunctionGenerators::sine(int n)
{
     return sinf(2.0 * M_PI * (float)n / size_);
}

float FunctionGenerators::saw(int n)
{
     return ((float)n / size_ - 0.5) * 2;
}

float FunctionGenerators::tri(int n)
{
    float midpoint = size_ / 2;

    float value = saw(n);

    return 2 * (n < midpoint ? 0.5 + value: 0.5 - value);
}

float FunctionGenerators::pulse(int n)
{
    float midpoint = size_ / 2;

    return n < midpoint ? 1 : -1;
}

std::vector<float> FunctionGenerators::generate(Functions func) {
    std::vector<float> vec(size_);

    using GeneratorFunc = float (FunctionGenerators::*)(int);

    GeneratorFunc generatorFunc;

    switch(func){
         case Sine: generatorFunc = &FunctionGenerators::sine; break;
         case Saw: generatorFunc = &FunctionGenerators::saw; break;
         case Pulse: generatorFunc = &FunctionGenerators::pulse; break;
         case Triangle: generatorFunc = &FunctionGenerators::tri; break;
    }

    for(unsigned int i = 0; i<vec.size(); i++){
        vec[i] = (this->*generatorFunc)(i);
    }
    return vec;
}
