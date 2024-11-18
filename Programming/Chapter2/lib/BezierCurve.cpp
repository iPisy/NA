/**
 * @file
 * @brief Implement functions of class @ref BezierCurve.
*/
#include"BezierCurve.hpp"
#include"BernsteinPolynomial.hpp"
#include"Polynomial.hpp"

void BezierCurve::generateCurve(){
    int curve_Dimension=controlPointsList[0][0].size();
    int controlPoint_num=controlPointsList.size();
    vector<Polynomial> foo(curve_Dimension,Polynomial(definitionDomain));
    for(int i=0;i<controlPoint_num;i++){
        foo+=controlPointsList[i][0]*BernsteinPolynomial(controlPoint_num-1,i);
    }
    for(auto& it:foo){
        curve_Function.push_back(new Polynomial(it));
    }
}

string BezierCurve::getLatexFormatString(){
    string ret="(";
    for(auto& it:curve_Function){
        ret+=ToPolynomial(it)->getLatexFormatString()+",";
    }
    ret.pop_back();//pop needless ','.
    ret+=")";
    return ret;
}