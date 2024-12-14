#include"../lib/CurveFitter.hpp"
#include"../lib/Curve.hpp"
#include"../lib/SphereCurveFitter.hpp"
#include<cmath>

using namespace std;

int main(){
    const double PI=3.1415926536;

    //E, Problem 1
    class E_1_F_1:public Function{
        double getValue(double x) const override{
            return x;
        }
    };

    class E_1_F_2:public Function{
        double getValue(double x) const override{
            return 2.0/3*(sqrt(fabs(x))+sqrt(3-x*x));
        }
    };

    class E_1_F_3:public Function{
        double getValue(double x) const override{
            return 2.0/3*(sqrt(fabs(x))-sqrt(3-x*x));
        }
    };

    E_1_F_1 C_u_F1,C_l_F1;
    E_1_F_2 C_u_F2;
    E_1_F_3 C_l_F2;
    Curve E_1_upper(vector<const Function*>{&C_u_F1,&C_u_F2},DefinitionDomain{-sqrt(3),sqrt(3)});
    Curve E_1_lower(vector<const Function*>{&C_l_F1,&C_l_F2},DefinitionDomain{-sqrt(3),sqrt(3)});

    int foo[3]={10,40,160},bar[3]={5,20,80};
    
    for(int i=0;i<3;i++){
        CurveFitter CFU,CFC;

        LatexOutputer o("E1, m="+to_string(foo[i])+".tex");
        o.quickStart("Problem E, 1, m="+to_string(foo[i]));
        o.addLine("({x},{2/3*(sqrt(abs(x))+sqrt(3-x*x))})",E_1_upper.getDefinitionDomain(),"exact curve","dashed");
        o.addLine("({x},{2/3*(sqrt(abs(x))-sqrt(3-x*x))})",E_1_lower.getDefinitionDomain(),"","dashed");

        CFU.fit(knotMode::Uniform,Curve::connectValueList(vector<CurveValueList>{E_1_lower.generateValueList(bar[i],0,1,0),E_1_upper.generateValueList(bar[i],0,0,1)}),BoundaryCondition_Periodic{},BoundaryCondition_Periodic{});
        CFU.print_Latex_Sole(o,"uniform knots");

        CFC.fit(knotMode::CumulativeChordal,Curve::connectValueList(vector<CurveValueList>{E_1_lower.generateValueList(bar[i],0,1,0),E_1_upper.generateValueList(bar[i],0,0,1)}),BoundaryCondition_Periodic{},BoundaryCondition_Periodic{});
        CFC.print_Latex_Sole(o,"cumulative chordal knots");

        o.quickEnd();
    }


    //E, Problem 2
    class E_2_F_1:public Function{
        double getValue(double x) const override{
            return sin(x)+x*cos(x);
        }
    };

    class E_2_F_2:public Function{
        double getValue(double x) const override{
            return cos(x)+x*sin(x);
        }
    };

    E_2_F_1 e2f1;
    E_2_F_2 e2f2;
    Curve E_2({&e2f1,&e2f2},DefinitionDomain{0,6*PI});
    BoundaryCondition_Complete x_BCC(E_2.tangentVector(0,1)[0],E_2.tangentVector(6*PI,1)[1]),
    y_BCC(E_2.tangentVector(0,1)[1],E_2.tangentVector(6*PI,1)[1]);

    for(int i=0;i<3;i++){
        CurveFitter CFU,CFC;

        LatexOutputer o("E2, m="+to_string(foo[i])+".tex");
        o.quickStart("Problem E, 2, m="+to_string(foo[i]));
        o.addLine(E_2.generateValueList(5000),"exact curve","dashed");

        CFU.fit(knotMode::Uniform,E_2.generateValueList(foo[i]),x_BCC,y_BCC);
        CFU.print_Latex_Sole(o,"uniform knots");

        CFC.fit(knotMode::CumulativeChordal,E_2.generateValueList(foo[i]),x_BCC,y_BCC);
        CFC.print_Latex_Sole(o,"cumulative chordal knots");

        o.quickEnd();
    }

    //E, Problem 3
    class E_3_F_1:public Function{
        double getValue(double x) const override{
            return sin(cos(x))*cos(sin(x));
        }
    };

    class E_3_F_2:public Function{
        double getValue(double x) const override{
            return sin(cos(x))*sin(sin(x));
        }
    };

    class E_3_F_3:public Function{
        double getValue(double x) const override{
            return cos(cos(x));
        }
    };
    E_3_F_1 e3f1;
    E_3_F_2 e3f2;
    E_3_F_3 e3f3;
    Curve E_3({&e3f1,&e3f2,&e3f3},DefinitionDomain{0,2*PI});

    for(int i=0;i<3;i++){
        SphereCurveFitter CFU,CFC;

        LatexOutputer o("E3, m="+to_string(foo[i])+".tex",1);
        o.quickStart("Problem E, 3, m="+to_string(foo[i]));
        o.addLine(E_3.generateValueList(5000),"exact curve","thick");

        CFU.fit(knotMode::Uniform,E_3.generateValueList(foo[i]));
        CFU.print_Latex_Sole(o,"uniform knots");

        CFC.fit(knotMode::CumulativeChordal,E_3.generateValueList(foo[i]));
        CFC.print_Latex_Sole(o,"cumulative chordal knots");

        o.quickEnd();
    }

    cout<< ".tex files generated."<<endl;
}