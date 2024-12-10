#pragma once
#include"Spline.hpp"

class BFormSpline:public Spline{
private:
    // virtual void generateBC(Eigen::VectorXd* b) const;
    void reuse(const Spline* s) override;
    void generate_A(const FunctionPointList& fList,const BoundaryCondition& boundaryCondition,const IndependentVariableList& knotList) override;
    void generate_bases(const FunctionPointList& fList);
    void generate_bases(const IndependentVariableList& knotList);
    Eigen::VectorXd generate_b(const FunctionPointList& fList) override;
    virtual void addBoundaryCondition(Eigen::MatrixXd* A,Eigen::VectorXd* b,const BoundaryCondition& boundaryCondition,const FunctionPointList& fList) override;
    void generate_piecePoly(Eigen::VectorXd& b) override;
protected:
    vector<PiecewisePolynomial>* bases;
    void periodicBoundaryCondition(Eigen::MatrixXd* A,Eigen::VectorXd* b,const FunctionPointList& fList);
public:
    BFormSpline(int n):Spline(n,n-1){}
    void draw_GivenCoef(const vector<double>& coefs,const IndependentVariableList& knotList,const string& filename);
};