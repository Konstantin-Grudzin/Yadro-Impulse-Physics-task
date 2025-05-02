#include<vector>
#include <stdexcept>
#include<cmath>

long double pi=acosl(-1);

class SinGenerator
{
private:
    long double sampling_rate;
    static double T;
public:
    //constr
    SinGenerator(long double sampling_rate=100.0):sampling_rate(sampling_rate){}
    // getter and setter
    long double& get_sampling_rate() {return sampling_rate;}
    const long double& get_sampling_rate() const {return sampling_rate;}

    //generate signal
    //output format: {time,f(time),time1,f(time1),...}
    //if need speeding it up, change return value to void and get result vector by parametr by link
    std::vector<long double> generate(long double f=50.0)
    {
        std::vector<long double> result;
        if(f>50 || f<0)
            throw std::runtime_error("frequency is not supported (f=0...50)");
        for(long double t=0;t<=T;t+=(1.0/sampling_rate))
        {
            long double arg=pi*2.0;
            arg*=f*t;
            result.push_back(t);
            result.push_back(sin(arg));
        }
        return result;
    }
};