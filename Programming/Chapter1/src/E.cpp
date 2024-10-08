#include"./../lib/Function.hpp"
#include"./../lib/EquationSolver.hpp"
#include<iostream>
#include<cmath>

using namespace std;

const double Pi=acos(-1.);

class F:public Function{
    const int L=10,r=1;
    const double V=12.4;
    double operator()(double h) const{
        return L*(0.5*Pi*r*r-r*r*asin(h/r)-h*sqrt(r*r-h*h))-V;
    }
    double derivative(double h) const{
        return -20*sqrt(1-h*h);
    }
};

void solveFWithBisectionMethod(double a,double b){
    cout << "Solving F with "<< "a=" << a << ", b=" << b << endl;
    BisectionMethod FSolver(F(),a,b,1e-7,0.01);
    double x=FSolver.solve();
    cout << "A root is " << x <<endl;
}

void solveFWithNewtonMethod(double x0){
    cout << "Solving F with "<< "x_0=" << x0 <<endl;
    NewtonMethod FSolver(F(),x0);
    double x=FSolver.solve();
    cout<< "A root is " << x << endl;
}

void solveFWithSecantMethod(double x0,double x1){
    cout << "Solving F with "<< "x_0=" << x0 << ", x_1=" << x1 << endl;
    SecantMethod FSolver(F(),x0,x1,1e-7,0.01);
    double x=FSolver.solve();
    cout<< "A root is " << x << endl;
}

int main(){
    solveFWithBisectionMethod(0,1);
    solveFWithNewtonMethod(0);
    solveFWithSecantMethod(0,1);
    return 0;
}