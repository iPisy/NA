/**
 * @file
 * @brief Declaration of class @ref Interpolator_N.
*/
#pragma once
#include"Polynomial.hpp"
#include"Function.hpp"
#include"Interpolator.hpp"
#include<vector>
using namespace std;

/**
 * @brief A sort of @ref Interpolator. It can solve non-Hermite interpolation problem with Newton formula.
*/
class Interpolator_N:public Interpolator{
public:
    Interpolator_N():Interpolator(){}
    Interpolator_N(const FunctionPointList& init):Interpolator(init){}
    /**
     * @brief It generate interpolation polynomial and return it.
     * 
     * It bases on the given function and interpolation points, and uses Newton formula to generate.
     * It create a difference quotient table, the operation of calculate it's element is implemented by 
     * calling virtual function `calculateDifferenceQuotient`, it can be overriden and thus can 
     * imply on Hermite problem.
    */
    Polynomial interpolate() const override;
protected:
    /**
     * @brief get value to initialize the difference quotient table. It can be overriden and imply on Hermite problem.
    */
    virtual double getInitializeValue(const vector<vector<double>>& table,int i) const{
        return interpolationPoints[i].value[0];
    }

    /**
     * @brief Calculate the element of difference quotient table. It can be overriden and imply on Hermite problem.
    */
    virtual double calculateDifferenceQuotient(const DifferenceQuotientTable& table,int i,int j) const;
 
};