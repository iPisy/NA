/**
 * @file
 * @brief implement function in @ref DS&Constants.hpp
 */
#include"DS&Constants.hpp"

ControlPoints toControlPoints(const CurvePointList& in){
    ControlPoints ret;
    for(auto& it:in){
        ret.curveValueList.push_back(it.value);
    }
    ret.l=in[0].t;
    ret.r=in.back().t;
    return ret;
}