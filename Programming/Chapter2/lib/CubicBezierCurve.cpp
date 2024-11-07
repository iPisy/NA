/**
 * @file
 * @brief Implement the function in `CubicBezierCurve.hpp`.
*/

#include"CubicBezierCurve.hpp"
#include"Polynomial.hpp"
#include"BernsteinPolynomial.hpp"
#include"Exceptions.hpp"

using namespace std;

ControlPoints CubicBezierCurve::initialize(const ControlPoints& list) const{
    int size=list.curveValueList.size();
    if(size==2){
        ControlPoints ret;
        ret.l=list.l;
        ret.r=list.r;

        int curve_Dimension=list.curveValueList[0][0].size();
        //init 2 control points at end.
        CurveValue foo[4];
        foo[0].push_back(list.curveValueList[0][0]);
        foo[3].push_back(list.curveValueList[1][0]);

        //init 2 control points at middle.
        vector<double> bar;
        for(int i=0;i<curve_Dimension;i++){
            bar.push_back(list.curveValueList[0][0][i]+list.curveValueList[0][1][i]/3);
        }
        foo[1].push_back(bar);

        bar.clear();
        for(int i=0;i<curve_Dimension;i++){
            bar.push_back(list.curveValueList[1][0][i]+list.curveValueList[1][1][i]/3);
        }
        foo[2].push_back(bar);
        
        for(int i=0;i<3;i++){
            ret.curveValueList.push_back(foo[i]);
        }
        return ret;
    }
    
    if(size==4) return list;
    throw InvalidInputException{};
}