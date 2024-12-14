#include"PiecewisePolynomial.hpp"

int PiecewisePolynomial::findPolynomial(double x) const{
    if(x<polys[0].get_definitionDomain().l) return -1;
    if(x>polys.back().get_definitionDomain().r) return polys.size();
    if(x>=polys.back().get_definitionDomain().l) return polys.size()-1;
    int l=0,r=polys.size()-1;
    while(l<r){
        int m=(l+r)/2;
        if(x>polys[m].get_definitionDomain().l) l=m+1;
        else if(x==polys[m].get_definitionDomain().l) return m;
        else r=m;
    }
    return r-1;
}

double PiecewisePolynomial::getValue(double x) const{
    int idx=findPolynomial(x);
    if(idx<0 || idx>=polys.size()) return 0;
    return polys[idx](x);
}

double PiecewisePolynomial::getDerivativeValue(double x,int order) const{
    int idx=findPolynomial(x);
    if(idx<0 || idx>=polys.size()) return 0;
    return polys[idx].derivativeValue(x,order);
}

void PiecewisePolynomial::print_Latex_SolePoly(LatexOutputer& o,int n,const string& PP_Name) const{
    string legendentry=PP_Name;
    if(legendentry=="") legendentry="Piecewise polynomial";
    //Generate points and connect them by LaTex. As LaTex is inaccurate in calculating, draw raw curve will cause huge error.
    FunctionPointList FPL;
    for(int i=n;i<polys.size()-n;i++){
        int dnum=SAMPLES/(polys.size()-2*n);
        FunctionPointList foo=polys[i].generatePointList(dnum);
        FPL.insert(FPL.end(),foo.begin(),foo.end());
    }
    o.addLine(FPL,legendentry);
}

void PiecewisePolynomial::print_Latex(const string& filename,int n,const string& PP_Name) const{
    LatexOutputer o(filename);
    o.quickStart();
    print_Latex_SolePoly(o,n,PP_Name);
    o.quickEnd();
}

PiecewisePolynomial operator+(const PiecewisePolynomial& lhs,const PiecewisePolynomial& rhs){
    if(lhs.polys.empty()) return rhs;
    //default: Append rhs to lhs, leaving rightmost polynomial outside.
    PiecewisePolynomial ret=lhs;
    for(int l=lhs.polys.size()-rhs.polys.size()+1;l<lhs.polys.size();l++){
        ret.polys[l]+=rhs.polys[l-(lhs.polys.size()-rhs.polys.size()+1)];
    }
    ret.polys.push_back(rhs.polys.back());
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