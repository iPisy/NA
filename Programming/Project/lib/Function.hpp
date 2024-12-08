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
    */
    double derivativeValue(double x,int order=1) const;

    Function(const DefinitionDomain& definitionDomain={}):
    definitionDomain(definitionDomain){}

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

    void set_l(double l){this->definitionDomain.l=l;}

    void set_r(double r){this->definitionDomain.r=r;}

    void set_lClosed(bool lClosed){this->definitionDomain.lClosed=lClosed;}

    void set_rClosed(bool rClosed){this->definitionDomain.rClosed=rClosed;}

    void set_definitionDomain(const DefinitionDomain& definitionDomain){this->definitionDomain=definitionDomain;}

    double get_l() const{
        return definitionDomain.get_l();
    }

    double get_r() const{
        return definitionDomain.get_r();
    }

    bool get_leftClosed() const{
        return definitionDomain.lClosed;
    }

    bool get_rightClosed() const{
        return definitionDomain.rClosed;
    }

    DefinitionDomain get_definitionDomain() const{
        return definitionDomain;
    }

protected:
    DefinitionDomain definitionDomain;
private:
    /**
     * @brief Internal method of @ref operator(). Need to be overridden.
    */
    virtual double getValue(double x) const=0;

    /**
     * @brief Internal method of @ref derivativeValue. Need to be overridden.
    */
    virtual double getDerivativeValue(double x,int order) const;
};