/**
 * @file
 * @brief implementation of member functions in @ref BezierCurve
*/
#include"BezierCurve.hpp"
#include"BernsteinPolynomial.hpp"
#include"Polynomial.hpp"

void BezierCurve::generateCurve(){
    int curve_Dimension=controlPoints.curveValueList[0][0].size();
    int controlPoint_num=controlPoints.curveValueList.size();
    for(int i=0;i<curve_Dimension;i++){
        Polynomial* foo=new Polynomial(l,r);
        for(int j=0;j<controlPoint_num;j++){
            *foo+=BernsteinPolynomial(controlPoint_num-1,j)*controlPoints.curveValueList[j][0][i];
        }
        curve_Function.push_back(foo);
    }
}

string BezierCurve::getLatexFormatString(){
    string ret="\\addplot[blue,samples=100, domain=";
    ret+=to_string(get_l())+":"+to_string(get_r())+"]";

    ret+="(";
    for(auto& it:curve_Function){
        string foo="{";
        foo+=ToPolynomial(it)->getLatexFormatString();
        foo+="}";
        foo+=",";
        ret+=foo;
    }
    ret.pop_back();//pop needless ','.
    ret+=");\n";
    return ret;
}