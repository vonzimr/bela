class FirstOrderLPF
{
public:
    FirstOrderLPF() {};
    float process(float input, float a) ;

private:
    float lastSample_ = 0;

};
