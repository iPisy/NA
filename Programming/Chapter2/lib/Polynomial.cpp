#include"Polynomial.hpp"

void Polynomial::clearLeadingZero(){
    for(auto it=coefficient.end()-1;it>=coefficient.begin();it--){
        if(isZero(*it)) coefficient.pop_back();
        else break;
    }
}

Polynomial Polynomial::operator+(const Polynomial& rhs){        
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

Polynomial Polynomial::operator*(const Polynomial& rhs){
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

Polynomial Polynomial::operator*(double rhs){
    return (*this*Polynomial({rhs}));
}

void Polynomial::operator*=(double rhs){
    coefficient=(*this*rhs).getCoefficient();
}

void Polynomial::print(){
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
                cout<<"*x";
                if(expo==1);
                else cout<<"^"<<expo;
            }
        }
    }
    if(!printFlag) cout<<"0";
    cout<<endl;
}