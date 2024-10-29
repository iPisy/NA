/**
 * @file
 * @brief Include declaration of class `Curve`
*/

#pragma once
#include<vector>
#include"Function.hpp"

using namespace std;

class Curve{
public:
    virtual vector<double> operator()(double t) const;
    virtual vector<double> derivative(double t,int order) const;
    /**
     * @brief Generate uniform points within the domain of definition.
     * 
     * @param count The number of points to generate. As it include the endpoint, it should >=2.
    */
    vector<vector<double>> generatePointList(int count);

    Curve(const vector<const Function&> curve_Function,double l,double r):
    curve_Function(curve_Function), l(l), r(r){};

    int getDimension() const{
        return curve_Function.size();
    }

    double get_l() const{
        return l;
    }

    double get_r() const{
        return r;
    }

    const vector<const Function&>& getCurve_Function() const{
        return curve_Function;
    }
private:
    vector<const Function&> curve_Function;

    /**
     * @brief The 2 endpoints of the domain of definition, also known as characteristic points.
     * 
     * We assume the curve is closed temporarily.
    */
    double l,r;
};