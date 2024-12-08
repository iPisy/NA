/**
 * @file
 * @brief Implement function in @ref DS&Constants.hpp
 */
#include"DS&Constants.hpp"

DefinitionDomain DefinitionDomain::merge(const DefinitionDomain& lhs,const DefinitionDomain& rhs){
    const DefinitionDomain* lf=nullptr,*rf=nullptr;
    if(lhs.l>rhs.l) lf=&lhs;
    else lf=&rhs;

    if(lhs.r<rhs.r) rf=&lhs;
    else rf=&rhs;

    return DefinitionDomain(lf->l,rf->r);
}

IndependentVariableList DefinitionDomain::generateVariableList(int number) const{
    if(number<=1) throw InvalidInputException{}; 
    IndependentVariableList list;
    double start=l,end=r;
    double delta=(end-start)/(number-1);
    for(int i=1;i<=number;i++){
        list.push_back(start);
        start+=delta;
    }
    list.back()=end;
    return list;
}

ostream& operator<<(ostream& out,const DefinitionDomain& foo){
    out<<foo.l<<":"<<foo.r;
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