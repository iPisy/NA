#pragma once
#include"BFormSpline.hpp"

class BFS3:public BFormSpline{
public:
    BFS3():BFormSpline(3){}
    void generate(const Spline* s,FunctionPointList fList,const BoundaryCondition& boundaryCondition){
        BFormSpline::generate(s,fList,boundaryCondition);
    }
private:
    void addBoundaryCondition(Eigen::MatrixXd* A,Eigen::VectorXd* b,const BoundaryCondition& boundaryCondition,const FunctionPointList& fList) override;
};