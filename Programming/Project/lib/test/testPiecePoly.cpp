#include"../PiecewisePolynomial.hpp"
#include"../BFormSplineRecursionBase.hpp"

int main(){
    BFSRB B1(0,1),B2(1,2),B3(2,3);
    PiecewisePolynomial p,pp;
    p+=B1*Polynomial(vector<double>({0,1}));
    p+=B2*Polynomial(vector<double>({2,-1}));
    pp+=B2*Polynomial(vector<double>({-1,1}));
    pp+=B3*Polynomial(vector<double>({3,-1}));
    p=p*(Polynomial(vector<double>({0,1}))/2)+pp*(Polynomial(vector<double>({3,-1}))/2);
    p.print_Latex("test_graph.tex");
    return 0;
}