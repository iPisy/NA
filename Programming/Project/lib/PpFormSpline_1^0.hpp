#pragma once
#include"PpFormSpline.hpp"

class PFS1:public PpFormSpline{
public:
    PFS1():PpFormSpline(1){}
    void generate(const Spline* s,FunctionPointList fList){
        PpFormSpline::generate(s,fList,BoundaryCondition_Nothing());
    }
};