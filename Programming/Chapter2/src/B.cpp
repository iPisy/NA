#include"../lib/Interpolator.hpp"
#include"../lib/Function.hpp"

class F:public Function{
public:
    double operator()(double x) const override{
        return 1/(1+x*x);
    }
};

int main(){
    vector<double> interpolatingPoints[4];
    for(int n=2;n<=8;n+=2){
        for(int i=0;i<=n;i++){
            interpolatingPoints[(n-2)/2].push_back(-5+10.0*i/n);
        }
    }

    Interpolator interpolator{F()};
    for(int i=0;i<4;i++){
        interpolator.setInterpolatingPoints(interpolatingPoints[i]);
        interpolator.interpolate().print();
    }
}