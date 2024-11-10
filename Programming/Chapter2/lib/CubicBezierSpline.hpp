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
    CubicBezierSpline(const CurvePointList& curvePointList):BezierSpline(curvePointList,2),curve_Num(controlPointsList_List.size()){}
    
    void setControlPointsList_List(const CurvePointList& curvePointList) override{
        BezierSpline::setControlPointsList_List(curvePointList);
        curve_Num=controlPointsList_List.size();
    }

    void generateSpline() override;
private:
    int curve_Num;
};