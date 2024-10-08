#include"./../lib/Function.hpp"
#include"./../lib/EquationSolver.hpp"
#include<iostream>
#include<cmath>

using namespace std;

const double Pi=acos(-1.);

class F:public Function{
private:
    double A,B,C,D,E,l,beta_1,h;
public:
    F(double D,double l,double beta_1,double h):
    D(D),l(l),beta_1(beta_1),h(h){
        beta_1=beta_1/180*Pi;
        A=l*sin(beta_1);
        B=l*cos(beta_1);
        C=(h+0.5*D)*sin(beta_1)-0.5*D*tan(beta_1);
        E=(h+0.5*D)*cos(beta_1)-0.5*D;
    }
    double operator()(double a) const{
        a=a/180*Pi;
        return A*sin(a)*cos(a)+B*sin(a)*sin(a)-C*cos(a)-E*sin(a);
    }
};

void solveFWithNewtonMethod(double x0,double D,double l,double beta_1,double h){
    cout << "Solving F with "<< "x_0=" << x0 <<endl;
    NewtonMethod FSolver(F(D,l,beta_1,h),x0);
    double x=FSolver.solve();
    cout<< "A root is " << x << endl;
}

void solveFWithSecantMethod(double x0,double x1,double D,double l,double beta_1,double h){
    cout << "Solving F with "<< "x_0=" << x0 << ", x_1=" << x1 << endl;
    SecantMethod FSolver(F(D,l,beta_1,h),x0,x1);
    double x=FSolver.solve();
    cout<< "A root is " << x << endl;
}

int main(){
    solveFWithNewtonMethod(33,55,89,11.5,49);
    solveFWithNewtonMethod(33,30,89,11.5,49);
    solveFWithSecantMethod(33,100000,55,89,11.5,49);
    return 0;
}
