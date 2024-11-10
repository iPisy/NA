/**
 * @file
 * @brief Implement function in @ref DS&Constants.hpp
 */
#include"DS&Constants.hpp"

ControlPoint toControlPoint(const CurvePoint& in){
    return in.value;
}

ControlPointsList toControlPointsList(const CurvePointList& in){
    ControlPointsList ret;
    for(auto& it:in){
        ret.push_back(toControlPoint(it));
    }
    return ret;
}