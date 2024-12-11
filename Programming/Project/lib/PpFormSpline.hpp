#pragma once
#include"Spline.hpp"

/**
 * @brief Consider k=n-1.
 */
class PpFormSpline:public Spline{
public:
    PpFormSpline(int n):Spline(n,n-1){}
    void print_Latex(const string& filename,const string& function_string,const Function& function_obj,const string& graphName=""){
        Spline::print_Latex(filename,function_string,function_obj,0,graphName);
    }
    void generate(const Spline* s,FunctionPointList fList,const BoundaryCondition& boundaryCondition=BoundaryCondition_Periodic{}){
        Spline::generate(s,fList,boundaryCondition);
    }
protected:
    void periodicBoundaryCondition(Eigen::MatrixXd* A,const FunctionPointList& fList);
private:
    void generate_A(const FunctionPointList& fList,const BoundaryCondition&,const IndependentVariableList&) override;
    Eigen::VectorXd generate_b(const FunctionPointList& fList) override;
    virtual void addBoundaryCondition(Eigen::MatrixXd* A,Eigen::VectorXd* b,const BoundaryCondition& boundaryCondition,const FunctionPointList& fList) override;
    void generate_PiecePoly(const Eigen::VectorXd& b,const FunctionPointList& fList,const BoundaryCondition&) override;
};