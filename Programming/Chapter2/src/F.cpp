#include"../lib/CubicBezierSpline.hpp"
#include"../lib/Curve.hpp"
#include"../lib/Function.hpp"
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
    F_F_1 F1;
    F_F_2 F2;
    F_F_3 F3;
    vector<const Function*> init1({&F1,&F2}),init2({&F1,&F3});
    Curve upper(init1,-sqrt(3),sqrt(3));
    Curve lower(init2,-sqrt(3),sqrt(3));

    int foo[3]={10,40,160},bar[3]={5,20,80};
    CurvePointList init[4];//init[3] for temporary storage.
    for(int i=0;i<3;i++){
        CubicBezierSpline spline;
        init[i]=upper.generatePointList(bar[i],1,0);
        init[3]=lower.generatePointList(bar[i],1,1);
        init[i].insert(init[i].end(),init[3].begin(),init[3].end());
        init[i].push_back(init[i][0]);

        spline.setControlPointsList_List(init[i]);
        spline.generateSpline();

        string filename;
        filename="m="+to_string(foo[i])+".tex";
        spline.print_Latex(filename);
    }
    cout<< "Generated!"<<endl;
}