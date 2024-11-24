/**
 * @file
 * @brief Implement functions of class @ref BezierSpline.
*/

#include"BezierSpline.hpp"
#include"DS&Constants.hpp"
#include<iostream>
#include<string>
#include"LatexOutputer.hpp"

using namespace std;

CurvePointList BezierSpline::connectInitList(const vector<CurvePointList>& initList){
    CurvePointList ret;
    for(auto& it:initList){
        ret.insert(ret.end(),it.begin(),it.end());
    }
    ret.push_back(ret[0]);
    return ret;
}

ControlPointsList_List BezierSpline::devideCurvePointList(const CurvePointList& in) const{
    ControlPointsList_List ret;
    int Point_Num=in.size();
    if((Point_Num-1)%(controlPoints_Num-1)!=0) throw InvalidInputException{};
    int ControlPoints_Num=(Point_Num-1)/(controlPoints_Num-1);
    for(int i=1;i<=ControlPoints_Num;i++){
        int index=(i-1)*(controlPoints_Num-1);
        ControlPointsList foo;
        for(int j=0;j<controlPoints_Num;j++){
            foo.push_back(in[index+j].value);
        }
        ret.push_back(foo);
    }
    return ret;
}

void BezierSpline::generateSpline(){
    for(auto& it:controlPointsList_List){
        //TYPE of it==CurvePointList
        m_BezierSpline.push_back(new BezierCurve(it));
        m_BezierSpline.back()->generateCurve();
    }
}

void BezierSpline::print_Latex(const string& fileName,const vector<string>& exactCurves,const vector<const Curve*>& curves,string graphName){
    LatexOutputer outputer(fileName);

    int exactcurve_num=exactCurves.size();
    int curve_num=m_BezierSpline.size();

    if(graphName=="") graphName="Bezier Spline approximation, m="+to_string(curve_num)+".";
    outputer.quickStart(graphName);

    for(int i=0;i<exactcurve_num;i++){
        string legendentry="";
        if(i==0) legendentry="exact curve";
        outputer.addLine(exactCurves[i],legendentry,"dashed",curves[i]->getDefinitionDomain());
    }

    
    for(int i=0;i<curve_num;i++){
        string legendentry="";
        if(i==0) legendentry="Bezier spline";
        outputer.addLine(m_BezierSpline[i]->toLatexFormatString(),m_BezierSpline[i]->getDefinitionDomain(),legendentry);
    }
    
    outputer.quickEnd();
}