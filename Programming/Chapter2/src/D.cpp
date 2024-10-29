#include"../lib/Function.hpp"
#include"../lib/Interpolator_HermiteProblem_NewtonFormula.hpp"
#include"../lib/Polynomial.hpp"
#include<iostream>

using namespace std;

/**
 * @brief The function of Question D.
*/
class F_D:public Function{
    double operator()(double x) const override{{
            
        }
        if(x==0) return 0;
        if(x==3) return 225;
        if(x==5) return 383;
        if(x==8) return 623;
        return 993;
    }

    double derivative(double x,int order) const override{
        if(order==1){
            if(x==0) return 75;
            if(x==3) return 77;
            if(x==5) return 80;
            if(x==8) return 74;
            return 72;
        }
        else return throwException();
    }
    
};

int main(){
    F_D f;
    Interpolator_Hermite_N interpolator(f,{0,0,3,3,5,5,8,8,13,13});
    Polynomial p_n_x=interpolator.interpolate();
    cout<<"Answer of (a):"<<endl;
    cout<<"position: "<<p_n_x(10)<<endl<<"speed: "<<p_n_x.derivative(10,1)<<endl;
    cout<<endl;

    cout<<"Answer of (b):"<<endl;
    double maxSpeed=p_n_x.getDerivativePoly().getLocalMax(interpolator.getInterpolatingPoints());
    cout<<"The max car speed is: "<<maxSpeed<<endl;
    if(maxSpeed>81) cout<<"Thus the car had ever exceeded the speed limit."<<endl;
    else cout<<"Thus the car didn't exceed the speed limit."<<endl;
}