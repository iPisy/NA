#include"../lib/Interpolator_NewtonFormula.hpp"
#include"../lib/Function.hpp"
#include<iostream>

using namespace std;

int main(){
    FunctionPointList Sp1_interpolationPoints{{0,{6.67}},{6,{17.3}},{10,{42.7}},{13,{37.3}},{17,{30.1}},{20,{29.3}},{28,{28.7}}},
    Sp2_interpolationPoints{{0,{6.67}},{6,{16.1}},{10,{18.9}},{13,{15.0}},{17,{10.6}},{20,{9.44}},{28,{8.89}}};

    Interpolator_N Sp1_interpolator(Sp1_interpolationPoints);
    Interpolator_N Sp2_interpolator(Sp2_interpolationPoints);

    cout<<"Answer of (a):"<<endl;
    cout<<"Average weight polynomial for Sp1: "<<endl<<Sp1_interpolator.interpolate()<<endl;

    cout<<"Average weight polynomial for Sp2: "<<endl<<Sp2_interpolator.interpolate()<<endl;
    
    cout<<"Answer of (b):"<<endl;
    cout<<"Define that a certain sample of larvae will die at day x "
    <<"iff average_weight_polynomial(x) <= 0"<<endl;

    cout<<"However, the interpolation can only apply to the points within the section. "
    <<"If the point is out of the section, f^{n+1}_(x) may have no definition or can be arbitrarily huge. "
    <<"Thus the remainder can be arbitrarily huge, the interpolation is now meaningless."<<endl;

    cout<<endl
    <<"In the program, the interpolation polynomial has it's definition domain within 2 endpoints of the interpolation points. "
    <<"\033[31m"
    <<"Get the value out of the domain will cause throwing exceptions below."
    <<"\033[0m"
    <<endl;

    cout<<endl;
    cout<<"The average weight of Sp1 at day 43 is: "<<Sp1_interpolator.interpolate()(43)<<endl;
    cout<<"The average weight of Sp2 at day 43 is: "<<Sp2_interpolator.interpolate()(43)<<endl;
    cout<<endl;

}