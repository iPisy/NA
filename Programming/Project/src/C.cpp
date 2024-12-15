#include"../lib/Function.hpp"
#include"../lib/BFormSpline_3^2.hpp"
#include"../lib/BFormSpline_Thm3.58.hpp"
#include"../lib/Function.hpp"

int main(){
    class F:public Function{
        using Function::Function;
        double getValue(double x) const override{
            return 1/(1+x*x);
        }
    };

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

    LatexOutputer o("C.tex");
    o.quickStart("Problem C");
    o.addLine("{1/(1+x*x)}","exact function","dashed",f.get_definitionDomain());
    Thm3_57.print_Latex_Sole(o,1,"spline of Theorem 3.57");
    Thm3_58.print_Latex_Sole(o,1,"spline of Theorem 3.58");
    o.quickEnd();

    cout<< ".tex files generated."<<endl;
}