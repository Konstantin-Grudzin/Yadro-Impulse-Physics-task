#include <vector>
#include <stdexcept>

//Decimator constructs in singletone paradigm
class Decimator
{
private:
    static Decimator* ptr;
    Decimator(){};
public:
    static Decimator& getDecimator()
    {
        if(ptr==nullptr)
        {
            ptr = new Decimator();
        }
        return *ptr;
    }

    //assuming that between two dots function is linear
    std::vector<long double> decimation(int coeff,std::vector<long double>& meas)
    {
        if(coeff<1)
            throw std::runtime_error("wrong coefficient for decimation(>1)");
        std::vector<long double> result;
        for(int i=0;i<meas.size();i+=2)
        {
            if((i/2)%coeff == 0){
                result.push_back(meas[i]);
                result.push_back(meas[i+1]);
            }
        }
        return result;
    }
};