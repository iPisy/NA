#include"Polynomial.hpp"

class BFSRB:public Polynomial{
public:
    BFSRB(double l,double r):Polynomial(vector<double>{1},DefinitionDomain{l,r,0,1}){}
};