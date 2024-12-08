#include"PiecewisePolynomial.hpp"

class Spline{
protected:
    int n,k,N;
    PiecewisePolynomial piecewisePolynomial;
public:
    Spline(int n,int k):n(n),k(k){}
};