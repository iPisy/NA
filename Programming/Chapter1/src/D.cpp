#include"./../lib/EquationSolver.hpp"
#include"./../lib/Function.hpp"
#include<iostream>
#include<cmath>

using namespace std;

const double Pi = acos(-1.);

class F1:public Function{
    double operator()(double x) const{
        return sin(x/2)-1;
    }
};

class F2:public Function{
    double operator()(double x) const{
        return exp(x)-tan(x);
    }
};

class F3:public Function{
    double operator()(double x) const{
        return x*x*x-12*x*x+3*x+1;
    }
};

void solve_F1(double x0,double x1){
    cout << "Solving sin(x/2)-1 with "<< "x_0=" << x0 << ", x_1=" << x1 << endl;
    SecantMethod F1Solver(F1(),x0,x1);
    double x=F1Solver.solve();
    cout << "A root is " << x <<endl;
}

void solve_F2(double x0,double x1){
    cout << "Solving e^{x}-tanx with "<< "x_0=" << x0 << ", x_1=" << x1 << endl;
    SecantMethod F2Solver(F2(),1,1.4);
    double x=F2Solver.solve();
    cout << "A root is " << x <<endl;
}

void solve_F3(double x0,double x1){
    cout << "Solving x^{3}-12*x^{2}+3x+1 with "<< "x_0=" << x0 << ", x_1=" << x1 << endl;
    SecantMethod F3Solver(F3(),0,-0.5);
    double x=F3Solver.solve();
    cout << "A root is " << x <<endl;
}

int main(){
    solve_F1(0,Pi/2);
    solve_F2(1,1.4);
    solve_F3(0,-0.5);

    solve_F1(Pi/12,Pi/13);
    cout<< "We could find that two roots of F1 are different. There are 2 close roots."<<endl;
    return 0;
}