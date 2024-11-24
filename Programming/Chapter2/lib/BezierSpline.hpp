/**
 * @file
 * @brief Declaration of class @ref BrzierSpline.
*/
#pragma once
#include"CubicBezierCurve.hpp"
#include"Exceptions.hpp"
#include<fstream>

using namespace std;

/**
 * @brief Bezier spline generator, given list of points on curve.
 * 
 * the number and order of BezierCurve are all arbitrary.
*/
class BezierSpline{
public:

    BezierSpline(int controlPoints_Num):controlPoints_Num(controlPoints_Num){
        if(controlPoints_Num<=1) throw InvalidInputException{};
    }

    BezierSpline(const CurvePointList& curvePointList,int controlPoints_Num):
    controlPoints_Num(controlPoints_Num),controlPointsList_List(devideCurvePointList(curvePointList)){
        if(controlPoints_Num<=1) throw InvalidInputException{};
    }

    static CurvePointList connectInitList(const vector<CurvePointList>& initList);

    virtual void setControlPointsList_List(const CurvePointList& curvePointList){
        controlPointsList_List=devideCurvePointList(curvePointList);
    }

    /**
     * @brief generate BezierSpline with given control points.
     * 
     * It is overridden in @ref CubicBezierSpline, as @a BezierCurve* in @ref m_BezierSpline 
     * is @a CubicBezierCurve*, so m_BezierSpline is assigned in different way.
    */
    virtual void generateSpline();

    /**
     * @brief generate a .tex file, which can draw the BezierSpline.
     * 
     * LaTeX only supports the plotting of parametric equations with dimensions == 2 or 3. 
     * The case for dimension == 3 is yet to be implemented.
    */
    void print_Latex(const string& fileName,const vector<string>& exactCurves,const vector<const Curve*>& curves,string graphName="");

protected:

    ControlPointsList_List controlPointsList_List;

    int controlPoints_Num;///< the number of control points in every BezierCurve.

    /**
     * @brief Bezier Spline, consisting of Bezier Curves. `m` in name just refers to `member`.
    */
    vector<BezierCurve*> m_BezierSpline;

private:
    /**
     * @brief devide the input, @a CurvePointList into @a several @a sub-ControlPoints, which constitute @a ControlPointsList.
     * 
     * @param in the CurvePointList to divide.
     * @throws InvalidInputException If the input @a CurvePointList can't be divided evenly.
    */
    ControlPointsList_List devideCurvePointList(const CurvePointList& in) const;
};