#include"Interpolator.hpp"
#include"Polynomial.hpp"

//can solve Hermite interpolation problem, in which for all m_i<=1.
Polynomial Interpolator::interpolate(){
    int l=interpolatingPoints.size();
    vector<vector<double>> differenceQuotientTable(l,vector<double>(l));
    //init
    for(int i=0;i<l;i++){
        differenceQuotientTable[i][0]=f(interpolatingPoints[i]);
    }
    //dp
    for(int j=1;j<l;j++){
        for(int i=0;i<l-j;i++){
            if(interpolatingPoints[i+j]==interpolatingPoints[i]) differenceQuotientTable[i][j]=
            f.derivative(interpolatingPoints[i]);
            else differenceQuotientTable[i][j]=
                (differenceQuotientTable[i+1][j-1]-differenceQuotientTable[i][j-1])/
                (interpolatingPoints[i+j]-interpolatingPoints[i]);
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