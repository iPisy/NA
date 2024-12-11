/**
 * @file
 * @brief Implement functions of class @ref Interpolator_N.
*/
#include"Interpolator_NewtonFormula.hpp"
#include"Polynomial.hpp"

Polynomial Interpolator_N::interpolate() const{
    int l=interpolationPoints.size();
    DifferenceQuotientTable differenceQuotientTable(l,vector<double>(l));
    //init
    for(int i=0;i<l;i++){
        differenceQuotientTable[i][0]=getInitializeValue(differenceQuotientTable,i);
    }
    //dp
    for(int j=1;j<l;j++){
        for(int i=0;i<l-j;i++){
            differenceQuotientTable[i][j]=calculateDifferenceQuotient(differenceQuotientTable,i,j);
        }
    }
    Polynomial p(DefinitionDomain{interpolationPoints[0].x,interpolationPoints.back().x});
    Polynomial pai(vector<double>{1});
    for(int i=0;i<l;i++){
        p+=pai*differenceQuotientTable[0][i];
        pai*=Polynomial(vector<double>{-interpolationPoints[i].x,1});
    }
    return p;
}

double Interpolator_N::calculateDifferenceQuotient(const DifferenceQuotientTable& table,int i,int j) const{
    return (table[i+1][j-1]-table[i][j-1])/(interpolationPoints[i+j].x-interpolationPoints[i].x);
}