#pragma once
#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include"Function.hpp"
#include"EquationSolver.hpp"
using namespace std;

#define EPSILON (1e-14)

inline bool isZero(double x){
    if(abs(x)<EPSILON) return 1;
    else return 0;
}

class Polynomial:public Function{
public:
    //ctors
    Polynomial(){}
    Polynomial(const vector<double>& init):coefficient(init){}

    void clearLeadingZero();

    const vector<double>& getCoefficient() const{
        return coefficient;
    }

    double operator()(double x) const override;

    Polynomial getDerivativePoly() const;

    double derivative(double x) const override;

    Polynomial operator+(const Polynomial& rhs) const;

    void operator+=(const Polynomial& rhs);

    Polynomial operator-(const Polynomial& rhs) const;

    void operator-=(const Polynomial& rhs);

    Polynomial operator*(const Polynomial& rhs) const;

    Polynomial operator*(double rhs) const;

    void operator*=(const Polynomial& rhs);

    void operator*=(double rhs);

    //If it's not divisible, result will have some errors.
    Polynomial operator/(const Polynomial& rhs) const;

    Polynomial operator/(double rhs) const;

    void operator/=(const Polynomial& rhs);

    void operator/=(double rhs);

    vector<double> getExtremePoints() const;

    //"local" means a section, which is offered by the both end of vector.
    double getLocalMax(const vector<double>& section) const;

    //Explaination of "local" is same as "double getLocalMax()".
    double getLocalMin(const vector<double>& section) const;
    
    void print() const;
    
private:
    vector<double> coefficient;

    enum class extremeType{
        MAX,MIN
    };

    //Explaination of "local" is same as "double getLocalMax()".
    double getLocalExtremeValue(const vector<double>& section,extremeType type) const;
};