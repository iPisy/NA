#include"../lib/PpFormSpline_3^2.hpp"
#include"../lib/Function.hpp"
#include<algorithm>
#include<iostream>

using namespace std;

int main(){
    class F:public Function{
        using Function::Function;
        double getValue(double x) const override{
            return 1/(1+25*x*x);
        }
    };

    //init
    F f(DefinitionDomain{-1,1});
    IndependentVariableList IVL[5];
    int foo[5]={6,11,21,41,81};
    for(int i=0;i<5;i++) IVL[i]=f.get_definitionDomain().generateVariableList(foo[i]);
    BoundaryCondition_Complete BCC(f.derivativeValue(-1),f.derivativeValue(1));

    LatexOutputer o("A.tex");
    o.quickStart("Problem A");
    o.addLine("{1/(1+25*x*x)}","exact function","dashed",f.get_definitionDomain());
    for(int i=0;i<5;i++){
        PFS3 spline;
        spline.generate(nullptr,f.generatePointList(IVL[i]),BCC);
        string legendentry="N="+to_string(foo[i]);
        spline.print_Latex_Sole(o,0,legendentry);

        double maximum=0;
        for(int j=0;j<IVL[i].size()-1;j++){
            double x=(IVL[i][j]+IVL[i][j+1])/2;
            maximum=max(maximum,fabs(spline(x)-f(x)));
        }
        cout<<legendentry+", error="<<maximum<<endl;
    }
    o.quickEnd();

    cout<<endl<<".tex files generated."<<endl;
}