#include"Spline.hpp"

class BFormSpline:public Spline{
private:
    vector<PiecewisePolynomial>* bases;
    // virtual void generateBC(Eigen::VectorXd* b) const;
    void reuse(const Spline* s) override;
    void generate_A(const FunctionPointList& fList,const BoundaryCondition& boundaryCondition,const IndependentVariableList& knotList) override;
    void generate_bases(const FunctionPointList& fList);
    void generate_bases(const IndependentVariableList& knotList);
    Eigen::VectorXd generate_b(const FunctionPointList& fList) override;
    virtual void addBoundaryCondition(Eigen::MatrixXd* A,Eigen::VectorXd* b,const BoundaryCondition& boundaryCondition,const FunctionPointList& fList) override;
    void periodicBoundaryCondition(Eigen::MatrixXd* A,Eigen::VectorXd* b,const FunctionPointList& fList);
    void generate_piecePoly(Eigen::VectorXd& b) override;
public:
    BFormSpline(int n):Spline(n,n-1){}
};