#include <cmath>
#include <vector>

enum Functions {
    Sine,
    Saw,
    Pulse,
    Triangle
};


class FunctionGenerators
{
public:
    FunctionGenerators(int size){
        size_ = (float) size;
    };
    std::vector<float> generate(Functions func);
    float sine(int n);
    float saw(int n);
    float pulse(int n);
    float tri(int n);

private:


private:
    float size_;
};

