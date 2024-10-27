#include"Interpolator.hpp"
#include"Function.hpp"

class F:public Function{
public:
    double operator()(double x) const override{
        if(x==0) return 5;
        if(x==1) return 3;
        if(x==3) return 5;
        if(x==4) return 12;
        return 0;
    }
};

int main(){
    Interpolator x(F(),{0,1,3,4});
    x.interpolate().print();
}