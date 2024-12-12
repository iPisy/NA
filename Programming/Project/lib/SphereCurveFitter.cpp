#include"SphereCurveFitter.hpp"

void SphereCurveFitter::fit(knotMode mode,const CurveValueList& list){
    CurveValueList foo;
    for(auto& it:list){
        double x=it[0][0],y=it[0][1],z=it[0][2];
        foo.push_back(CurveValue{vector<double>{x/(1-z),y/(1-z)}});
    }
    curveFitter.fit(mode,foo,BoundaryCondition_Periodic{});
}

void SphereCurveFitter::print_Latex(const string& fileName,const vector<string>& exactCurves,const vector<const Curve*>& curves,string graphName){
    LatexOutputer o(fileName,1);

    int exactCurve_num=exactCurves.size();

    o.quickStart(graphName);

    for(int i=0;i<exactCurve_num;i++){
        string legendentry="";
        if(i==0) legendentry="exact curve";
        o.addLine(exactCurves[i],legendentry,"dashed",curves[i]->getDefinitionDomain());
    }

    //Generate points and connect them by LaTex. As LaTex is inaccurate in calculating, draw raw curve will cause huge error.
    print_Latex_Sole(o,"fitted curve");

    o.quickEnd();
}

void SphereCurveFitter::print_Latex_Sole(LatexOutputer& o,const string& legendentry){
    //Generate points and connect them by LaTex. As LaTex is inaccurate in calculating, draw raw curve will cause huge error.
    vector<const Function*> foo{&(curveFitter.spline_x.piecewisePolynomial),&(curveFitter.spline_y.piecewisePolynomial)};
    Curve bar(foo,DefinitionDomain{0,1});
    CurveValueList l=bar.generateValueList(10000);
    CurveValueList out;
    for(auto& it:l){
        double x=it[0][0],y=it[0][1];
        out.push_back(CurveValue{vector<double>{2*x/(1+x*x+y*y),2*y/(1+x*x+y*y),(x*x+y*y-1)/(x*x+y*y+1)}});
    }
    o.addLine(out,legendentry);
}