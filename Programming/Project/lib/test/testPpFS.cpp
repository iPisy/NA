#include"../PpFormSpline.hpp"
#include"../PpFormSpline_3^2.hpp"

class F:public Function{
    using Function::Function;
    double getValue(double x) const override{
        return 1/(1+x*x);
    }
};

int main(){

    /*
    compile:
    make runTest && cd bin/test && pdflatex PpFS.tex && xdg-open PpFS.pdf && cd ../..
    */

    F f(DefinitionDomain{-1.3,1});

    // PpFormSpline s1(7);
    // s1.generate(nullptr,f.generatePointList(9));
    // // s1.generate(nullptr,FunctionPointList{{1,{0}},{2,{0.6931}},{3,{0.6931}}},BoundaryCondition_Periodic());
    // s1.print_Latex("PpFS.tex","{0}",f);

    // PpFormSpline s(3);
    PFS3 s;
    s.generate(nullptr,{{-1.3,{4.1}},{-1,{4.3}},{0,{4.1}},{1,{3.0}}},BoundaryCondition_Periodic());
    s.print_Latex("PpFS.tex","{4}",f);

    // cout<<"========="<<endl;

    // PFS3 pfs3;
    // // pfs3.generate(nullptr,FunctionPointList{{1,{0}},{2,{0.6931}},{3,{1.0986}},{4,{1.3863}},{6,{1.7918}}},BoundaryCondition_Complete(1,0.1667));
    // pfs3.generate(nullptr,f.generatePointList(9),BoundaryCondition_Complete(-5,4));
    // // pfs3.generate(nullptr,f.generatePointList(9),BoundaryCondition_Periodic());
    // PFS3 parallel;
    // parallel.generate(&pfs3,f.generatePointList(9),BoundaryCondition_Complete(-8,10));
    // parallel.print_Latex("PpFS.tex","{1/(1+x*x)}",f);

    // PiecewisePolynomial p=s1.piecewisePolynomial;
    // Polynomial foo=p.polys[p.findPolynomial(-2)];
    // cout<<"======"<<endl;
    // for(int i=0;i<3;i++){
    //     foo.getDerivative(i);
    //     cout<<"======"<<endl;
    // }
    // for(int i=0;i<3;i++){
    //     cout<<p.derivativeValue(-2,i)<<endl;
    //     cout<<p.derivativeValue(1,i)<<endl;
    //     cout<<"======"<<endl;
    // }
}

