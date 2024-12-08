/**
 * @file
 * @brief Implement functions of class @ref Function.
*/
#include"Function.hpp"
#include<iostream>
#include<cstdlib>
#include"Exceptions.hpp"

using namespace std;

double Function::operator()(double x) const{
    if(definitionDomain.inDefinitionDomain(x)) return getValue(x);
    throw Out_DefinitionDomainException{};
}

double Function::derivativeValue(double x,int order) const{
    if(definitionDomain.inDefinitionDomain(x)) return getDerivativeValue(x,order);
    else throw Out_DefinitionDomainException{};
}

FunctionPointList Function::generatePointList(int number,int derivative_order) const{
    return generatePointList(definitionDomain.generateVariableList(number),derivative_order);
}

FunctionPointList Function::generatePointList(const IndependentVariableList& in,int derivative_order) const{
    FunctionPointList ret;
    for(auto& it:in){
        FunctionPoint foo;
        foo.x=it;
        foo.value.push_back((*this)(it));
        for(int i=1;i<=derivative_order;i++){
            foo.value.push_back(this->derivativeValue(it,i));
        }
        ret.push_back(foo);
    }
    return ret;
}

/**
 * @brief a default definition of order=1, using difference quotient.
 */
double Function::getDerivativeValue(double x,int order) const{
    if(order==1){
        if(x==definitionDomain.r) return derivativeValue(x-DELTA/2,order);
        else if(x==definitionDomain.l) return derivativeValue(x+DELTA/2,order);
        else return ((*this)(x+DELTA/2)-(*this)(x-DELTA/2))/DELTA;
    }
    throw NotDefinedException{};
}