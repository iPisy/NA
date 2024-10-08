#pragma once
//This class is an abstract class. It defines what function is.

class Function {
public:
    //Definition of the function.
    virtual double operator() (double x) const = 0;
    //Definition of the derivative function.
    //If we use difference quotient, it might be not precise. So we need override it temporarily.
    virtual double derivative(double x) const {
        //difference quotient
        //for function whose derivation is hard to get.
        const double delta=1e-6;
        return (operator()(x+delta/2)-operator()(x-delta/2))/delta;
    }
};