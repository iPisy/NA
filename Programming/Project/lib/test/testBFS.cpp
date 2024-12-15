#include"../BFormSpline.hpp"
#include"../BFormSpline_1^0.hpp"
#include"../BFormSpline_3^2.hpp"
#include"../BFormSpline_Thm3.58.hpp"

class F:public Function{
    using Function::Function;
    double getValue(double x) const override{
        return 1/(1+25*x*x);
    }
};

int main(){

    /*
    compile:
    make runTest && cd bin/test && pdflatex BFS.tex && xdg-open BFS.pdf && cd ../..
    */

    F f(DefinitionDomain{27.7,30});

    // BFS3 s3;
    // s3.generate(nullptr,f.generatePointList(81),)


    // BFS1 s1;
    // s1.generate(nullptr,f.generatePointList(5));
    // s1.print_Latex("BFS.tex","{1/(1+x*x)}",f);

    // BFS_Thm3_58 sThm;
    // sThm.generate(nullptr,f.generatePointList(IndependentVariableList{0}),BoundaryCondition_Theorem3_58(-0.5,f(-0.5),0.5,f(0.5)),IndependentVariableList{-0.5,0.5});
    // sThm.generate(nullptr,f.generatePointList(IndependentVariableList{-1,0,1}),BoundaryCondition_Theorem3_58(-1.5,f(-1.5),1.5,f(1.5)),IndependentVariableList{-1.5,-0.5,0.5,1.5});
    // sThm.print_Latex("BFS.tex","{1/(1+x*x)}",f);

    // BFS3 s3;
    // s3.generate(nullptr,FunctionPointList{{1,{0}},{2,{0.6931}},{3,{1.0986}},{4,{1.3863}},{6,{1.7918}}},BoundaryCondition_Complete(1,0.1667));
    // s3.generate(nullptr,f.generatePointList(9),BoundaryCondition_Periodic());
    // s3.generate(nullptr,f.generatePointList(9),BoundaryCondition_Complete(-8,10));
    // s3.print_Latex("BFS.tex","{1/(1+x*x)}",f);

    // BFormSpline spline(11);
    // spline.draw_GivenCoef(vector<double>{0,1,1,1,1,1,1,1,1},vector<double>{-1,0,1},"BFS.tex");
    // spline.generate(nullptr,f.generatePointList(5));
    // spline.print_Latex("BFS.tex","{1/(1+x*x)}",f);
    // PiecewisePolynomial p=spline.piecewisePolynomial;
    // cout<<p.polys[0]<<endl;
    // for(int i=0;i<3;i++){
    //     cout<<p.derivativeValue(-2,i)<<endl;
    //     cout<<p.derivativeValue(1,i)<<endl;
    //     cout<<"======"<<endl;
    // }

    // BFormSpline s(2);
    // s.generate(nullptr,FunctionPointList{{1,{0}},{2,{0.6931}},{3,{1.0986}},{4,{1.3863}},{6,{1.7918}}},BoundaryCondition_Periodic());
    // s.print_Latex("BFS.tex","{0}",f);

    // BFormSpline s(7);
    // s.generate(nullptr,f.generatePointList(9));
    // BFormSpline par(7);
    // par.generate(&s,f.generatePointList(9));
    // par.print_Latex("BFS.tex","{0}",f);

    BFormSpline s(3);
    s.generate(nullptr,{{27.7,{4.1}},{28,{4.3}},{29,{4.1}},{30,{3.0}}});
    s.print_Latex("BFS.tex","{4}",f);
}