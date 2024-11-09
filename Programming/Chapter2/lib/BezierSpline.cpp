/**
 * @file
 * @brief Implement the function in @ref BezierSpline.hpp.
*/

#include"BezierSpline.hpp"
#include"DS&Constants.hpp"
#include<iostream>
#include<string>

using namespace std;

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

void BezierSpline::print_Latex(string filename){
    ofstream file(filename);

    file << "\\documentclass{standalone}\n";
    file << "\\usepackage{pgfplots}\n";
    file << "\\pgfplotsset{compat=1.16}\n";
    file << "\\begin{document}\n";
    file << "\\begin{tikzpicture}\n";
    file << "\\begin{axis}[\n";
    file << "    axis lines=center,\n";
    file << "    xlabel=$x$, ylabel=$y$,\n";
    file << "    title={Bezier Spline approximation},\n";
    file << "    enlargelimits]\n";
    for(auto& it:m_BezierSpline){
        //TYPE of it==BezierCurve*
        file<<it->getLatexFormatString();
    }
    file << "\\end{axis}\n";
    file << "\\end{tikzpicture}\n";
    file << "\\end{document}\n";

    file.close();
}