/**
 * @file
 * @brief declaration of class @ref BezierCurve
*/
#pragma once
#include"PolynomialCurve.hpp"
#include"DS&Constants.hpp"

/**
 * @brief generate the BezierCurve with control point with control points.
 * 
 * It will save the generated Curve in it.
*/
class BezierCurve:public PolynomialCurve{
public:

    BezierCurve(const ControlPoints& controlPoints):
    controlPoints(controlPoints),PolynomialCurve(controlPoints.l,controlPoints.r){}

    BezierCurve(const CurvePointList& curvePointList):
    BezierCurve(toControlPoints(curvePointList)){}

    /**
     * @brief Generate Bezier curve using the condition.
    */
    void generateCurve();

    /**
     * @brief Generate string that illustrate the curve and can be drawn with LaTex.
    */
    string getLatexFormatString();

protected:
    ControlPoints controlPoints;
};