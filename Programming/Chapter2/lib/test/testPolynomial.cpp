#include"../Polynomial.hpp"
#include<iostream>

using namespace std;

int main(){
    Polynomial x(vector<double>{0,2,0,4,-2,0});
    cout<<(x/3)<<endl;
}

// int main(){
//     Polynomial A({1,-2,1}),a({-1,1});
//     cout<<A.getLocalMax({-2,5})<<endl;
//     cout<<A.getLocalMin({-1,1})<<endl;
// }