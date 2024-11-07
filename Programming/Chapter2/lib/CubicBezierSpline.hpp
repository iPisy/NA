/**
 * @file
 * @brief declaration of @ref CubicBezierSpline.
 */

#pragma once
#include"BezierSpline.hpp"

class CubicBezierSpline:public BezierSpline{
public:
    CubicBezierSpline():BezierSpline(3,2){}
    CubicBezierSpline(const CurvePointList& curvePointList):BezierSpline(3,curvePointList,2){}

    void generateSpline() override;
};