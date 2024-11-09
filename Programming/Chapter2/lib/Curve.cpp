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

vector<double> Curve::tangentVector(double t,int order,Direction direction) const{
    vector<double> ret;
    for(auto& it:curve_Function){
        ret.push_back((*it).derivativeValue(t,order,direction));
    }
    return ret;
}

CurvePointList Curve::generatePointList(int number,int derivative_order,bool direction) const{
    if(number<=1) throw InvalidInputException{}; 
    IndependentVariableList list;
    double start=get_l(),end=get_r();
    double delta=(end-start)/number;
    start+=delta/2;//avoid extreme huge derivative.
    end-=delta/2;//avoid extreme huge derivative.
    for(int i=1;i<=number;i++){
        list.push_back(start);
        start+=delta;
    }
    list.back()=end;
    return generatePointList(list,derivative_order,direction);
}

CurvePointList Curve::generatePointList(const IndependentVariableList& in,int derivative_order,bool direction) const{
    CurvePointList ret;
    for(auto it_=in.begin();it_!=in.end();it_++){
        auto it=*it_;
        CurvePoint foo;
        foo.t=it;
        foo.value.push_back((*this)(it));

        Direction direction=Direction::DEFAULT;
        if(it_==in.begin()) direction=Direction::right;
        if(next(it_)==in.end()) direction=Direction::left;
        for(int i=1;i<=derivative_order;i++){
            foo.value.push_back(this->tangentVector(it,i,direction));
        }
        ret.push_back(foo);
    }
    if(direction) reverse(ret.begin(),ret.end());
    return ret;
}