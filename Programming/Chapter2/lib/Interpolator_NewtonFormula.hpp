#pragma once
#include"Polynomial.hpp"
#include"Function.hpp"
#include"Interpolator.hpp"
#include<vector>
using namespace std;

//This class can solve non-Hermite interpolation problem with Newton formula.
class Interpolator_N:public Interpolator{
public:
    Interpolator_N(const Function& f):Interpolator(f){}
    Interpolator_N(const Function& f,const vector<double>& vec):Interpolator(f,vec){}
    Polynomial interpolate() const override;
protected:
    virtual double calculateDifferenceQuotient(const vector<vector<double>>& table,int i,int j) const;
};