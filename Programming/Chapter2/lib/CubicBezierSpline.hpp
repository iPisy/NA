/**
 * @file
 * @brief Include the declaration of class `CubicBrzierSpline`
*/
#pragma once
#include"CubicBezierCurve.hpp"
#include<fstream>

using namespace std;

class CubicBizierSpline{
public:
    /**
     * @param m the number of the control points.
    */
    CubicBizierSpline(const vector<Curve*>& exactCurveList,int m);

    void print_Latex(string filename);

private:
    vector<Curve*> exactCurveList;
    vector<vector<CubicBezierCurve*>> BezierCurveList;
};