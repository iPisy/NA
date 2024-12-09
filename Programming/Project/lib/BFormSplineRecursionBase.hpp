#include"Polynomial.hpp"

class BFSRB:public Polynomial{
public:
    enum class Mode{
        Default,
        PlaceHolder
    };
    BFSRB(double l,double r,Mode mode=Mode::Default):Polynomial(vector<double>{mode==Mode::Default?1.0:0},DefinitionDomain{l,r}){}
};