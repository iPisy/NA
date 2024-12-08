#include"Polynomial.hpp"

class BFSRB:public Polynomial{
    BFSRB(double l,double r):Polynomial(vector<double>{1},DefinitionDomain{l,r}){}
};