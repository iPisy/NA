#include"Function.hpp"

double Function::derivative(double x) const {
    //difference quotient
    //for function whose derivation is hard to get.
    const double delta=1e-6;
    return ((*this)(x+delta/2)-(*this)(x-delta/2))/delta;
}