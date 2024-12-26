#include"../lib/BFormSpline.hpp"
#include"../lib/PpFormSpline.hpp"
#include"../lib/PpFormSpline_3^2.hpp"
#include"../lib/Function.hpp"
#include<cmath>

using namespace std;

const double PI=3.1415926536;

int main(){
    class F_1:public Function{
        using Function::Function;
    private:
        double getValue(double x) const override{
            return cos(x);
        }
    };
    F_1 f1(DefinitionDomain{-2*PI,2*PI});

    BFormSpline BFS(9);
    BFS.generate(nullptr,f1.generatePointList(5));
    BFS.print_Latex("cos_BFS.tex","{cos(x*180/pi)}",f1);

    PpFormSpline PFS(7);
    PFS.generate(nullptr,f1.generatePointList(5));
    PFS.print_Latex("cos_PFS.tex","{cos(x*180/pi)}",f1);

    class F_2:public Function{
        using Function::Function;
    private:
        double getValue(double x) const override{
            return sqrt(x);
        }
    };
    F_2 f2(DefinitionDomain{1,10});

    PFS3 PFS3_N;
    PFS3_N.generate(nullptr,f2.generatePointList(4),BoundaryCondition_Natural());
    PFS3_N.print_Latex("sqrt,S_3^2, Natural.tex","{sqrt(x)}",f2);

    PFS3 PFS3_C;
    PFS3_C.generate(nullptr,f2.generatePointList(4),BoundaryCondition_Complete(f2.derivativeValue(1),f2.derivativeValue(10)));
    PFS3_C.print_Latex("sqrt,S_3^2, Complete.tex","{sqrt(x)}",f2);

    PFS3 PFS3_D2;
    PFS3_C.generate(nullptr,f2.generatePointList(4),BoundaryCondition_D2(-0.25,-0.25*pow(10,-1.5)));
    PFS3_C.print_Latex("sqrt,S_3^2, D2.tex","{sqrt(x)}",f2);

    PFS3 PFS3_NAK;
    PFS3_C.generate(nullptr,f2.generatePointList(4),BoundaryCondition_NotAKnot());
    PFS3_C.print_Latex("sqrt,S_3^2, Not-a-knot.tex","{sqrt(x)}",f2);

    BFormSpline draw(11);
    draw.draw_GivenCoef(vector<double>{0.1,0.36,0.02,0.42,0.33,0.17,0.38,0.35,0.233,0.1,0.43,0.34,0.51,0.19},vector<double>{0.2,0.6931,1.14514,3.14},"Draw B form splines.tex");

    BFormSpline draw_PU(11);
    draw_PU.draw_GivenCoef(vector<double>(14,1),vector<double>{0.2,0.6931,1.14514,3.14},"Draw B form splines, Partition of Unity.tex");

    cout<< ".tex files generated."<<endl;
}