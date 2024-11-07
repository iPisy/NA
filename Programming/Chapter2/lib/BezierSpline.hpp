/**
 * @file
 * @brief Include the declaration of class @ref BrzierSpline.
*/
#pragma once
#include"CubicBezierCurve.hpp"
#include"Exceptions.hpp"
#include<fstream>

using namespace std;

/**
 * @brief a BezierSpline generator, given the control points list.
 * 
 * the number and order of BezierCurve can be arbitrarily assigned by assigning member variables.
*/
class BezierSpline{
public:
    BezierSpline(int order):BezierSpline(order,order+1){}

    BezierSpline(int order,int size):order(order),size(size){
        if(order<=0) throw InvalidInputException{};
    }

    BezierSpline(int order,const CurvePointList& curvePointList):BezierSpline(order,curvePointList,order+1){}

    BezierSpline(int order,const CurvePointList& curvePointList,int size):
    order(order),size(size),controlPointsList(devideCurvePointList(curvePointList)){
        if(order<=0) throw InvalidInputException{};
    }

    void setControlPoint(const CurvePointList& curvePointList){
        controlPointsList=devideCurvePointList(curvePointList);
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
    void print_Latex(string filename);

protected:
    /**
     * @brief the order of the BezierCurve, i.e. (the number of control points - 1 ) in every BezierCurve.
    */
    int order;

    ControlPointsList controlPointsList;

    int size;///< the number of control points in every BezierCurve.

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
    ControlPointsList devideCurvePointList(const CurvePointList& in);
};