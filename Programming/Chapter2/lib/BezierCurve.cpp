/**
 * @file
 * @brief implementation of member functions in @ref BezierCurve
*/
#include"BezierCurve.hpp"
#include"BernsteinPolynomial.hpp"
#include"Polynomial.hpp"

void BezierCurve::generateCurve(){
    int curve_Dimension=controlPointsList[0][0].size();
    int controlPoint_num=controlPointsList.size();
    for(int i=0;i<curve_Dimension;i++){
        Polynomial* foo=new Polynomial(l,r);
        for(int j=0;j<controlPoint_num;j++){
            *foo+=BernsteinPolynomial(controlPoint_num-1,j)*controlPointsList[j][0][i];
        }
        curve_Function.push_back(foo);
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