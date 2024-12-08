#include"../lib/Function.hpp"
#include"../lib/Interpolator_HermiteProblem_NewtonFormula.hpp"
#include"../lib/Polynomial.hpp"
#include<iostream>

using namespace std;

int main(){
    Interpolator_Hermite_N interpolator({{0,{0,75}},{0,{}},{3,{225,77}},{3,{}},{5,{383,80}},{5,{}},{8,{623,74}},{8,{}},{13,{993,72}},{13,{}}});
    Polynomial p_n_x=interpolator.interpolate();
    cout<<"Answer of (a):"<<endl;
    cout<<"position: "<<p_n_x(10)<<endl<<"speed: "<<p_n_x.derivativeValue(10)<<endl;
    cout<<endl;

    cout<<"Answer of (b):"<<endl;
    double maxSpeed=p_n_x.getDerivative(1).getLocalMax();
    cout<<"The max car speed is: "<<maxSpeed<<endl;
    if(maxSpeed>81) cout<<"Thus the car had ever exceeded the speed limit."<<endl;
    else cout<<"Thus the car didn't exceed the speed limit."<<endl;
}