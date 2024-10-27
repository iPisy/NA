#include"Function.hpp"

double Function::derivative(double x) const {
    //difference quotient
    //for function whose derivation is hard to get.
    const double delta=1e-6;
    return (operator()(x+delta/2)-operator()(x-delta/2))/delta;
}