/**
 * @file
 * @brief Include declaration of class `BernsteinPolynomial`
*/

#include"Polynomial.hpp"

/**
 * @brief generate Bernstein polynomial with given parameter n and k.
*/
class BernsteinPolynomial:public Polynomial{
public:
    BernsteinPolynomial(int n,int k);
};