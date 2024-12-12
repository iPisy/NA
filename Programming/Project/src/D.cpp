#include"../lib/Function.hpp"
#include"../lib/BFormSpline_3^2.hpp"
#include"../lib/BFormSpline_Thm3.58.hpp"
#include"../lib/Function.hpp"
#include<iostream>

using namespace std;

class F:public Function{
    using Function::Function;
    double getValue(double x) const override{
        return 1/(1+x*x);
    }
};

int main(){
    F f(DefinitionDomain{-5,5});
    IndependentVariableList IVL3,IVL2;
    for(int i=1;i<=11;i++) IVL3.push_back(i-6);
    for(int i=1;i<=10;i++) IVL2.push_back(i-5.5);
    BoundaryCondition_Complete BCC(f.derivativeValue(-5),f.derivativeValue(5));
    BoundaryCondition_Theorem3_58 BCT(-5,f(-5),5,f(5));
    BFS3 Thm3_57;
    BFS_Thm3_58 Thm3_58;

    Thm3_57.generate(nullptr,f.generatePointList(IVL3),BCC);
    Thm3_58.generate(nullptr,f.generatePointList(IVL2),BCT,IVL3);

    double foo[7]={-3.5,-3,-0.5,0,0.5,3,3.5};
    Spline* bar[2]={&Thm3_57,&Thm3_58};
    const string splineName[2]={"Thm3_57","Thm3_58"};
    for(int i=0;i<2;i++){
        cout<<"Errors of spline of "<<splineName[i]<<":"<<endl;
        for(auto& it:foo){
            cout<<"x="<<it<<", error="<<fabs(bar[i]->operator()(it)-f(it))<<endl;
        }
        cout<<endl;
    }

}