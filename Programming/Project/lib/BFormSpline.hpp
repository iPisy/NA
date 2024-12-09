#include"Spline.hpp"

class BFormSpline:public Spline{
private:
    vector<PiecewisePolynomial>* bases;
    // virtual void generateBC(Eigen::VectorXd* b) const;
    void generate_A(const FunctionPointList& fList,const BoundaryCondition& boundaryCondition,const IndependentVariableList& knotList) override;
    void generate_bases(const FunctionPointList& fList);
    void generate_bases(const IndependentVariableList& knotList);
    Eigen::VectorXd generate_b(const FunctionPointList& fList,const BoundaryCondition& boundaryCondition) override;
    void generate_piecePoly(const Eigen::VectorXd& b) override;
    
public:
    BFormSpline(int n):Spline(n,n-1){}

    
};