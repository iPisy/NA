#pragma once
#include"BFormSpline.hpp"

class BFS_Thm3_58:public BFormSpline{
private:
    void addBoundaryCondition(Eigen::MatrixXd* A,Eigen::VectorXd* b,const BoundaryCondition& boundaryCondition,const FunctionPointList& fList) override;
public:
    BFS_Thm3_58():BFormSpline(2){}
};