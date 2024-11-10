/**
 * @file
 * 
 */
#include"CubicBezierSpline.hpp"

void CubicBezierSpline::generateSpline(){
    for(auto& it:controlPointsList_List){
        m_BezierSpline.push_back(new CubicBezierCurve(it,curve_Num));
        m_BezierSpline.back()->generateCurve();
    }
}