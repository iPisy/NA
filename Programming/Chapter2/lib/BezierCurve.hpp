/**
 * @file
 * @brief Declaration of class @ref BezierCurve.
*/
#pragma once
#include"PolynomialCurve.hpp"
#include"DS&Constants.hpp"

/**
 * @brief Bezier curve generator, using given control points. It will save the generated Curve in it.
*/
class BezierCurve:public PolynomialCurve{
public:

    BezierCurve(const ControlPointsList& controlPointsList):
    controlPointsList(controlPointsList),PolynomialCurve(DefinitionDomain{0,1}){}

    BezierCurve(const CurvePointList& curvePointList):
    BezierCurve(toControlPointsList(curvePointList)){}

    /**
     * @brief Generate Bezier curve using the given condition.
    */
    void generateCurve();

    /**
     * @brief Generate string of curve that can be drawn with LaTex. Format: ({func},{func},{func})
    */
    string toLatexFormatString();

protected:
    ControlPointsList controlPointsList;
};