#include"PiecewisePolynomial.hpp"

PiecewisePolynomial::PiecewisePolynomial(const vector<Polynomial>& init):PiecewisePolynomial(){
    polys=init;
    set_definitionDomain(DefinitionDomain{init[0].get_definitionDomain().l,init.back().get_definitionDomain().r});
}

int PiecewisePolynomial::findPolynomial(double x) const{
    if(x<definitionDomain.l) return -1;
    if(x>definitionDomain.r) return polys.size();
    if(x>=polys.back().get_definitionDomain().l) return polys.size()-1;
    int l=0,r=polys.size()-1;
    while(l<r){
        int m=(l+r)/2;
        if(x<polys[m].get_definitionDomain().l) l=m+1;
        else if(x==polys[m].get_definitionDomain().l) return m;
        else r=m;
    }
    return r-1;
}

double PiecewisePolynomial::getValue(double x) const{
    int idx=findPolynomial(x);
    if(x<0 || x>=polys.size()) return 0;
    return polys[idx](x);
}

double PiecewisePolynomial::getDerivativeValue(double x,int order) const{
    int idx=findPolynomial(x);
    if(x<0 || x>=polys.size()) return 0;
    return polys[idx].derivativeValue(x,order);
}

PiecewisePolynomial operator+(const PiecewisePolynomial& lhs,const PiecewisePolynomial& rhs){
    if(lhs.polys.empty()) return rhs;
    //default: 2 pp in the same order.
    PiecewisePolynomial ret=lhs;
    for(int l=1;l<ret.polys.size();l++){
        ret.polys[l]+=rhs.polys[l-1];
    }
    ret.polys.push_back(rhs.polys.back());
    ret.set_definitionDomain(DefinitionDomain{ret.get_definitionDomain().l,ret.polys.back().get_definitionDomain().r});
    return ret;
}

void operator+=(PiecewisePolynomial& lhs,const PiecewisePolynomial& rhs){
    lhs=lhs+rhs;
}

PiecewisePolynomial operator*(const PiecewisePolynomial& lhs,const Polynomial& rhs){
    PiecewisePolynomial ret=lhs;
    ret.polys*=rhs;
    return ret;
}