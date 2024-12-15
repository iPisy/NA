#include"../BFormSpline.hpp"
#include"../Function.hpp"

class F:public Function{
    double getValue(double x) const override{
        return x;
    }
};

int main(){
    // F f;
    // FunctionPointList l=f.generatePointList(vector<double>{1,2,3,4,5},0);
    // BFormSpline b(3);
    
    // b.generate_bases(l);
    // (*(b.t()))[1].print_Latex("0.tex",0);
}