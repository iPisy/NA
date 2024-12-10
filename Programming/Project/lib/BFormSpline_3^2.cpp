#include"BFormSpline_3^2.hpp"

void BFS3::addBoundaryCondition(Eigen::MatrixXd* A,Eigen::VectorXd* b,const BoundaryCondition& boundaryCondition,const FunctionPointList& fList){
    if(boundaryCondition.type==BoundaryCondition::Type::Theorem3_58) throw InvalidInputException{};
    if(boundaryCondition.type==BoundaryCondition::Type::Periodic) periodicBoundaryCondition(A,b,fList);
    else if(boundaryCondition.type==BoundaryCondition::Type::Complete){
        //add A
        for(int j=0;j<n;j++){
            (*A)(N,j)=((*bases)[j]).derivativeValue(fList[0].x);
        }
        for(int j=N-1;j<N+n-1;j++){
            (*A)(N+1,j)+=((*bases)[j]).derivativeValue(fList.back().x);
        }
        //add b
        (*b)(N)=boundaryCondition.l;
        (*b)(N+1)=boundaryCondition.r;
    }
    //natural
    else{
        //add A
        for(int j=0;j<n;j++){
            (*A)(N,j)=((*bases)[j]).derivativeValue(fList[0].x,2);
        }
        for(int j=N-1;j<N+n-1;j++){
            (*A)(N+1,j)+=((*bases)[j]).derivativeValue(fList.back().x,2);
        }
        //add b: do nothing.
    }
}
