#pragma once
#include"CurveFitter.hpp"

class SphereCurveFitter{
private:
    CurveFitter curveFitter;
public:
    void fit(knotMode mode,const CurveValueList& list);
    void print_Latex(const string& fileName,const vector<string>& exactCurves,const vector<const Curve*>& curves,string graphName="");
    void print_Latex_Sole(LatexOutputer& o,const string& legendentry);
};