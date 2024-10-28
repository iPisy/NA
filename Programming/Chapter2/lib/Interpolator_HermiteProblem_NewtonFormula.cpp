#include"Interpolator_HermiteProblem_NewtonFormula.hpp"

double factorial(int x){
    double ret=1;
    for(int i=2;i<=x;i++){
        ret*=i;
    }
    return ret;
}

double Interpolator_Hermite_N::calculateDifferenceQuotient(const vector<vector<double>>& table,int i,int j) const{
    //special case.(Hermite)
    if(interpolatingPoints[i+j]==interpolatingPoints[i]) return f.derivative(interpolatingPoints[i],j)/factorial(j);
    //normal case.
    return Interpolator_N::calculateDifferenceQuotient(table,i,j);
}