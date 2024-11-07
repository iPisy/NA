/**
 * @file
 * @brief Include declaration of class `Interpolator`
*/
#pragma once
#include"Polynomial.hpp"
#include"Function.hpp"
#include<vector>
using namespace std;

/**
 * @brief The base class and an abstract class, defining interpolators.
 * 
 * The function `interpolate` needs to be implemented by subclasses. 
*/
class Interpolator{
public:
    Interpolator(){}
    Interpolator(const FunctionPointList& init):interpolatingPoints(init){}
    void setInterpolatingPoints(const FunctionPointList& vec){
        interpolatingPoints=vec;
    }
    const FunctionPointList& getInterpolatingPoints() const{
        return interpolatingPoints;
    }
    virtual Polynomial interpolate() const=0;
protected:
    FunctionPointList interpolatingPoints;
};