/**
 * @file
 * @brief Include the declaration of class `CubicBrzierCurve`
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
*/
class CubicBezierCurve:public BezierCurve{
public:
    CubicBezierCurve(const ControlPoints& list):BezierCurve(initialize(list)){}
private:
    ControlPoints initialize(const ControlPoints& list) const;
};