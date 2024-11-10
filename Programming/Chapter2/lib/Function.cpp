/**
 * @file
 * @brief Implement functions of class @ref Function.
*/
#include"Function.hpp"
#include<iostream>
#include<cstdlib>
#include"Exceptions.hpp"

using namespace std;

const double delta=1e-6;

double Function::operator()(double x) const{
    if(InDefinitionDomain(x)) return getValue(x);
    throw Out_DomainException{};
}

double Function::derivativeValue(double x,int order,Direction direction) const{
    
    if(order==1){
        if(direction==Direction::DEFAULT) return ((*this)(x+delta/2)-(*this)(x-delta/2))/delta;
        if(direction==Direction::left) return derivativeValue(x-delta/2,order);
        else return derivativeValue(x+delta/2,order);
    }

    throw NotDefinedException{};
}

FunctionPointList Function::generatePointList(int number,int derivative_order) const{
    if(number<=1) throw InvalidInputException{};
    IndependentVariableList foo;
    double start=get_l(),end=get_r();
    double delta=(end-start)/(number-1);
    for(int i=1;i<=number;i++){
        foo.push_back(start);
        start+=delta;
    }
    foo.back()=end;
    return generatePointList(foo,derivative_order);
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