/**
 * @brief Declaration of class @ref PolynomialCurve.
*/
#pragma once
#include"Polynomial.hpp"
#include"Curve.hpp"
#include<limits>

using namespace std;

/**
 * @brief It's a sort of @ref Curve, whose function in direction of every basis vector is @ref Polynomial.
 * 
 * @details As @ref Polynomial is a sort of @ref Function, polymorphism automatically update the 
 * implementation of member function in @ref Curve.
*/
class PolynomialCurve:public Curve{
public:
    PolynomialCurve(double l=numeric_limits<double>::lowest(),double r=numeric_limits<double>::max(),bool leftClosed=1,bool rightClosed=1):
    Curve(l,r,leftClosed,rightClosed){}

    PolynomialCurve(const vector<const Polynomial*>& curve_Function,double l=numeric_limits<double>::lowest(),double r=numeric_limits<double>::max(),bool leftClosed=1,bool rightClosed=1):
    Curve(vector<const Function*>(curve_Function.begin(),curve_Function.end()),l,r,leftClosed,rightClosed){}

protected:
    /**
     * @brief change the curve's pointer to polynomial's pointer. 
    */
    const Polynomial* ToPolynomial(const Function* in) const{
        return static_cast<const Polynomial*>(in);
    }
};