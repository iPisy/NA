#pragma once
#include"Function.hpp"
#include"Polynomial.hpp"
#include<vector>

using namespace std;

/**
 * @brief A piecewise function. Each piece of the function is Polynomial.
 * 
 * Assume each polynomial's definition dom is 
 */
class PiecewisePolynomial:public Function{
private:
    vector<Polynomial> def;

    //overrides
    double getValue(double x) const override;
    double getDerivativeValue(double x,int order=1) const override;

    /**
     * @brief find the polymonial whose 
     * 
     * @return the index of the polynomial.
     */
    int findPolynomial(double x) const;
public:
    PiecewisePolynomial():Function(DefinitionDomain{0,0,0,0}){}
    PiecewisePolynomial(const vector<Polynomial>& init);

    void insertPolynomial(const Polynomial& in);
};