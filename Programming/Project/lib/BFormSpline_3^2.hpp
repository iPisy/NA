#pragma once
#include"BFormSpline.hpp"

class BFS3:public BFormSpline{
public:
    BFS3():BFormSpline(3){}
private:
    void addBoundaryCondition(Eigen::MatrixXd* A,Eigen::VectorXd* b,const BoundaryCondition& boundaryCondition,const FunctionPointList& fList) override;
};