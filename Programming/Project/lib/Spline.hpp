#pragma once
#include"PiecewisePolynomial.hpp"
#include<Eigen/Dense>
#include"Exceptions.hpp"
#include"BoundaryConditions.hpp"

class Spline{
private:
    virtual void generate_A(const FunctionPointList& fList,const BoundaryCondition& boundaryCondition,const IndependentVariableList& knotList)=0;
    virtual Eigen::VectorXd generate_b(const FunctionPointList& fList)=0;
    virtual void addBoundaryCondition(Eigen::MatrixXd* A,Eigen::VectorXd* b,const BoundaryCondition& boundaryCondition,const FunctionPointList& fList)=0;
    virtual void generate_PiecePoly(const Eigen::VectorXd& b,const FunctionPointList& fList,const BoundaryCondition& boundaryCondition)=0;

protected:
    int n,k,N;
    Eigen::MatrixXd* A;
    PiecewisePolynomial piecewisePolynomial;
    friend class CurveFitter;
    friend class SphereCurveFitter;

    /**
     * @brief Reuse calculated things, e.g. A(in spline) and bases(in B-form spline).
     */
    virtual void reuse(const Spline* s){A=s->A;}
    bool reused;///< ==1 if the spline reuse A. Then there is no need to add boundary condition for A.

    /**
     * @param offside for B-form splines. Avoid drawing out of domain.
     */
    void print_Latex(const string& filename,const string& function_string,const Function& function_obj,bool offside,const string& graphName="") const;

public:
    Spline(int n,int k):n(n),k(k),A(nullptr),reused(0){
        if(n%2==0 && n>2) cout<<"\033[31mWarning: if the order of the spline is even, the problem may be ill-posed. Then interpolation may fail.\033[0m"<<endl;
    }

    /**
     * @brief generate a spline.
     * 
     * @param s In curve fitting, the matrix is already generated. Thus we can reuse it.
     * @param fList A list of points on the function.
     * @param boundaryCondition Boundary condition of the spline. The default value is periodic.
     * @param knotList Knots of the spline. The default value means that they fall on points in fList.
     */
    void generate(const Spline* s,FunctionPointList fList,const BoundaryCondition& boundaryCondition=BoundaryCondition_Periodic{},const IndependentVariableList& knotList={});

    double operator()(double x) const{
        return piecewisePolynomial(x);
    }

    void print_Latex_Sole(LatexOutputer& o,bool offside,const string& legendentry) const{
        piecewisePolynomial.print_Latex_SolePoly(o,offside?n:0,legendentry);
    }

};