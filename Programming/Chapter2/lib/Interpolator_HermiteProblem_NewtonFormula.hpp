/**
 * @file
 * @brief Declaration of class @ref Interpolator_Hermite_N.
*/
#include"Interpolator_NewtonFormula.hpp"

/**
 * @brief A sort of @ref Interpolator_N. It is improved and can solve Hermite interpolation problem with Newton formula.
*/
class Interpolator_Hermite_N:public Interpolator_N{
public:
    Interpolator_Hermite_N(const FunctionPointList& init):Interpolator_N(init){}
protected:
    double getInitializeValue(const vector<vector<double>>& table,int i) const override{
        if(i>=1)
            if(interpolationPoints[i].x==interpolationPoints[i-1].x) return table[i-1][0];
        return Interpolator_N::getInitializeValue(table,i);
    }
    double calculateDifferenceQuotient(const DifferenceQuotientTable& table,int i,int j) const override;
};