/**
 * @file
 * @brief Declaration of class @ref Polynomial and some functions concerning vector<Polynomial>.
*/
#pragma once
#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include"Function.hpp"
#include"EquationSolver.hpp"
#include"DS&Constants.hpp"
using namespace std;

inline bool isZero(double x){
    if(abs(x)<EPSILON) return 1;
    else return 0;
}

/**
 * @brief A sort of @ref Function, defining polynomials and offers lots of operations of it.
*/
class Polynomial:public Function{
public:

    Polynomial(const DefinitionDomain& definitionDomain={}):
    Function(definitionDomain){}

    Polynomial(const vector<double>& init,const DefinitionDomain& definitionDomain={}):
    coefficient(init),Function(definitionDomain){}

    Polynomial(double x):coefficient(vector<double>{x}){}

    const vector<double>& getCoefficient() const{
        return coefficient;
    }

    void clearCoefficient(){
        coefficient.clear();
    }

    /**
     * @brief It returns the derivative function of Polynomial(this). Public method.
     * 
     * @param order the order of the derivative function.
    */
    Polynomial getDerivative(int order) const;

    void operator+=(const Polynomial& rhs);

    void operator-=(const Polynomial& rhs);

    void operator*=(const Polynomial& rhs);

    void operator/=(const Polynomial& rhs);
    /**
     * @brief apply affine transformation @b x=ax'+b on *this.
     */
    void affineTransformation(double a,double b);

    /**
     * @brief apply affine transformation on *this, making the definition domain [0,1].
     */
    void regularization();

    vector<double> getExtremePoints() const;

    /**
     * @brief To get the maximum. Public method.
     * 
     * It calls the private function @ref getLocalExtremeValue.
    */
    double getLocalMax() const;

    /**
     * @brief To get the minimum. Public method.
     * 
     * It calls the private function @ref getLocalExtremeValue.
    */
    double getLocalMin() const;
    
    /**
     * @brief Print polynomial in terminal.
     */
    void print() const;

    /**
     * @brief Generate string that illustrate the polynomial and can be drawn with LaTex.
    */
    string getLatexFormatString() const;
    
protected:
    vector<double> coefficient;

    enum class extremeType{
        MAX,MIN
    };

    /**
     * @brief Private method of public method @ref getLocalMax and @ref getLocalMin.
    */
    double getLocalExtremeValue(extremeType type) const;

private:

    double getValue(double x) const override;

    double getDerivativeValue(double x,int order) const override;
    
    /**
     * @brief It returns derivative function of the Polynomial `in`. Internal method.
     * 
     * @param in primitive function.
     * @param order the order of the derivative function.
    */
    Polynomial getDerivative(const Polynomial& in,int order) const;

    /**
     * @brief clear those coefficient=0 in high-order term after a certain operation.
    */
    void clearLeadingZero();

    /**
     * @brief Private method of public method @ref print and @ref getLatexFormatString.
    */
    string ToString() const;

    /*
    ===================================================================================
    */

    //friends
        //Arithmetical operators
    friend Polynomial operator+(const Polynomial& lhs,const Polynomial& rhs);
    friend Polynomial operator-(const Polynomial& lhs,const Polynomial& rhs);
    friend Polynomial operator*(const Polynomial& lhs,const Polynomial& rhs);
    friend Polynomial operator/(const Polynomial& lhs,const Polynomial& rhs);
};

//Arithmetical operators
Polynomial operator+(const Polynomial& lhs,const Polynomial& rhs);
Polynomial operator-(const Polynomial& lhs,const Polynomial& rhs);
Polynomial operator*(const Polynomial& lhs,const Polynomial& rhs);
    //If it's not divisible, result will have some errors.
Polynomial operator/(const Polynomial& lhs,const Polynomial& rhs);

//operators of vector<Polynomial>
vector<Polynomial> operator+(const vector<Polynomial>& lhs,const vector<Polynomial>& rhs);
void operator+=(vector<Polynomial>& lhs,const vector<Polynomial>& rhs);
vector<Polynomial> operator-(const vector<Polynomial>& lhs,const vector<Polynomial>& rhs);
void operator-=(vector<Polynomial>& lhs,const vector<Polynomial>& rhs);
vector<Polynomial> operator*(const vector<Polynomial>& polyArray,const Polynomial& rhs);
vector<Polynomial> operator*(const Polynomial& lhs,const vector<Polynomial>& polyArray);
void operator*=(vector<Polynomial>& polyArray,const Polynomial& rhs);
    //still needed, as compiler can't choose the correct implicit conversion.
vector<Polynomial> operator*(const vector<double>& doubleArray,const Polynomial& rhs);
vector<Polynomial> operator*(const Polynomial& lhs,const vector<double>& doubleArray);