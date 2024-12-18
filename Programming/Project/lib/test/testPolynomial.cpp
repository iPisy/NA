#include"../Polynomial.hpp"
#include<cmath>
using namespace std;

int main(){
    Polynomial p1(vector<double>{1/2.0/sqrt(3)}),p2(vector<double>{-6.5,1}),p3(vector<double>{91.0/3,-13,1});
    p2*=1/sqrt(143);
    p3*=sqrt(3.0/4004);
    cout<<p1*479.7780736966+p2* 49.2546543894+p3*330.3306671357<<endl;
}