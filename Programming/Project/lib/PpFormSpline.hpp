#pragma once
#include"Spline.hpp"

/**
 * @brief Consider k=n-1.
 */
class PpFormSpline:public Spline{
public:
    PpFormSpline(int n):Spline(n,n-1){}
protected:
    void periodicBoundaryCondition(Eigen::MatrixXd* A,Eigen::VectorXd* b,const FunctionPointList& fList);
private:
    void generate_A(const FunctionPointList& fList,const BoundaryCondition& boundaryCondition,const IndependentVariableList& knotList) override;
    Eigen::VectorXd generate_b(const FunctionPointList& fList) override;
    virtual void addBoundaryCondition(Eigen::MatrixXd* A,Eigen::VectorXd* b,const BoundaryCondition& boundaryCondition,const FunctionPointList& fList) override;
    void generate_piecePoly(Eigen::VectorXd& b,const FunctionPointList& fList) override;
};