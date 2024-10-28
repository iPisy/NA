#pragma once

#include"Function.hpp"
#include<cmath>
#include<iostream>

using namespace std;

class EquationSolver{
protected:
    const Function& F;
    virtual void checkPrecondition()=0;
public:
    EquationSolver(const Function& F) : F(F) {}
    virtual double solve() = 0;
};

class BisectionMethod : public EquationSolver {
private:
    double a, b;
    double eps, delta;
    int maxIter;

protected:
    virtual void checkPrecondition(){
        if(F(a)*F(b)>0) cout<< "Sign of f(a) and f(b) is same, the root is probably not correct. " << endl;
    }
public:
    BisectionMethod(const Function& F, double a, double b, 
        double eps = 1e-7, double delta = 1e-6, int maxIter = 50) :
        EquationSolver(F), a(a), b(b), eps(eps), delta(delta), maxIter(maxIter) {}
    
    virtual double solve() override;
};

class NewtonMethod : public EquationSolver {
private:
    double x0;
    double eps;
    int maxIter;
protected:
    virtual void checkPrecondition(){
        ;
    }
public:
    NewtonMethod(const Function& F, double x0, 
        double eps = 1e-7, int maxIter = 8) :
        EquationSolver(F), x0(x0), maxIter(maxIter), eps(eps) {}
    
    virtual double solve() override;
};

class SecantMethod: public EquationSolver{
private:
    double x0,x1;
    double eps,delta;
    int maxIter;
protected:
    virtual void checkPrecondition(){
        ;
    }
public:
    //Default value of delta/maxIter should be tested.
    SecantMethod(const Function& F,double x0,double x1,
    double eps=1e-7,double delta=1e-6,int maxIter=50):
    EquationSolver(F),x0(x0),x1(x1),eps(eps),delta(delta),maxIter(maxIter){}

    virtual double solve() override;
};