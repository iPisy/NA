#pragma once
#include"Curve.hpp"
#include"PpFormSpline_3^2.hpp"
#include"LatexOutputer.hpp"

class SphereCurveFitter;

/**
 * @brief A curve fitter used in dimension 2. It use pp-form spline of order 3, which is the fastest.
 */
class CurveFitter{
private:
    PFS3 spline_x,spline_y;
    friend class SphereCurveFitter;
public:
    enum class knotMode{
        CumulativeChordal,
        Uniform
    };
    void fit(knotMode mode,const CurveValueList& list,const BoundaryCondition& boundaryCondition);
    void print_Latex(const string& fileName,const vector<string>& exactCurves,const vector<const Curve*>& curves,string graphName="");
};