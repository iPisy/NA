#include"../lib/CubicBezierSpline.hpp"
#include"../lib/Curve.hpp"
#include"../lib/Function.hpp"
#include<cmath>
#include<iostream>

using namespace std;

class Function_F_1:public Function{
    double operator()(double x) const override{
        return x;
    }
};

class Function_F_2:public Function{
    double operator()(double x) const override{
        return 2.0/3*(sqrt(fabs(x))+sqrt(3-x*x));
    }
};

class Function_F_3:public Function{
    double operator()(double x) const override{
        return 2.0/3*(sqrt(fabs(x))-sqrt(3-x*x));
    }
};

int main(){
    Function_F_1 F1;
    Function_F_2 F2;
    Function_F_3 F3;
    vector<const Function*> init1,init2;
    init1.push_back(&F1);
    init1.push_back(&F2);
    init2.push_back(&F1);
    init2.push_back(&F3);
    Curve upper(init1,-sqrt(3),sqrt(3));
    Curve lower(init2,-sqrt(3),sqrt(3));
    vector<Curve*> init;
    init.push_back(&lower);
    init.push_back(&upper);
    CubicBizierSpline s1(init,10);
    s1.print_Latex("m=10.tex");
    CubicBizierSpline s2(init,40);
    s2.print_Latex("m=40.tex");
    CubicBizierSpline s3(init,160);
    s3.print_Latex("m=160.tex");
    cout<< "Generated!"<<endl;
}