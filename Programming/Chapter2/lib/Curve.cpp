/**
 * @file
 * @brief Implement the function in @ref Curve.hpp.
*/

#include"Curve.hpp"
#include<iostream>
#include<cstdlib>
#include<algorithm>

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

CurvePointList Curve::generatePointList(int number,int derivative_order,bool direction) const{
    if(number<=1) throw InvalidInputException{}; 
    IndependentVariableList list;
    int start=get_l(),end=get_r();
    double delta=(end-start)/(number-1);
    if(direction){
        swap(start,end);
        delta=-delta;
    }
    for(int i=1;i<=number;i++){
        list.push_back(start);
        start+=delta;
    }
    list.back()=end;
    return generatePointList(list,derivative_order,direction);
}

CurvePointList Curve::generatePointList(const IndependentVariableList& in,int derivative_order) const{
    CurvePointList ret;
    for(auto& it:in){
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