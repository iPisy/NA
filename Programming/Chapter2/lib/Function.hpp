#pragma once
//This class is an abstract class. It defines what function is.
class Function{
public:
    //Definition of the function.
    virtual double operator()(double x) const=0;

    //Definition of the derivative function.
    //If we use difference quotient, it might be not precise. So we need override it temporarily.
    virtual double derivative(double x) const;
};