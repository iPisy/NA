#include"Polynomial.hpp"
#include<limits>

using namespace std;

void Polynomial::clearLeadingZero(){
    for(auto it=coefficient.rbegin();it!=coefficient.rend();it++){
        if(isZero(*it)) coefficient.pop_back();
        else break;
    }
}

double Polynomial::operator()(double x) const{
    double ret=0;
    for(auto it=coefficient.rbegin();it!=coefficient.rend();it++){
        ret=ret*x+*it;
    }
    return ret;
}

Polynomial Polynomial::getDerivativePoly() const{    
    vector<double> deriCoefficient;
    for(auto it=coefficient.begin();it!=coefficient.end();it++){
        if(it==coefficient.begin()) continue;
        deriCoefficient.push_back((it-coefficient.begin())* *it);
    }
    Polynomial deri(deriCoefficient);
    return deri;
}

double Polynomial::derivative(double x,int order) const{
    if(order==1) return getDerivativePoly()(x);
    else return throwException();
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
    Polynomial ret(retPolynomial);
    ret.clearLeadingZero();
    return ret;
}

void Polynomial::operator+=(const Polynomial& rhs){
    coefficient=(*this+rhs).getCoefficient();
}

Polynomial Polynomial::operator-(const Polynomial& rhs) const{
    Polynomial ans=*this+(rhs)*(-1);
    ans.clearLeadingZero();
    return ans;
}

void Polynomial::operator-=(const Polynomial& rhs){
    coefficient=(*this-rhs).getCoefficient();
}

Polynomial Polynomial::operator*(const Polynomial& rhs) const{
    vector<double> retPolynomial(coefficient.size()+rhs.getCoefficient().size()-1,0);
    for(int i=0;i<coefficient.size();i++){
        for(int j=0;j<rhs.getCoefficient().size();j++){
            retPolynomial[i+j]+=coefficient[i]*rhs.getCoefficient()[j];
        }
    }
    Polynomial ret(retPolynomial);
    ret.clearLeadingZero();
    return ret;
}

void Polynomial::operator*=(const Polynomial& rhs){
    coefficient=(*this*rhs).getCoefficient();   
}

Polynomial Polynomial::operator*(double rhs) const{
    return *this*Polynomial({rhs});
}

void Polynomial::operator*=(double rhs){
    coefficient=(*this*rhs).getCoefficient();
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
    Polynomial ans(ansCoefficient);
    return ans;
}

Polynomial Polynomial::operator/(double rhs) const{
    return *this/Polynomial({rhs});
}

void Polynomial::operator/=(const Polynomial& rhs){
    coefficient=(*this/rhs).getCoefficient();
}

void Polynomial::operator/=(double rhs){
    coefficient=(*this/Polynomial({rhs})).getCoefficient();
}

vector<double> Polynomial::getExtremePoints() const{
    Polynomial deri=getDerivativePoly();
    vector<double> ans;
    while(deri.getCoefficient().size()>=2){   
        NewtonMethod ExtremePointsSolver(deri,0);        
        double root=ExtremePointsSolver.solve();
        deri/=Polynomial({-root,1});
        ans.push_back(root);
    }
    return ans;
}

void Polynomial::print() const{
    bool firstSignFlag=1;
    bool printFlag=0;
    for(auto it=coefficient.begin();it!=coefficient.end();it++){
        if(isZero(*it)) continue;
        else{
            printFlag=1;
            if(!firstSignFlag) cout<<" ";
            if(*it<0) cout<<"- ";
            else{
                if(firstSignFlag);
                else{
                    cout<<"+ ";
                }
            }
            if(firstSignFlag) firstSignFlag=0;
            cout<< fabs(*it);
            int expo=it-coefficient.begin();
            if(expo==0);
            else{
                cout<<"x";
                if(expo==1);
                else cout<<"^"<<expo;
            }
        }
    }
    if(!printFlag) cout<<"0";
    cout<<endl;
}

double Polynomial::getLocalMax(const vector<double>& section) const{
    return getLocalExtremeValue(section,extremeType::MAX);
}

double Polynomial::getLocalMin(const vector<double>& section) const{
    return getLocalExtremeValue(section,extremeType::MIN);
}

double Polynomial::getLocalExtremeValue(const vector<double>& section,extremeType type) const{
    double left=section.front(),right=section.back();
    vector<double> extremePoints=getExtremePoints();
    extremePoints.push_back(left);
    extremePoints.push_back(right);
    // for(auto it=extremePoints.begin();it!=extremePoints.end();it++) cout<<*it<<endl;
    double extremeValue=numeric_limits<double>::min();
    if(type==extremeType::MIN) extremeValue=numeric_limits<double>::max();
    while(!extremePoints.empty()){
        double foo=extremePoints.back();
        extremePoints.pop_back();
        if(foo<left || foo>right) continue;
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