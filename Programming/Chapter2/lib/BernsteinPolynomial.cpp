/**
 * @file
 * @brief Implement the function in `BernsteinPolynomial.hpp`.
*/

#include"BernsteinPolynomial.hpp"

/**
 * @brief return m choose n.
*/
double combinatorialNumber(int m,int n){
    if(n>m) return 0;
    double ret=1;
    for(int i=1;i<=n;i++){
        ret*=(m+1-i);
        ret/=i;
    }
    return ret;
}

BernsteinPolynomial::BernsteinPolynomial(int n,int k):Polynomial({combinatorialNumber(n,k)}){
    for(int i=1;i<=k;i++){
        (*this)*=Polynomial({0,1});
    }
    for(int i=1;i<=n-k;i++){
        (*this)*=Polynomial({1,-1});
    }
}