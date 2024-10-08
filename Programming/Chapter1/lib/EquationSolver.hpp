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
    
    virtual double solve(){
        checkPrecondition();
        double absoluteError=b-a;
        double valueOfA=F(a);
        int iterCount=0;
        double centre;
        double valueOfcentre;
        for(;iterCount<=maxIter;iterCount++){
            absoluteError/=2;
            centre=a+absoluteError;
            if(absoluteError<delta) break;
            valueOfcentre=F(centre);
            if(fabs(valueOfcentre)<eps) break;
            if(valueOfcentre*valueOfA>0) a=centre;
        }
        if(abs(valueOfcentre)>10e3) cout<< "The function is not continuous, the root is probably not correct. " << endl;
        return centre;
    }
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
    
    virtual double solve() {
        checkPrecondition();
        double x=x0;
        int iterCount=0;
        for(;iterCount<=maxIter;iterCount++){
            double v=F(x);
            if(fabs(v)<eps) break;
            x=x-v/F.derivative(x);
        }
        return x;
    }
};

/* Type your code here. */
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

    virtual double solve(){
        checkPrecondition();
        double nextX=x1,prevX=x0;
        double nextV=F(x1),prevV=F(x0);
        int iterCount=0;
        for(;iterCount<=maxIter;iterCount++){
            double s=(nextX-prevX)/(nextV-prevV);
            prevX=nextX;
            prevV=nextV;
            nextX=nextX-nextV*s;
            if(fabs(nextX-prevX)<delta) break;
            nextV=F(nextX);
            if(fabs(nextV)<eps) break;
        }
        return nextX;
    }
};