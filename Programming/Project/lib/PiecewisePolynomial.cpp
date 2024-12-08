#include"PiecewisePolynomial.hpp"

PiecewisePolynomial::PiecewisePolynomial(const vector<Polynomial>& init):PiecewisePolynomial(){
    for(auto& it:init){
        this->insertPolynomial(it);
    }
}

Polynomial* PiecewisePolynomial::findPolynomial(double x) const{
    
}