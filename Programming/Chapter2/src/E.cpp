#include"../lib/Interpolator_NewtonFormula.hpp"
#include"../lib/Function.hpp"
#include<iostream>

using namespace std;

/**
 * @brief The function of Question E, sample 1.
*/
class F_E_Sp1:public Function{
    double operator()(double x) const override{
        if(x==0) return 6.67;
        if(x==6) return 17.3;
        if(x==10) return 42.7;
        if(x==13) return 37.3;
        if(x==17) return 30.1;
        if(x==20) return 29.3;
        return 28.7;
    }
};

/**
 * @brief The function of Question E, sample 2.
*/
class F_E_Sp2:public Function{
    double operator()(double x) const override{
        if(x==0) return 6.67;
        if(x==6) return 16.1;
        if(x==10) return 18.9;
        if(x==13) return 15.0;
        if(x==17) return 10.6;
        if(x==20) return 9.44;
        return 8.89;
    }
};

int main(){
    vector<double> interpolatingPoints({0,6,10,13,17,20,28});
    F_E_Sp1 sp1;
    F_E_Sp2 sp2;
    Interpolator_N Sp1_interpolator(sp1,interpolatingPoints);
    Interpolator_N Sp2_interpolator(sp2,interpolatingPoints);

    cout<<"Answer of (a):"<<endl;
    cout<<"Average weight polynomial for Sp1: "<<endl;
    Sp1_interpolator.interpolate().print();
    cout<<"Average weight polynomial for Sp2: "<<endl;
    Sp2_interpolator.interpolate().print();
    cout<<endl;
    
    cout<<"Answer of (b):"<<endl;
    cout<<"Define that a certain sample of larvae will die at day x "
    <<"iff average_weight_polynomial(x) <= 0"<<endl;

    cout<<endl;
    cout<<"The average weight of Sp1 at day 43 is: "<<Sp1_interpolator.interpolate()(43)<<endl;
    cout<<"The average weight of Sp2 at day 43 is: "<<Sp2_interpolator.interpolate()(43)<<endl;
    cout<<endl;

    cout<<"However, the interpolation can only apply to the points within the section. "
    <<"If the point is out of the section, f^{n+1}_(x) may have no definition or can be arbitrarily huge. "
    <<"Thus the remainder can be arbitrarily huge, the interpolation is now meaningless."<<endl;
}