#pragma once
#include"BFormSpline.hpp"

class BFS1:public BFormSpline{
public:
    BFS1():BFormSpline(1){}
    void generate(const Spline* s,FunctionPointList fList){
        BFormSpline::generate(s,fList,BoundaryCondition_Nothing());
    }
};