/**
 * @file
 * @brief Include the declaration of class `CubicBrzierCurve`
*/

#pragma once
#include"Function.hpp"
#include"Curve.hpp"

/**
 * @brief A cubic Bezier curve generator. The exact curve and the control points should be offered.
*/
class CubicBezierCurve{
public:

    CubicBezierCurve(const Curve& exactCurve,double t_0,double t_1):
    exactCurve(exactCurve), t_0(t_0), t_1(t_1){}

    /**
     * @brief Generate a cubic Bezier curve using the condition.
    */
    Curve generateCurve();

    /**
     * @brief Print the curve it generated into .tex file.
    */
    void print_Latex_format();
private:
    const Curve& exactCurve;
    double t_0,t_1;///< 2 control point with its derivation.
};