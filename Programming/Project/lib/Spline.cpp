#include"Spline.hpp"
#include"LatexOutputer.hpp"

void Spline::generate(const Spline* s,const FunctionPointList& fList,const BoundaryCondition& boundaryCondition,const IndependentVariableList& knotList){
    if(boundaryCondition.type!=BoundaryCondition::Type::Theorem3_58) N=fList.size();
    else N=knotList.size();
    if(s!=nullptr) A=s->A;
    else generate_A(fList,boundaryCondition,knotList);
    Eigen::VectorXd b=generate_b(fList,boundaryCondition);
    b=A->partialPivLu().solve(b);
    generate_piecePoly(b);
}

void Spline::print_Latex(const string& filename,const string& function_string,const Function* function_class,const string& graphName){
    LatexOutputer o(filename);
    o.quickStart();
    o.addLine(function_string,"exact function","dashed",function_class->get_definitionDomain());
    piecewisePolynomial.print_Latex_SolePoly(o,n,"Spline");
    o.quickEnd();
}