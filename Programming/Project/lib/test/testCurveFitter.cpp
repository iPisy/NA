#include"../CurveFitter.hpp"
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
        return 2.0/3*(sqrt(fabs(x))+sqrt(3-x*x));
    }
};

class F_F_3:public Function{
    using Function::Function;
    double getValue(double x) const override{
        return 2.0/3*(sqrt(fabs(x))-sqrt(3-x*x));
    }
};
/// @endcond

int main(){
    F_F_1 C_u_F1,C_l_F1;
    F_F_2 C_u_F2;
    F_F_3 C_l_F2;
    Curve upper(vector<const Function*>{&C_u_F1,&C_u_F2},DefinitionDomain{-sqrt(3),sqrt(3)});
    Curve lower(vector<const Function*>{&C_l_F1,&C_l_F2},DefinitionDomain{-sqrt(3),sqrt(3)});

    int foo[3]={10,40,160},bar[3]={5,20,80};
    
    for(int i=0;i<3;i++){
        CurveFitter CF;

        CF.fit(knotMode::Uniform,Curve::connectValueList(vector<CurveValueList>{lower.generateValueList(bar[i],0,1,0),upper.generateValueList(bar[i]+1,0,0,1)}),BoundaryCondition_Periodic{},BoundaryCondition_Periodic{});
        
        CF.print_Latex("m="+to_string(foo[i])+".tex",vector<string>{"({x},{2/3*(sqrt(abs(x))+sqrt(3-x*x))})","({x},{2/3*(sqrt(abs(x))-sqrt(3-x*x))})"},vector<const Curve*>{&upper,&lower});
    }

    cout<< "Generated! Images will be in report after compilation."<<endl;
}