#include"../lib/Function.hpp"
#include"../lib/Interpolator.hpp"
#include<vector>
#include<cmath>

using namespace std;

const double PI=acos(-1.);

class F:public Function{
    double operator()(double x) const override{
        return 1/(1+25*x*x);
    }
};

int main(){
    vector<double> interpolatingPoints[4];
    for(int i=0;i<4;i++){
        int n=(i+1)*5;
        for(int j=1;j<=n;j++){
            interpolatingPoints[i].push_back(cos((2*j-1)*PI/(2*n)));
        }
    }
    F f;
    Interpolator interpolator{f};
    for(int i=0;i<4;i++){
        interpolator.setInterpolatingPoints(interpolatingPoints[i]);
        interpolator.interpolate().print();
    }
    return 0;
}