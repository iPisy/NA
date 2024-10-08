#include "./lib/EquationSolver.hpp"
#include "./lib/Function.hpp"
#include <iostream>
#include <cmath>

using namespace std;

const double Pi = acos(-1.);

class F1 : public Function {
public:
    double operator() (double x) const {
        return 1/x-tan(x);
    }
};

class F2: public Function{
public:
    double operator()(double x) const{
        return 1/x-exp2(x);
    }
};

class F3: public Function{
public:
    double operator()(double x) const{
        return 1/exp2(x)+exp(x)+2*cos(x)-6;
    }
};

class F4: public Function{
public:
    double operator()(double x) const{
        return (x*x*x+4*x*x+3*x+5)/(2*x*x*x-9*x*x+18*x-2);
    }
};

void solve_F1() {
    std::cout << "Solving x^{-1} - \\tan x on [0, \\pi/2]" << std::endl;
    BisectionMethod solver_f1(F1(), 0, Pi/2);
    double x = solver_f1.solve();
    std::cout << "A root is: " << x << std::endl;
}

void solve_F2(){
    cout << "Solving x^{-1}-2^{x} on [0,1]" << endl;
    BisectionMethod solver_f2(F2(),0,1);
    double x= solver_f2.solve();
    std::cout << "A root is: " << x << std::endl;
}

void solve_F3(){
    cout << "Solving 2^{-x}+e^{x}+2cosx-6 on [1,3]" << endl;
    BisectionMethod solver_f3(F3(),1,3);
    double x= solver_f3.solve();
    std::cout << "A root is: " << x << std::endl;
}

void solve_F4(){
    cout << "Solving (x^{3}+4*x^{2}+3x+5)/(2*x^{3}-9x^{2}+18x-2) on [0,4]" << endl;
    BisectionMethod solver_f4(F4(),0,4);
    double x= solver_f4.solve();
    std::cout << "A root is: " << x << std::endl;
}

/* Type your code here */

int main() {
    solve_F1();
    solve_F2();
    solve_F3();
    solve_F4();
    return 0;
}