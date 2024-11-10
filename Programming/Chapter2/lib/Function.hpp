/**
 * @file
 * @brief Declaration of class @ref Function.
*/
#pragma once
#include<limits>
#include"DS&Constants.hpp"
#include"Exceptions.hpp"

using namespace std;

/**
 * @brief The base class and an abstract class, defining the characteristics of function.
 *  
 * Users can derive it by offering the definition of assignment and derivation operation to get a certain function. 
*/
class Function{
public:

    /**
     * @brief Get the value of function at point x. Public method.
     * 
     * Implemented by calling internal method @ref getValue.
    */
    double operator()(double x) const;

    /**
     * @brief Get the value of order `order` derivative in a certain direction at point x.
     * 
     * @details We use central difference quotient there, it might be not precise. So we need override it if necessary.
     * And those order>=2 is not defined, then if it is not overridden but called, program will throw an exception and exit.
     * @param x the point.
     * @param order the order of the derivative.
     * @param direction the direction of derivative. @b DEFAULT means without direction. Otherwise we actually give 
     * the derivative at x+(-)delta/2 to avoid the nan return value at characteristic points. 
     * With default definition of derivative, it returns right(left) difference quotient.
    */
    virtual double derivativeValue(double x,int order,Direction direction=Direction::DEFAULT) const;

    Function(double l=numeric_limits<double>::lowest(),double r=numeric_limits<double>::max(),bool leftClosed=1,bool rightClosed=1):
    l(l),r(r),leftClosed(leftClosed),rightClosed(rightClosed){}

    /**
     * @brief generate a list of uniformly distributed points within the definition domain of the function.
     * 
     * @param m number of points. As it includes the endpoints, it should >= 2.
     * @param derivative_order the highest derivative order of the point.
    */
    FunctionPointList generatePointList(int number,int derivative_order=0) const;

    /**
     * @brief generate a list of points, given the independent variable list.
     * 
     * @param in independent variable list.
     * @param derivative_order the highest derivative order of the point.
    */
    FunctionPointList generatePointList(const IndependentVariableList& in,int derivative_order) const;

    void set_l(double l){this->l=l;}

    void set_r(double r){this->r=r;}

    double get_l() const{
        if(leftClosed) return l;
        return l+EPSILON;
    }

    double get_r() const{
        if(rightClosed) return r;
        return r-EPSILON;
    }

    bool get_leftClosed() const{
        return leftClosed;
    }

    bool get_rightClosed() const{
        return rightClosed;
    }

protected:

    /**
     * @brief Internal method of @ref operator(). Need to be overridden.
    */
    virtual double getValue(double x) const=0;

    double l,r;///< The 2 endpoints of the domain of definition.

    bool leftClosed,rightClosed;///< is 1 if the domain is closed at the endpoint, otherwise 0.

    /**
     * @brief check if the point is in the definition domain. 
    */
    bool InDefinitionDomain(double x) const{
        return x>=l && x<=r;
    }

};