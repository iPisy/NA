/**
 * @file
 * @brief Implement the function in class @ref Polynomial and some functions concerning vector<Polynomial>.
*/
#include"Polynomial.hpp"
#include<limits>
#include<iomanip>
#include<sstream>
#include<algorithm>
#include"Exceptions.hpp"

using namespace std;

void Polynomial::clearLeadingZero(){
    for(auto it=coefficient.rbegin();it!=coefficient.rend();it++){
        if(isZero(*it)) coefficient.pop_back();
        else break;
    }
}

double Polynomial::getValue(double x) const{
    if(!InDefinitionDomain(x)) throw Out_DomainException{};
    double ret=0;
    for(auto it=coefficient.rbegin();it!=coefficient.rend();it++){
        ret=ret*x+*it;
    }
    return ret;
}

Polynomial Polynomial::getDerivative(int order) const{
    return getDerivative(*this,order);
}

Polynomial Polynomial::getDerivative(const Polynomial& in,int order) const{
    if(order==0) return in;
    vector<double> deriCoefficient,coefficient(in.getCoefficient());
    int l=coefficient.size();
    for(int i=1;i<l;i++){
        deriCoefficient.push_back(i*coefficient[i]);
    }
    Polynomial deri(deriCoefficient,in.get_l(),in.get_r(),in.get_leftClosed(),in.get_rightClosed());
    return getDerivative(deri,order-1);
}

double Polynomial::derivativeValue(double x,int order) const{
    Polynomial foo=getDerivative(order);
    if(!foo.InDefinitionDomain(x)) throw Out_DomainException{};
    return foo(x);
}

Polynomial Polynomial::operator+(const Polynomial& rhs) const{        
    vector<double> retPolynomial(coefficient);
    int i;
    for(i=0;i<coefficient.size() && i<rhs.getCoefficient().size();i++){
        retPolynomial[i]+=rhs.getCoefficient()[i];
    }
    if(i<rhs.coefficient.size()){
        for(;i<rhs.coefficient.size();i++){
            retPolynomial.push_back(rhs.getCoefficient()[i]);
        }
    }
    Polynomial ret(retPolynomial,min(this->get_l(),rhs.get_l()),min(this->get_r(),rhs.get_r()),this->get_leftClosed() && rhs.get_leftClosed(),this->get_rightClosed() && rhs.get_rightClosed());
    ret.clearLeadingZero();
    return ret;
}

void Polynomial::operator+=(const Polynomial& rhs){
    Polynomial ans;
    ans=*this+rhs;
    *this=ans;
}

Polynomial Polynomial::operator-(const Polynomial& rhs) const{
    return *this+(rhs)*(-1);
}

void Polynomial::operator-=(const Polynomial& rhs){
    Polynomial ans;
    ans=*this-rhs;
    *this=ans;
}

Polynomial Polynomial::operator*(const Polynomial& rhs) const{
    vector<double> retPolynomial(coefficient.size()+rhs.getCoefficient().size()-1,0);
    for(int i=0;i<coefficient.size();i++){
        for(int j=0;j<rhs.getCoefficient().size();j++){
            retPolynomial[i+j]+=coefficient[i]*rhs.getCoefficient()[j];
        }
    }
    Polynomial ret(retPolynomial,min(this->get_l(),rhs.get_l()),min(this->get_r(),rhs.get_r()),this->get_leftClosed() && rhs.get_leftClosed(),this->get_rightClosed() && rhs.get_rightClosed());
    ret.clearLeadingZero();
    return ret;
}

void Polynomial::operator*=(const Polynomial& rhs){
    Polynomial ans;
    ans=*this*rhs;
    *this=ans;
}

Polynomial Polynomial::operator*(double rhs) const{
    return *this*Polynomial(vector<double>{rhs});
}

void Polynomial::operator*=(double rhs){
    Polynomial ans;
    ans=*this*rhs;
    *this=ans;
}

Polynomial Polynomial::operator/(const Polynomial& rhs) const{
    Polynomial lhs=*this;
    const vector<double>& rhsCoefficient=rhs.getCoefficient();
    int rhsOrder=rhsCoefficient.size()-1;
    double rhsHighestOrderCoefficient=rhsCoefficient[rhsOrder];
    vector<double> ansCoefficient;
    for(int lhsOrder=coefficient.size()-1;lhsOrder>=rhsOrder;lhsOrder--){
        double singleCoefficient=lhs.getCoefficient()[lhsOrder]/rhsHighestOrderCoefficient;
        ansCoefficient.insert(ansCoefficient.begin(),singleCoefficient);
        vector<double> foo(lhsOrder-rhsOrder+1,0);
        foo.back()=1;
        lhs-=rhs*Polynomial(foo)*singleCoefficient;
    }
    Polynomial ans(ansCoefficient,min(this->get_l(),rhs.get_l()),min(this->get_r(),rhs.get_r()),this->get_leftClosed() && rhs.get_leftClosed(),this->get_rightClosed() && rhs.get_rightClosed());
    return ans;
}

Polynomial Polynomial::operator/(double rhs) const{
    return *this/Polynomial(vector<double>{rhs});
}

void Polynomial::operator/=(const Polynomial& rhs){
    Polynomial ans;
    ans=*this/rhs;
    *this=ans;
}

void Polynomial::operator/=(double rhs){
    Polynomial ans;
    ans=*this/rhs;
    *this=ans;
}

vector<double> Polynomial::getExtremePoints() const{
    Polynomial deri=getDerivative(1);
    vector<double> ans;
    while(deri.getCoefficient().size()>=2){
        NewtonMethod ExtremePointsSolver(deri,0);        
        double root=ExtremePointsSolver.solve();
        deri/=Polynomial(vector<double>{-root,1});
        if(InDefinitionDomain(root)) ans.push_back(root);
    }
    return ans;
}

void Polynomial::print() const{
    cout<<getLatexFormatString()<<endl;
}

string Polynomial::getLatexFormatString() const{
    bool firstSignFlag=1;
    bool printFlag=0;
    string ret;
    for(auto it=coefficient.begin();it!=coefficient.end();it++){
        if(isZero(*it)) continue;
        else{
            printFlag=1;
            if(!firstSignFlag) ret+=" ";
            if(*it<0) ret+="- ";
            else{
                if(firstSignFlag);
                else{
                    ret+="+ ";
                }
            }
            if(firstSignFlag) firstSignFlag=0;
            ostringstream oss;
            oss << std::fixed << std::setprecision(15) << fabs(*it);
            ret+=oss.str();
            int expo=it-coefficient.begin();
            if(expo==0);
            else{
                ret+="*x";
                if(expo==1);
                else{
                    ret+="^";
                    ret+=to_string(expo);
                }
            }
        }
    }
    if(!printFlag) ret+="0";
    return ret;
}

double Polynomial::getLocalMax() const{
    return getLocalExtremeValue(extremeType::MAX);
}

double Polynomial::getLocalMin() const{
    return getLocalExtremeValue(extremeType::MIN);
}

double Polynomial::getLocalExtremeValue(extremeType type) const{
    vector<double> extremePoints=getExtremePoints();
    extremePoints.push_back(this->get_l());
    extremePoints.push_back(this->get_r());
    double extremeValue=numeric_limits<double>::min();
    if(type==extremeType::MIN) extremeValue=numeric_limits<double>::max();
    while(!extremePoints.empty()){
        double foo=extremePoints.back();
        extremePoints.pop_back();
        foo=(*this)(foo);
        if(type==extremeType::MAX){
            if(foo>extremeValue) extremeValue=foo;
        }
        else{
            if(foo<extremeValue) extremeValue=foo;
        }
    }
    return extremeValue;
}

vector<Polynomial> operator*(vector<Polynomial> polys,const Polynomial& rhs){
    for(auto& it:polys){
        it*=rhs;
    }
    return polys;
}

vector<Polynomial> operator*(const Polynomial& lhs,const vector<Polynomial>& polys){
    return polys*lhs;
}