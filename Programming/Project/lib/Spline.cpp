#include"Spline.hpp"
#include"LatexOutputer.hpp"

void Spline::generate(const Spline* s,FunctionPointList fList,const BoundaryCondition& boundaryCondition,const IndependentVariableList& knotList){
    if(boundaryCondition.type!=BoundaryCondition::Type::Theorem3_58) N=fList.size();
    else N=knotList.size();
    if(boundaryCondition.type==BoundaryCondition::Type::Periodic && n!=1) fList.back().value=fList[0].value; 
    if(s!=nullptr){
        reuse(s);
        reuseFlag=1;
    }
    else generate_A(fList,boundaryCondition,knotList);
    Eigen::VectorXd b=generate_b(fList);
    addBoundaryCondition(A,&b,boundaryCondition,fList);
    b=A->partialPivLu().solve(b);
    generate_piecePoly(b);
}

void Spline::print_Latex(const string& filename,const string& function_string,const Function& function_obj,const string& graphName){
    LatexOutputer o(filename);
    o.quickStart();
    o.addLine(function_string,"exact function","dashed",function_obj.get_definitionDomain());
    piecewisePolynomial.print_Latex_SolePoly(o,n,"$spline\\in \\mathbb{S}_{"+to_string(n)+"}^{"+to_string(k)+"}$");
    o.quickEnd();
}