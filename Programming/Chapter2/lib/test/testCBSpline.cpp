#include"../CubicBezierSpline.hpp"
#include"../Curve.hpp"
#include"../Function.hpp"
#include<cmath>
#include<iostream>
#include<string>

using namespace std;

/// @cond
class F_F_1:public Function{
    using Function::Function;
    double getValue(double x) const override{
        return x;
    }
};

class F_F_2:public Function{
    using Function::Function;
    double getValue(double x) const override{
        return -sqrt(1-0.5*x*x);
    }
};

class F_F_3:public Function{
    using Function::Function;
    double getValue(double x) const override{
        return sqrt(1-0.5*x*x);
    }
};
/// @endcond

int main(){
    F_F_1 C_u_F1,C_l_F1;
    F_F_2 C_u_F2;
    F_F_3 C_l_F2;
    Curve upper(vector<const Function*>{&C_u_F1,&C_u_F2},DefinitionDomain{-sqrt(2),sqrt(2)});
    Curve lower(vector<const Function*>{&C_l_F1,&C_l_F2},DefinitionDomain{-sqrt(2),sqrt(2)});

    int foo[3]={10,40},bar[3]={5,20};
    
    for(int i=0;i<2;i++){
        CubicBezierSpline spline;

        spline.setControlPointsList_List(BezierSpline::connectInitList(
            vector<CurvePointList>{upper.generatePointList(bar[i],1,0),lower.generatePointList(bar[i],1,1)}));

        spline.generateSpline();
        
        spline.print_Latex("Circle-m="+to_string(foo[i])+".tex",vector<string>{"({x},{-sqrt(1-0.5*x*x)})","({x},{sqrt(1-0.5*x*x)})"},vector<const Curve*>{&upper,&lower});
    }
    cout<< "Generated!"<<endl;
}