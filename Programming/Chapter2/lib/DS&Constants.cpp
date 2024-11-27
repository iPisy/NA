/**
 * @file
 * @brief Implement function in @ref DS&Constants.hpp
 */
#include"DS&Constants.hpp"

DefinitionDomain DefinitionDomain::merge(const DefinitionDomain& lhs,const DefinitionDomain& rhs){
    const DefinitionDomain* lf=nullptr,*rf=nullptr;
    if(lhs.l>rhs.l) lf=&lhs;
    else if(lhs.l<rhs.l) lf=&rhs;
    else if(lhs.lClosed==0) lf=&lhs;
    else lf=&rhs;

    if(lhs.r<rhs.r) rf=&lhs;
    else if(lhs.r>rhs.r) rf=&rhs;
    else if(lhs.rClosed==0) rf=&lhs;
    else rf=&rhs;

    return DefinitionDomain(lf->l,rf->r,lf->lClosed,rf->rClosed);
}

ostream& operator<<(ostream& out,const DefinitionDomain& foo){
    out<<foo.get_l()<<":"<<foo.get_r();
    return out;
}

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