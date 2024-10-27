#pragma once
#include"Polynomial.hpp"
#include"Function.hpp"
#include<vector>
using namespace std;

class Interpolator{
public:
    Interpolator(const Function& f):f(f){}
    Interpolator(const Function& f,const vector<double>& vec):f(f),interpolatingPoints(vec){}
    void setInterpolatingPoints(const vector<double>& vec){
        interpolatingPoints=vec;
    }
    Polynomial interpolate();
private:
    const Function& f;
    vector<double> interpolatingPoints;
};