#include"PiecewisePolynomial.hpp"
#include<Eigen/Dense>

class Spline{
protected:
    struct BoundaryCondition{
        enum class Type{
            Complete,
            Natural,
            Periodic,
            Theorem3_58
        };
        Type type;
        double l,r;
        BoundaryCondition(Type type=Type::Periodic,double l=0,double r=0):type(type),l(l),r(r){}
    };

private:
    virtual void generate_A(const FunctionPointList& fList,const BoundaryCondition& boundaryCondition,const IndependentVariableList& knotList)=0;
    virtual Eigen::VectorXd generate_b(const FunctionPointList& fList,const BoundaryCondition& boundaryCondition)=0;
    virtual void generate_piecePoly(const Eigen::VectorXd& b)=0;

protected:
    int n,k,N;
    Eigen::MatrixXd* A;
    PiecewisePolynomial piecewisePolynomial;

public:
    Spline(int n,int k):n(n),k(k),A(nullptr){}

    /**
     * @brief generate a spline.
     * 
     * @param s In curve fitting, the matrix is already generated. Thus we can reuse it.
     * @param fList A list of points on the function.
     * @param boundaryCondition Boundary condition of the spline. The default value is periodic.
     * @param knotList Knots of the spline. The default value means that they fall on points in fList.
     */
    void generate(const Spline* s,const FunctionPointList& fList,const BoundaryCondition& boundaryCondition={},const IndependentVariableList& knotList={});

    void print_Latex(const string& filename,const string& function_string,const Function* function_class,const string& graphName="");
};