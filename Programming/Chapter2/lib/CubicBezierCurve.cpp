/**
 * @file
 * @brief Implement functions of class @ref CubicBezierCurve.
*/

#include"CubicBezierCurve.hpp"
#include"Polynomial.hpp"
#include"BernsteinPolynomial.hpp"
#include"Exceptions.hpp"
#include<cmath>

using namespace std;

ControlPointsList CubicBezierCurve::initialize(const ControlPointsList& list,int spline_Curve_Num) const{
    int size=list.size();
    if(size==2){
        ControlPointsList ret;

        int curve_Dimension=list[0][0].size();
        //init 2 control points at end.
        CurveValue foo[4];
        foo[0].push_back(list[0][0]);
        foo[3].push_back(list[1][0]);

        //init 2 control points at middle.
        vector<double> bar;
        for(int i=0;i<curve_Dimension;i++){
            bar.push_back(list[0][0][i]+list[0][1][i]*(1.0/3-2.0/5.0/sqrt(sqrt(spline_Curve_Num))));
        }
        foo[1].push_back(bar);

        bar.clear();
        for(int i=0;i<curve_Dimension;i++){
            bar.push_back(list[1][0][i]-list[1][1][i]*(1.0/3-2.0/5.0/sqrt(sqrt(spline_Curve_Num))));
        }
        foo[2].push_back(bar);
        
        for(int i=0;i<4;i++){
            ret.push_back(foo[i]);
        }
        return ret;
    }

    throw InvalidInputException{};
}