/**
 * @file
 * @brief Implement the function in `CubicBezierCurve.hpp`.
*/

#include"CubicBezierCurve.hpp"
#include"Polynomial.hpp"
#include"BernsteinPolynomial.hpp"
#include<fstream>

using namespace std;

Curve CubicBezierCurve::generateCurve(){
    vector<double> p_0=exactCurve(t_0),p_1=exactCurve(t_1),
    p_0_d=exactCurve.derivative(t_0,1),p_1_d=exactCurve.derivative(t_1,1);

    int dimension=exactCurve.getDimension();

    vector<double> q_0=p_0,q_3=p_1,q_1,q_2;

    for(int i=0;i<dimension;i++){
        q_1.push_back(p_0_d[i]/3+p_0[i]);
        q_2.push_back(p_1[i]-p_1_d[i]/3);
    }

    vector<const Function&> init;
    for(int i=0;i<dimension;i++){
        Polynomial* poly=new Polynomial;
        (*poly)+=(BernsteinPolynomial{3,0}*q_0[i]+BernsteinPolynomial{3,1}*q_1[i]+
        BernsteinPolynomial{3,2}*q_2[i]+BernsteinPolynomial{3,3}*q_3[i]);
        init.push_back(*poly);
    }
    return Curve(init,t_0,t_1);
}