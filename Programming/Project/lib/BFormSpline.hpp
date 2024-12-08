#include"Spline.hpp"
#include<Eigen/Dense>

class BFormSpline:public Spline{
private:
    Eigen::MatrixXd* A;
    vector<PiecewisePolynomial>* bases;
    virtual void generateBC(Eigen::VectorXd* b) const;
protected:
    enum class BoundaryCondition{
        Complete,
        Natural,
        Periodic,
        Theorem3_58
    };
public:
    BFormSpline(int n):Spline(n,n-1){}

    void generate(const BFormSpline& s,const FunctionPointList& list,BoundaryCondition boundaryCondition=BoundaryCondition::Periodic);

    void 
}