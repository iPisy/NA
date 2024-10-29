/**
 * @file
 * @brief Include declaration of class `Interpolator_Hermite_N`
*/
#include"Interpolator_NewtonFormula.hpp"

/**
 * @brief The subclass of `Interpolator_N`. It is improved and can solve Hermite interpolation problem with Newton formula.
*/
class Interpolator_Hermite_N:public Interpolator_N{
public:
    Interpolator_Hermite_N(const Function& f,vector<double> vec):Interpolator_N(f,vec){}
protected:
    double calculateDifferenceQuotient(const vector<vector<double>>& table,int i,int j) const override;
};