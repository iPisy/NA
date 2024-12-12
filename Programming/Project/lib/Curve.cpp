/**
 * @file
 * @brief Implement functions of class @ref Curve.
*/

#include"Curve.hpp"
#include<iostream>
#include<cstdlib>

using namespace std;

vector<double> Curve::operator()(double t) const{
    vector<double> ret;
    for(auto& it:curve_Function){
        ret.push_back((*it)(t));
    }
    return ret;
}

vector<double> Curve::tangentVector(double t,int order) const{
    vector<double> ret;
    for(auto& it:curve_Function){
        ret.push_back((*it).derivativeValue(t,order));
    }
    return ret;
}

CurvePointList Curve::generatePointList(int number,int derivative_order,bool b_reverse,bool withEnd) const{
    IndependentVariableList l=definitionDomain.generateVariableList(withEnd?number:number+1,b_reverse);
    if(!withEnd) l.pop_back();
    return generatePointList(l,derivative_order);
}

CurvePointList Curve::generatePointList(const IndependentVariableList& in,int derivative_order) const{
    CurvePointList ret;
    for(auto it_=in.begin();it_!=in.end();it_++){
        auto it=*it_;
        CurvePoint foo;
        foo.t=it;
        foo.value.push_back((*this)(it));

        for(int i=1;i<=derivative_order;i++){
            foo.value.push_back(this->tangentVector(it,i));
        }
        ret.push_back(foo);
    }
    return ret;
}

CurveValueList Curve::generateValueList(int number,int derivative_order,bool b_reverse,bool withEnd) const{
    IndependentVariableList l=definitionDomain.generateVariableList(withEnd?number:number+1,b_reverse);
    if(!withEnd) l.pop_back();
    return generateValueList(l,derivative_order);
}

CurveValueList Curve::generateValueList(const IndependentVariableList& in,int derivative_order) const{
    CurvePointList foo=generatePointList(in,derivative_order);
    CurveValueList ret;
    for(auto& it:foo){
        ret.push_back(it.value);
    }
    return ret;
}

CurveValueList Curve::connectValueList(const vector<CurveValueList>& in){
    CurveValueList ret;
    for(auto& it:in){
        ret.insert(ret.end(),it.begin(),it.end());
    }
    return ret;
}