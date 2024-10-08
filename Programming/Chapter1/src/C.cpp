#include "./../lib/EquationSolver.hpp"
#include "./../lib/Function.hpp"
#include<cmath>
#include<iostream>

using namespace std;

class F:public Function{
    double operator()(double x) const{
        return x-tan(x);
    }
    double derivative(double x) const{
        return 1-1/(cos(x)*cos(x));
    }
};

void solve_F(double x0){
    cout << "Solving x-tan(x) near "<< x0 << endl;
    NewtonMethod FSolver(F(),x0);
    double x;
    x=FSolver.solve();
    cout<< "A root is " << x << endl;
}

int main(){
    solve_F(4.5);
    solve_F(7.7);
    return 0;
}