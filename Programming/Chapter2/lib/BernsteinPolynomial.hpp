/**
 * @file
 * @brief Declaration of class @ref BernsteinPolynomial.
*/

#include"Polynomial.hpp"

/**
 * @brief A sort of @ref Polynomial. Can generate a Bernstein polynomial with given parameter n and k through construction.
*/
class BernsteinPolynomial:public Polynomial{
public:
    BernsteinPolynomial(int n,int k);
};