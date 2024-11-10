/**
 * @file
 * @brief Declaration of class @ref Interpolator.
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
    Interpolator(const FunctionPointList& init):interpolationPoints(init){}
    void setInterpolationPoints(const FunctionPointList& vec){
        interpolationPoints=vec;
    }
    const FunctionPointList& getInterpolationPoints() const{
        return interpolationPoints;
    }
    virtual Polynomial interpolate() const=0;
protected:
    FunctionPointList interpolationPoints;
};