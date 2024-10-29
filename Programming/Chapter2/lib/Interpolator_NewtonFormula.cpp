/**
 * @file
 * @brief Implement the function in `Interpolator_NewtonFormula.hpp`.
*/
#include"Interpolator_NewtonFormula.hpp"
#include"Polynomial.hpp"

Polynomial Interpolator_N::interpolate() const{
    int l=interpolatingPoints.size();
    vector<vector<double>> differenceQuotientTable(l,vector<double>(l));
    //init
    for(int i=0;i<l;i++){
        differenceQuotientTable[i][0]=f(interpolatingPoints[i]);
    }
    //dp
    for(int j=1;j<l;j++){
        for(int i=0;i<l-j;i++){
            differenceQuotientTable[i][j]=calculateDifferenceQuotient(differenceQuotientTable,i,j);
        }
    }
    Polynomial p;
    Polynomial pai({1});
    for(int i=0;i<l;i++){
        p+=pai*differenceQuotientTable[0][i];
        pai*=Polynomial({-interpolatingPoints[i],1});
    }
    return p;
}

double Interpolator_N::calculateDifferenceQuotient(const vector<vector<double>>& table,int i,int j) const{
    return (table[i+1][j-1]-table[i][j-1])/(interpolatingPoints[i+j]-interpolatingPoints[i]);
}