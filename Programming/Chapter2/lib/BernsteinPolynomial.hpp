/**
 * @file
 * @brief Declaration of class @ref BernsteinPolynomial.
*/

#include"Polynomial.hpp"

/**
 * @brief generate a Bernstein polynomial with given parameter n and k.
*/
class BernsteinPolynomial:public Polynomial{
public:
    BernsteinPolynomial(int n,int k);
};