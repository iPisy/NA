/**
 * @file
 * @brief Implement functions of class @ref Polynomial and some functions concerning vector<Polynomial>.
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

/**
 * @details using Qin Jiushao Algorithm.
 */
double Polynomial::getValue(double x) const{
    double ret=0;
    for(auto it=coefficient.rbegin();it!=coefficient.rend();it++){
        ret=ret*x+*it;
    }
    return ret;
}

Polynomial Polynomial::getDerivative(int order) const{
    return getDerivative(*this,order);
}

/**
 * @details implement by using recursion.
 */
Polynomial Polynomial::getDerivative(const Polynomial& in,int order) const{
    if(order==0) return in;
    Polynomial deri(in.get_l(),in.get_r(),in.get_leftClosed(),in.get_rightClosed());
    int l=coefficient.size();
    for(int i=1;i<l;i++){
        deri.coefficient.push_back(i*in.coefficient[i]);
    }
    return getDerivative(deri,order-1);
}

double Polynomial::getDerivativeValue(double x,int order) const{
    return getDerivative(order)(x);
}

Polynomial Polynomial::operator+(const Polynomial& rhs) const{
    Polynomial ret(coefficient,min(this->get_l(),rhs.get_l()),min(this->get_r(),rhs.get_r()),this->get_leftClosed() && rhs.get_leftClosed(),this->get_rightClosed() && rhs.get_rightClosed());
    int i;
    for(i=0;i<coefficient.size() && i<rhs.coefficient.size();i++){
        ret.coefficient[i]+=rhs.coefficient[i];
    }
    if(i<rhs.coefficient.size()){
        for(;i<rhs.coefficient.size();i++){
            ret.coefficient.push_back(rhs.coefficient[i]);
        }
    }
    ret.clearLeadingZero();
    return ret;
}

void Polynomial::operator+=(const Polynomial& rhs){
    *this=*this+rhs;
}

Polynomial Polynomial::operator-(const Polynomial& rhs) const{
    return *this+(rhs)*(-1);
}

void Polynomial::operator-=(const Polynomial& rhs){
    *this=*this-rhs;
}

Polynomial Polynomial::operator*(const Polynomial& rhs) const{
    Polynomial ret(min(this->get_l(),rhs.get_l()),min(this->get_r(),rhs.get_r()),this->get_leftClosed() && rhs.get_leftClosed(),this->get_rightClosed() && rhs.get_rightClosed());
    ret.coefficient.assign(coefficient.size()+rhs.coefficient.size()-1,0);
    for(int i=0;i<coefficient.size();i++){
        for(int j=0;j<rhs.coefficient.size();j++){
            ret.coefficient[i+j]+=coefficient[i]*rhs.coefficient[j];
        }
    }
    ret.clearLeadingZero();
    return ret;
}

void Polynomial::operator*=(const Polynomial& rhs){
    *this=*this*rhs;
}

Polynomial Polynomial::operator*(double rhs) const{
    return *this*Polynomial(vector<double>{rhs});
}

void Polynomial::operator*=(double rhs){
    *this=*this*rhs;
}

Polynomial Polynomial::operator/(const Polynomial& rhs) const{
    Polynomial lhs=*this;
    int rhsOrder=rhs.coefficient.size()-1;
    double rhsHighestOrderCoefficient=rhs.coefficient[rhsOrder];
    Polynomial ans(min(this->get_l(),rhs.get_l()),min(this->get_r(),rhs.get_r()),this->get_leftClosed() && rhs.get_leftClosed(),this->get_rightClosed() && rhs.get_rightClosed());
    for(int lhsOrder=coefficient.size()-1;lhsOrder>=rhsOrder;lhsOrder--){
        double singleCoefficient=lhs.coefficient[lhsOrder]/rhsHighestOrderCoefficient;
        ans.coefficient.insert(ans.coefficient.begin(),singleCoefficient);
        vector<double> foo(lhsOrder-rhsOrder+1,0);
        foo.back()=1;
        lhs-=rhs*Polynomial(foo)*singleCoefficient;
    }
    return ans;
}

Polynomial Polynomial::operator/(double rhs) const{
    return *this/Polynomial(vector<double>{rhs});
}

void Polynomial::operator/=(const Polynomial& rhs){
    *this=*this/rhs;
}

void Polynomial::operator/=(double rhs){
    *this=*this/rhs;
}

void Polynomial::affineTransformation(double a,double b){
    Polynomial ans=*this;
    ans.clearCoefficient();
    Polynomial foo(vector<double>{1});
    for(int i=0;i<coefficient.size();i++){
        ans+=foo*coefficient[i];
        foo*=Polynomial(vector<double>{b,a});
    }
    *this=ans;
}

void Polynomial::regularization(){
    affineTransformation(definitionDomain.r-definitionDomain.l,definitionDomain.l);
}

IndependentVariableList Polynomial::getExtremePoints() const{
    Polynomial deri=getDerivative(1);
    vector<double> ans;
    while(deri.coefficient.size()>=2){
        NewtonMethod ExtremePointsSolver(deri,0);        
        double root=ExtremePointsSolver.solve();
        deri/=Polynomial(vector<double>{-root,1});
        if(definitionDomain.InDefinitionDomain(root)) ans.push_back(root);
    }
    return ans;
}

void Polynomial::print() const{
    cout<<ToString()<<endl;
}

string Polynomial::getLatexFormatString() const{
    return "{"+ToString()+"}";
}

string Polynomial::ToString() const{
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
    IndependentVariableList extremePoints=getExtremePoints();
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

Polynomial operator+(double lhs,const Polynomial& rhs){
    return rhs+lhs;
}

Polynomial operator-(double lhs,const Polynomial& rhs){
    return Polynomial(vector<double>{lhs})-rhs;
}

Polynomial operator*(double lhs,const Polynomial& rhs){
    return rhs*lhs;
}

vector<Polynomial> operator+(const vector<Polynomial>& lhs,const vector<Polynomial>& rhs){
    if(lhs.size()!=rhs.size()) throw VectorSizeMismatchException{};
    vector<Polynomial> ret;
    for(int i=0;i<lhs.size();i++){
        ret.push_back(lhs[i]+rhs[i]);
    }
    return ret;
}

void operator+=(vector<Polynomial>& lhs,const vector<Polynomial>& rhs){
    lhs=lhs+rhs;
}

vector<Polynomial> operator-(const vector<Polynomial>& lhs,const vector<Polynomial>& rhs){
    return lhs+(-1)*rhs;
}

vector<Polynomial> operator-=(vector<Polynomial>& lhs,const vector<Polynomial>& rhs){
    lhs=lhs-rhs;
}

vector<Polynomial> operator*(const vector<Polynomial>& polyArray,const Polynomial& rhs){
    vector<Polynomial> ret;
    for(auto& it:polyArray){
        ret.push_back(it*rhs);
    }
    return ret;
}

vector<Polynomial> operator*=(vector<Polynomial>& polyArray,const Polynomial& rhs){
    polyArray=polyArray*rhs;
}

vector<Polynomial> operator*(const Polynomial& lhs,const vector<Polynomial>& polyArray){
    return polyArray*lhs;
}

vector<Polynomial> operator*(const vector<double>& doubleArray,const Polynomial& rhs){
    vector<Polynomial> ret;
    for(auto& it:doubleArray){
        ret.push_back(it*rhs);
    }
    return ret;
}

vector<Polynomial> operator*(const Polynomial& lhs,const vector<double>& doubleArray){
    return doubleArray*lhs;
}

vector<Polynomial> operator*(double lhs,const vector<Polynomial>& polyArray){
    vector<Polynomial> ret;
    for(auto& it:polyArray){
        ret.push_back(lhs*it);
    }
    return ret;
}

vector<Polynomial> operator*(const vector<Polynomial>& polyArray,double rhs){
    return rhs*polyArray;
}