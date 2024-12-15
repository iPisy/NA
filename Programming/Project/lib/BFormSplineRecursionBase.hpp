#pragma once
#include"PiecewisePolynomial.hpp"

class BFSRB:public PiecewisePolynomial{
public:
    /*
    Set lClosed=rClosed=1 cause redefinition at knots. 
    However,as the spline is continuous, it's okay.
    By this, we can solve the problem of absence of definition at the endpoint of spline's definition domain. 
    */
    BFSRB(double l,double r):PiecewisePolynomial(Polynomial(vector<double>{1},DefinitionDomain{l,r})){}
};