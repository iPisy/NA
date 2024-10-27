#pragma once
#include"Polynomial.hpp"
#include"Function.hpp"
#include<vector>
using namespace std;

class Interpolator{
public:
    Interpolator(const Function& f,const vector<double>& init):f(f),interpolatingPoints(init){}
    Polynomial interpolate();
private:
    const Function& f;
    vector<double> interpolatingPoints;
};