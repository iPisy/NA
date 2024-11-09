/**
 * @file
 * @brief Include declaration of class @ref Curve.
*/

#pragma once
#include<vector>
#include<limits>
#include"Function.hpp"
#include"DS&Constants.hpp"

using namespace std;

/**
 * @brief Define the Curve same as Definition 2.62. 
 * It consists of @ref Function in direction of every basis vector.
 * 
 * When initializing the curve, you need offer the sub-functions. 
 * The domains of the sub-functions of the curve do not need to be provided one by one. 
 * Just provide the domain of the curve, and all the curve operation will check it.
*/
class Curve{
public:
    Curve(double l=numeric_limits<double>::lowest(),double r=numeric_limits<double>::max(),bool leftClosed=1,bool rightClosed=1):
    l(l),r(r),leftClosed(leftClosed),rightClosed(rightClosed){}

    Curve(const vector<const Function*>& curve_Function,double l=numeric_limits<double>::lowest(),double r=numeric_limits<double>::max(),bool leftClosed=1,bool rightClosed=1):
    curve_Function(curve_Function), l(l), r(r),leftClosed(leftClosed),rightClosed(rightClosed){
        for(auto& it:curve_Function){
            const_cast<Function*>(it)->set_l(l);
            const_cast<Function*>(it)->set_r(r);
        }
    };

    /**
     * @brief Get the value vector of Curve at point t.
    */
    vector<double> operator()(double t) const;

    /**
     * @brief Get the tangent vector of order `order` at point t.
     * 
     * @param t the point.
     * @param order the order of the tangent vector.
     * 
     * @details We use central difference quotient there, it might be not precise. So we need override it if necessary.
     * And for those order>=2, if it is not overridden but called, program will throw an exception and exit.
    */
    vector<double> tangentVector(double t,int order,Direction direction=Direction::DEFAULT) const;

    int getDimension() const{
        return curve_Function.size();
    }

    double get_l() const{
        if(leftClosed) return l;
        return l+EPSILON;
    }

    double get_r() const{
        if(rightClosed) return r;
        return r-EPSILON;
    }

    bool get_leftClosed() const{
        return leftClosed;
    }

    bool get_rightClose() const{
        return rightClosed;
    }

    /**
     * @brief generate a list of uniformly distributed points within the definition domain of the curve.
     * 
     * @param m number of points. As it includes the endpoints, it should >= 2.
     * @param derivative_order the highest derivative order of the point.
     * @param direction used when dividing the shape into curves. @b direction=0 generate 
     * a list with increasing x, while @b direction=1 generate a list with decreasing x.
     * @details implement by calling @ref generatePointList(const IndependentVariableList&,int) const.
    */
    CurvePointList generatePointList(int number,int derivative_order=0,bool direction=0) const;

    /**
     * @brief generate a list of points, given the independent variable list.
     * 
     * @param in independent variable list.
     * @param derivative_order the highest derivative order of the point.
    */
    CurvePointList generatePointList(const IndependentVariableList& in,int derivative_order,bool direction=0) const;
    
protected:

    vector<const Function*> curve_Function;///< @ref Curve consists of a few @ref Function "Function"s.

    double l,///< left endpoint.
    r;///< right endpoint.

    bool leftClosed,///< is 1 if the domain is closed at the left endpoint, otherwise 0.
    rightClosed;///< similar to @ref leftClosed

};