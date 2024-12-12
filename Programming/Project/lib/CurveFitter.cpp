#include"CurveFitter.hpp"
#include<cmath>
using namespace std;

void CurveFitter::fit(knotMode mode,const CurveValueList& list){
    int knotsNum=list.size();

    //mode determine the way of generating VariableList.
    IndependentVariableList tlist;
    if(mode==knotMode::Uniform){
        for(int i=0;i<knotsNum;i++) tlist.push_back(i);
    }
    else{
        tlist.push_back(0);
        for(int i=1;i<knotsNum;i++){
            tlist.push_back(
                (tlist.back())
                +sqrt(
                (list[i][0][0]-list[i-1][0][0])*(list[i][0][0]-list[i-1][0][0])
                +
                (list[i][0][1]-list[i-1][0][1])*(list[i][0][1]-list[i-1][0][1])
                )
            );
        }
    }
    //normalization
    for(auto& it:tlist) it/=tlist.back();

    FunctionPointList FPL_x,FPL_y;
    for(int i=0;i<knotsNum;i++){
        FPL_x.push_back(FunctionPoint{tlist[i],{list[i][0][0]}});
        FPL_y.push_back(FunctionPoint{tlist[i],{list[i][0][1]}});
    }

    spline_x.generate(nullptr,FPL_x,BoundaryCondition_Periodic{});
    spline_y.generate(&spline_x,FPL_y,BoundaryCondition_Periodic{});
}
    
void CurveFitter::print_Latex(const string& fileName,const vector<string>& exactCurves,const vector<const Curve*>& curves,string graphName){
    LatexOutputer o(fileName);

    int exactCurve_num=exactCurves.size();

    o.quickStart(graphName);

    for(int i=0;i<exactCurve_num;i++){
        string legendentry="";
        if(i==0) legendentry="exact curve";
        o.addLine(exactCurves[i],legendentry,"dashed",curves[i]->getDefinitionDomain());
    }

    int curve_num=spline_x.piecewisePolynomial.polys.size();
    for(int i=0;i<curve_num;i++){
        string legendentry="";
        if(i==0) legendentry="fitted curve";
        o.addLine("("+spline_x.piecewisePolynomial.polys[i].getLatexFormatString()+","
        +spline_y.piecewisePolynomial.polys[i].getLatexFormatString()+")",
        spline_x.piecewisePolynomial.polys[i].get_definitionDomain(),
        legendentry);
    }

    o.quickEnd();
}