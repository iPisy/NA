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
    Interpolator(const Function& f):f(f){}
    Interpolator(const Function& f,const vector<double>& vec):f(f),interpolatingPoints(vec){}
    void setInterpolatingPoints(const vector<double>& vec){
        interpolatingPoints=vec;
    }
    const vector<double>& getInterpolatingPoints() const{
        return interpolatingPoints;
    }
    virtual Polynomial interpolate() const=0;
protected:
    const Function& f;
    vector<double> interpolatingPoints;
};