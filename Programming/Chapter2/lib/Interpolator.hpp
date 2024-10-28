#pragma once
#include"Polynomial.hpp"
#include"Function.hpp"
#include<vector>
using namespace std;

/*Base class of interpolators. 
It is a virtual class. The function "interpolate" needs to be overridden.*/
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