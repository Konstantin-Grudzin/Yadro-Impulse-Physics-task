#include <vector>

//Interpolator constructs in singletone paradigm
class Interpolator
{
private:
    static Interpolator* ptr;
    Interpolator(){};
public:
    static Interpolator& getInterpolator()
    {
        if(ptr==nullptr)
        {
            ptr = new Interpolator();
        }
        return *ptr;
    }

    //assuming that between two dots function is linear
    std::vector<long double> interpolation(int coeff,std::vector<long double>& meas)
    {
        std::vector<long double> result;
        int N = coeff - 1;
        for(int i=0;i<meas.size()-2;i+=2)
        {
            result.push_back(meas[i]);
            result.push_back(meas[i+1]);

            long double step = (meas[i+2] - meas[i])/(N+1);
            long double dx = (meas[i+2] - meas[i]);
            long double dy = (meas[i+3] - meas[i+1]);
            for(long double x=meas[i]+step;x<meas[i+2];x+=step)
            {
                result.push_back(x);
                result.push_back(dy/dx*(x-meas[i]) + meas[i+1]);
            }
        }
        result.push_back(meas[meas.size()-2]);
        result.push_back(meas[meas.size()-1]);
        return result;
    }
};