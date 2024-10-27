#pragma once
#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

#define EPSILON (1e-14)

inline bool isZero(double x){
    if(abs(x)<EPSILON) return 1;
    else return 0;
}

class Polynomial{
public:
    //ctors
    Polynomial(){}
    Polynomial(const vector<double>& init):coefficient(init){}

    void clearLeadingZero();

    const vector<double>& getCoefficient() const{
        return coefficient;
    }

    Polynomial operator+(const Polynomial& rhs);

    void operator+=(const Polynomial& rhs);

    Polynomial operator*(const Polynomial& rhs);

    Polynomial operator*(double rhs);

    void operator*=(const Polynomial& rhs);

    void operator*=(double rhs);
    
    void print();
    
private:
    vector<double> coefficient;
};