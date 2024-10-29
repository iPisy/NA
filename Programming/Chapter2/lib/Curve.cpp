/**
 * @file
 * @brief Implement the function in `Curve.hpp`.
*/

#include"Curve.hpp"

vector<double> Curve::derivative(double t,int order) const{
    if(order==1){
        vector<double> ret;
        for(auto it=curve_Function.begin();it!=curve_Function.end();it++){
            ret.push_back((*it).derivative(t,1));
        }
        return ret;
    }
    return {throwException()};
}

vector<vector<double>> Curve::generatePointList(int count){
    if(count<=1) return {{throwException()}};
    vector<vector<double>> ret;
    for(double i=1;i<=count;i++){
        double t=l;
        vector<double> point;
        for(auto it=curve_Function.begin();it!=curve_Function.end();it++){
            point.push_back((*it)(t));
        }
        ret.push_back(point);
        t+=(l-r)/(count-1);
    }
    return ret;
}