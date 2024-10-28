#include"Interpolator_NewtonFormula.hpp"

class Interpolator_Hermite_N:public Interpolator_N{
public:
    Interpolator_Hermite_N(const Function& f,vector<double> vec):Interpolator_N(f,vec){}
protected:
    double calculateDifferenceQuotient(const vector<vector<double>>& table,int i,int j) const override;
};