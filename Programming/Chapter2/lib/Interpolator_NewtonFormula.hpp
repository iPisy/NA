/**
 * @file
 * @brief Include declaration of class `Interpolator_N`
*/
#pragma once
#include"Polynomial.hpp"
#include"Function.hpp"
#include"Interpolator.hpp"
#include<vector>
using namespace std;

/**
 * @brief The subclass of `Interpolator`. It can solve non-Hermite interpolation problem with Newton formula.
*/
class Interpolator_N:public Interpolator{
public:
    Interpolator_N(const Function& f):Interpolator(f){}
    Interpolator_N(const Function& f,const vector<double>& vec):Interpolator(f,vec){}
    /**
     * @brief It generate interpolation polynomial and return it.
     * 
     * It bases on the given function and interpolating points, and uses Newton formula to generate.
     * It create a difference quotient table, the operation of calculate it's element is implemented by 
     * calling virtual function `calculateDifferenceQuotient`, it can be overriden and thus can 
     * imply on Hermite problem.
    */
    Polynomial interpolate() const override;
protected:
    /**
     * @brief Calculate the element of difference quotient table. It can be overriden and imply on Hermite problem.
    */
    virtual double calculateDifferenceQuotient(const vector<vector<double>>& table,int i,int j) const;
};