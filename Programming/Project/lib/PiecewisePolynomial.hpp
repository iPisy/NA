#pragma once
#include"Function.hpp"
#include"Polynomial.hpp"
#include<vector>
#include"LatexOutputer.hpp"

using namespace std;

/**
 * @brief A piecewise function. Each piece of the function is Polynomial.
 * 
 * This class is designed only for @ref Spline. Don't use it in other project.
 */
class PiecewisePolynomial:public Function{
private:
    vector<Polynomial> polys;

    //overrides
    double getValue(double x) const override;
    double getDerivativeValue(double x,int order=1) const override;

    /**
     * @brief find the polymonial whose definition domain include x.
     * 
     * @return the index of the polynomial.
     * - `-1` if x falls at the lhs of the definition domain.  
     * - `def.size()` if x falls at the rhs of the definition domain.
     */
    // called when not empty.
    int findPolynomial(double x) const;

public:
    //ctors
    PiecewisePolynomial():Function(DefinitionDomain{0,0,0,0}){}
    PiecewisePolynomial(const Polynomial& init):Function(init.get_definitionDomain()){polys.push_back(init);}
    PiecewisePolynomial(const vector<Polynomial>& init);

    friend PiecewisePolynomial operator+(const PiecewisePolynomial& lhs,const PiecewisePolynomial& rhs);
    friend PiecewisePolynomial operator*(const PiecewisePolynomial& lhs,const Polynomial& rhs);

    void print_Latex_SolePoly(LatexOutputer& o,int n=0,const string& PP_Name="") const;

    void print_Latex(const string& filename,int n=0) const;
};

PiecewisePolynomial operator+(const PiecewisePolynomial& lhs,const PiecewisePolynomial& rhs);

void operator+=(PiecewisePolynomial& lhs,const PiecewisePolynomial& rhs);

PiecewisePolynomial operator*(const PiecewisePolynomial& lhs,const Polynomial& rhs);