/**
 * @file
 * @brief Declaration of class @ref Curve.
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
 * Just provide the domain of the curve, and it will convey it to its sub-functions.
*/
class Curve{
public:
    Curve(const DefinitionDomain& definitionDomain={}):
    definitionDomain(definitionDomain){}

    Curve(const vector<const Function*>& curve_Function,const DefinitionDomain& definitionDomain={}):
    curve_Function(curve_Function),definitionDomain(definitionDomain){
        for(auto& it:curve_Function){
            const_cast<Function*>(it)->set_definitionDomain(definitionDomain);
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
     * @details I use central difference quotient there, it might be not precise. So we need override it if necessary.
     * And for those order>=2, if it is not overridden but called, program will throw an exception and exit.
    */
    vector<double> tangentVector(double t,int order) const;

    int getDimension() const{
        return curve_Function.size();
    }

    DefinitionDomain getDefinitionDomain() const{
        return definitionDomain;
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

    DefinitionDomain definitionDomain;
};