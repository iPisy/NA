#include"Function.hpp"
#include<iostream>
#include<cstdlib> 

using namespace std;

double Function::derivative(double x,int order) const{
    //difference quotient
    //for function whose derivation is hard to get.
    const double delta=1e-6;
    if(order==1) return ((*this)(x+delta/2)-(*this)(x-delta/2))/delta;

    return throwException();
}

double throwException(){
    cerr<< "Error! Higher derivative is not defined!" <<endl;
    exit(-1);
    return 0;
}