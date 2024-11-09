/**
 * @file
 * 
 */
#include"CubicBezierSpline.hpp"

void CubicBezierSpline::generateSpline(){
    for(auto& it:controlPointsList){
        m_BezierSpline.push_back(new CubicBezierCurve(it));
        m_BezierSpline.back()->generateCurve();
    }
}