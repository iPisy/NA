#include"CurveFitter.hpp"
#include<cmath>
using namespace std;

void CurveFitter::fit(knotMode mode,const CurveValueList& list,const BoundaryCondition& boundaryCondition){
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

    spline_x.generate(nullptr,FPL_x,boundaryCondition);
    spline_y.generate(&spline_x,FPL_y,boundaryCondition);
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

    //Generate points and connect them by LaTex. As LaTex is inaccurate in calculating, draw raw curve will cause huge error.
    vector<const Function*> foo{&(spline_x.piecewisePolynomial),&(spline_y.piecewisePolynomial)};
    Curve bar(foo,DefinitionDomain{0,1});
    o.addLine(bar.generateValueList(10000),"fitted curve");

    o.quickEnd();
}