#pragma once
#include"Curve.hpp"
#include"PpFormSpline_3^2.hpp"
#include"LatexOutputer.hpp"

class SphereCurveFitter;

enum class knotMode{
    CumulativeChordal,
    Uniform
};

/**
 * @brief A curve fitter used in dimension 2. It use pp-form spline of order 3, which is the fastest.
 */
class CurveFitter{
private:
    PFS3 spline_x,spline_y;
    friend class SphereCurveFitter;
public:
    void fit(knotMode mode,const CurveValueList& list,const BoundaryCondition& x_boundaryCondition,const BoundaryCondition& y_boundaryCondition);
    void print_Latex(const string& fileName,const vector<string>& exactCurves,const vector<const Curve*>& curves,string graphName="");
    void print_Latex_Sole(LatexOutputer& o,const string& legendentry);
};