#include"Interpolator.hpp"
#include"Polynomial.hpp"
#define DEBUG 0
#if DEBUG

#endif

Polynomial Interpolator::interpolate(){
    int l=interpolatingPoints.size();
    vector<vector<double>> differenceQuotientTable(l,vector<double>(l));
    //init
    for(int i=0;i<l;i++){
        differenceQuotientTable[i][0]=f(interpolatingPoints[i]);
    }
    #if DEBUG
            cout<< differenceQuotientTable[0][0] <<endl;
        #endif
    //dp
    for(int j=1;j<l;j++){
        for(int i=0;i<l-j;i++){
            differenceQuotientTable[i][j]=(differenceQuotientTable[i+1][j-1]-differenceQuotientTable[i][j-1])/
                (interpolatingPoints[i+j]-interpolatingPoints[i]);
        }
        #if DEBUG
            cout<< differenceQuotientTable[0][j] <<endl;
        #endif
    }
    Polynomial p;
    Polynomial pai({1});
    for(int i=0;i<l;i++){
        p+=pai*differenceQuotientTable[0][i];
        pai*=Polynomial({-interpolatingPoints[i],1});
        #if DEBUG
            cout<<"p_"<<i<<"(x)=";
            p.print();
            cout<<endl;
            cout<<"pai_"<<i+1<<"(x)=";
            pai.print();
            cout<<endl;
        #endif
    }
    return p;
}