#pragma once
#include"PpFormSpline.hpp"

/**
 * @brief It is derived from Spline, not PpFormSpline. Reasons are in details.
 * 
 * Pp-form spline in S_3^2 is abbreviated by mathematical derivation. 
 * Then it's algorithm is completely different from Pp-form spline in S_n^{n-1}, so we derive it from Spline, not PpFormSpline.
 */
class PFS3:public Spline{
public:
    PFS3():Spline(3,2){}
private:
    void generate_A(const FunctionPointList& fList,const BoundaryCondition& boundaryCondition,const IndependentVariableList& knotList) override;
    Eigen::VectorXd generate_b(const FunctionPointList& fList) override;
    void addBoundaryCondition(Eigen::MatrixXd* A,Eigen::VectorXd* b,const BoundaryCondition& boundaryCondition,const FunctionPointList& fList) override;
    void generate_PiecePoly(const Eigen::VectorXd& b,const FunctionPointList& fList,const BoundaryCondition& boundaryCondition) override;
public:
    void generate(const Spline* s,FunctionPointList fList,const BoundaryCondition& boundaryCondition){
        Spline::generate(s,fList,boundaryCondition);
    }
    void print_Latex(const string& filename,const string& function_string,const Function& function_obj,const string& graphName=""){
        Spline::print_Latex(filename,function_string,function_obj,0,graphName);
    }
};