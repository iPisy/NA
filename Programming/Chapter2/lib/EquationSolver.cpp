/**
 * @file
 * @brief Implement functions of class @ref BisectionMethod, class @ref NewtonMethod, class @ref SecantMethod.
*/
#include"EquationSolver.hpp"

double BisectionMethod::solve(){
    checkPrecondition();
    double absoluteError=b-a;
    double valueOfA=F(a);
    int iterCount=0;
    double centre=(a+b)/2;
    double valueOfcentre=F(centre);
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

double NewtonMethod::solve(){
    checkPrecondition();
    double x=x0;
    int iterCount=0;
    for(;iterCount<=maxIter;iterCount++){
        double v=F(x);
        if(fabs(v)<eps) break;
        x=x-v/F.derivativeValue(x,1);
    }
    return x;
}

double SecantMethod::solve(){
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