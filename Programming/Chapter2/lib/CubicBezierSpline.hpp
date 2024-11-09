/**
 * @file
 * @brief declaration of @ref CubicBezierSpline.
 */

#pragma once
#include"BezierSpline.hpp"

/**
 * @brief A cubic Bezier Spline generator. Every curve in it use 2 control points with value and tangent vector.
 * 
 * If you indeed need to create curve in spline with four control points, use @ref BezierSpline.
 */
class CubicBezierSpline:public BezierSpline{
public:
    CubicBezierSpline():BezierSpline(2){}
    CubicBezierSpline(const CurvePointList& curvePointList):BezierSpline(curvePointList,2){}

    void generateSpline() override;
};