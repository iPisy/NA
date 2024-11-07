#include "../EquationSolver.hpp"
#include "../Function.hpp"
#include <iostream>
#include <cmath>

using namespace std;

const double Pi = acos(-1.);

class F1 : public Function {
    double getValue(double x) const override{
        return 1/x-tan(x);
    }
};

void solve_F1() {
    cout << "Solving x^{-1} - \\tan x on [0, \\pi/2]" << endl;
    BisectionMethod solver_f1(F1(), 0, Pi/2);
    double x = solver_f1.solve();
    cout << "A root is: " << x << endl;
}
/* Type your code here */

int main() {
    solve_F1();
    return 0;
}