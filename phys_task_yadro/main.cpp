#include<iostream>
#include<iomanip>
#include "generator.hpp"
#include "interpolation.hpp"
#include "decimation.hpp"

Interpolator* Interpolator::ptr=nullptr;
Decimator* Decimator::ptr=nullptr;
double SinGenerator::T=1;

int main()
{
    std::cout<<std::fixed<<std::setprecision(5);
    std::vector<long double> max_absolute_errors_by_f;
    for(long double f=1;f<=50;f+=1)
    {
        SinGenerator sg;
        std::vector<long double> res=sg.generate(f);
        auto& deci = Decimator::getDecimator();
        auto nres=deci.decimation(2,res);
        auto& inter = Interpolator::getInterpolator();
        nres=inter.interpolation(2,nres);
        long double max_absolute_error=0;
        for(size_t i=0;i<nres.size();i+=2)
        {
            long double value=abs(nres[i+1]-sin(2*pi*f*nres[i]));
            max_absolute_error=std::max(max_absolute_error,value);
        }
        max_absolute_errors_by_f.push_back(max_absolute_error);
#ifdef DETAILS
        std::cout<<"\n---------------------ORIGINAL SIGNAL---------------------------\n";
        for(size_t i=0;i<res.size();i+=2)
        {
            std::cout<<res[i]<<" "<<res[i+1]<<"\n";
        }
        std::cout<<"\n----------------SIGNAL AFTER DECIMATION----------------------\n";

        for(size_t i=0;i<nres.size();i+=2)
        {
            std::cout<<nres[i]<<" "<<nres[i+1]<<"\n";
        }
        std::cout<<"\n----------------SIGNAL AFTER INTERPOLATION----------------------\n";
        for(size_t i=0;i<nres.size();i+=2)
        {
            std::cout<<nres[i]<<" "<<nres[i+1];
        }
        std::cout<<"Max absolute Error: "<<max_absolute_error<<"\n";
#endif
    }
    std::cout<<"\nMax absolute errors by f:\n";
    for(int i=0;i<max_absolute_errors_by_f.size();++i)
    {
        std::cout<<"f="<<i+1<<" "<<max_absolute_errors_by_f[i]<<"\n";
    }
}