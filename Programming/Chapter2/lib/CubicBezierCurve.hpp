/**
 * @file
 * @brief Declaration of class @ref CubicBezierCurve.
*/

#pragma once
#include"Function.hpp"
#include"PolynomialCurve.hpp"
#include"BezierCurve.hpp"
#include<string>

using namespace std;

/**
 * @brief A cubic Bezier curve generator.
 * 
 * cubic Bezier curve can use 2 point with it's derivative instead of 4 control points.
 * If you indeed need to initialize with four control points, use @ref BezierCurve.
*/
class CubicBezierCurve:public BezierCurve{
public:
    CubicBezierCurve(const ControlPointsList& list,int spline_Curve_Num):
    BezierCurve(initialize(list,spline_Curve_Num)){}
private:
    ControlPointsList initialize(const ControlPointsList& list,int spline_Curve_Num) const;
};