/**
 * @file
 * @brief Include declaration of class `Polynomial`.
*/
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

/**
 * @brief The subclass of `Function`, defining the polynomials and offer lots of operations.
*/
class Polynomial:public Function{
public:
    //ctors
    Polynomial(){}
    Polynomial(const vector<double>& init):coefficient(init){}

    const vector<double>& getCoefficient() const{
        return coefficient;
    }

    double operator()(double x) const override;

    /**
     * @brief It returns the derivative function of the Polynomial.
    */
    Polynomial getDerivativePoly() const;

    double derivative(double x,int order) const override;

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

    /**
     * @brief Public interface. To get the maximum in a section, 
     * which is offered by the both end of vector.
     * 
     * It calls the private function `getLocalExtremeValue`.
    */
    double getLocalMax(const vector<double>& section) const;

    /**
     * @brief Public interface. To get the minimum in a section, 
     * which is offered by the both end of vector.
     * 
     * It calls the private function `getLocalExtremeValue`.
    */
    double getLocalMin(const vector<double>& section) const;
    
    void print() const;
    
protected:
    vector<double> coefficient;

    void clearLeadingZero();

    enum class extremeType{
        MAX,MIN
    };

    /**
     * @brief Private implementation of public interface `getLocalMax` and `getLocalMin`.
    */
    double getLocalExtremeValue(const vector<double>& section,extremeType type) const;

};