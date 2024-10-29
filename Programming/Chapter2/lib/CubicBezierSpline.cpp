/**
 * @file
 * @brief Implement the function in `CubicBezierSpline.hpp`.
*/

#include"CubicBezierSpline.hpp"

using namespace std;

CubicBizierSpline::CubicBizierSpline(const vector<Curve&>& exactCurveList,int m):
exactCurveList(exactCurveList){
    vector<double> controlPoints;
    int n=exactCurveList.size();
    int curveCnt_ExactCurve=m/n;
    for(auto it=exactCurveList.begin();it!=exactCurveList.end();it++){
        vector<CubicBezierCurve&> foo;
        double l=(*it).get_l();
        double r=(*it).get_r();
        double add=(r-l)/curveCnt_ExactCurve;
        for(int i=1;i<=curveCnt_ExactCurve;i++){
            CubicBezierCurve* bar=new CubicBezierCurve{*it,l,l+add};
            foo.push_back(*bar);
            l+=add;
        }
        BezierCurveList.push_back(foo);
    }
}


void CubicBizierSpline::print_Latex(){
    ofstream file("Q6.tex");

    file << "\\documentclass{standalone}\n";
    file << "\\usepackage{pgfplots}\n";
    file << "\\pgfplotsset{compat=1.16}\n";
    file << "\\begin{document}\n";
    file << "\\begin{tikzpicture}\n";
    file << "\\begin{axis}[\n";
    file << "    domain=-10:10,\n";
    file << "    samples=100,\n";
    file << "    xmin=-10, xmax=10,\n";
    file << "    ymin=-10, ymax=10,\n";
    file << "    axis lines=center,\n";
    file << "    xlabel=$x$, ylabel=$y$,\n";
    file << "    title={Parametric Equations}]\n";
    for(auto it=BezierCurveList.begin();it!=BezierCurveList.end();it++){
        for(auto it_=(*it).begin();it_!=(*it).end();it_++){
            file << "\\addplot[blue, thick, domain=-10:10] (\n";
            string foo=(*it_).print_Latex_format();
            file << foo;
            file << ");\n";
        }
    }
    file << "\\end{axis}\n";
    file << "\\end{tikzpicture}\n";
    file << "\\end{document}\n";

    file.close();
}