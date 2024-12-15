#include"../Polynomial.hpp"

int main(){
    Polynomial p(vector<double>{0,0,1},DefinitionDomain{-1,0});
    cout<<p/10<<endl;
}