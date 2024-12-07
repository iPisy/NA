/**
 * @file
 * @brief Declaration of class @ref PolynomialCurve.
*/
#pragma once
#include"Polynomial.hpp"
#include"Curve.hpp"
#include<limits>

using namespace std;

/**
 * @brief A sort of @ref Curve, whose function in direction of every basis vector is @ref Polynomial.
 * 
 * @details As @ref Polynomial is a sort of @ref Function, polymorphism automatically update the 
 * implementation of member function in @ref Curve.
*/
class PolynomialCurve:public Curve{
public:
    PolynomialCurve(const DefinitionDomain& definitionDomain={}):
    Curve(definitionDomain){}

    PolynomialCurve(const vector<const Polynomial*>& curve_Function,const DefinitionDomain& definitionDomain):
    Curve(vector<const Function*>(curve_Function.begin(),curve_Function.end()),definitionDomain){}

protected:
    /**
     * @brief change the curve's pointer to polynomial's pointer. 
    */
    static const Polynomial* toPolynomial(const Function* in){
        return static_cast<const Polynomial*>(in);
    }
};