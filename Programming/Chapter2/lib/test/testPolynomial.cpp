#include"../Polynomial.hpp"

int main(){
Polynomial P1({2, 3, 3,4,5});
Polynomial P2({-1, -2, -3, -4, -5});
    Polynomial c;
    c+=P1;
    c+=P2;
    c.print();
}