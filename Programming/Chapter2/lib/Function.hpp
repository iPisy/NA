/**
 * @file
 * @brief Include declaration of class `Function`.
*/
#pragma once
//This class is an abstract class. It defines what function is.

/**
 * @brief The base class and an abstract class, defining the characteristics of function.
 *  
 * Users can derive it by offering the definition of assignment and derivation operation to get a certain function. 
*/
class Function{
public:
    //Definition of the function.
    virtual double operator()(double x) const=0;

    //Definition of the derivative function.
    //If we use difference quotient, it might be not precise. So we need override it temporarily.
    //those order>=2 is not defined. If it is not override but called, program will throw an exception and exit.
    virtual double derivative(double x,int order) const;
};

double throwException();