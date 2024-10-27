#include"../lib/Function.hpp"
#include"../lib/Interpolator.hpp"
#include"../lib/Polynomial.hpp"
#include<iostream>

using namespace std;

class F:public Function{
    double operator()(double x) const override{
        if(x==0) return 0;
        if(x==3) return 225;
        if(x==5) return 383;
        if(x==8) return 623;
        return 993;
    }

    double derivative(double x) const override{
        if(x==0) return 75;
        if(x==3) return 77;
        if(x==5) return 80;
        if(x==8) return 74;
        return 72;
    }
    
};

int main(){
    F f;
    Interpolator interpolator(f,{0,0,3,3,5,5,8,8,13,13});
    Polynomial poly=interpolator.interpolate();
    cout<<"Answer of (a):"<<endl;
    cout<<"position: "<<poly(10)<<endl<<"speed: "<<poly.derivative(10)<<endl;
}