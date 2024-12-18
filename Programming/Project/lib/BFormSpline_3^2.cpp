#include"BFormSpline_3^2.hpp"

void BFS3::addBoundaryCondition(Eigen::MatrixXd* A,Eigen::VectorXd* b,const BoundaryCondition& boundaryCondition,const FunctionPointList& fList){
    if(boundaryCondition.type==BoundaryCondition::Type::Theorem3_58){
        cerr<<"Invalid boundary condition!"<<endl;
        throw InvalidInputException{};
    }
    if(boundaryCondition.type==BoundaryCondition::Type::Periodic) periodicBoundaryCondition(A,fList);
    else if(boundaryCondition.type==BoundaryCondition::Type::Complete){
        const BoundaryCondition_Complete& foo=static_cast<const BoundaryCondition_Complete&>(boundaryCondition);
        double lv=foo.lv,rv=foo.rv;
        if(!reused){
            //add A
            for(int j=0;j<n;j++){
                (*A)(N,j)=((*bases)[j]).derivativeValue(fList[0].x);
            }
            for(int j=N-1;j<N+n-1;j++){
                (*A)(N+1,j)+=((*bases)[j]).derivativeValue(fList.back().x);
            }
        }
        
        //add b
        (*b)(N)=lv;
        (*b)(N+1)=rv;
    }
    else if(boundaryCondition.type==BoundaryCondition::Type::D2){
        const BoundaryCondition_D2& bc=static_cast<const BoundaryCondition_D2&>(boundaryCondition);
        if(!reused){
            //add A
            for(int j=0;j<n;j++){
                (*A)(N,j)=((*bases)[j]).derivativeValue(fList[0].x,2);
            }
            for(int j=N-1;j<N+n-1;j++){
                (*A)(N+1,j)+=((*bases)[j]).derivativeValue(fList.back().x,2);
            }
        }
        (*b)(N-2)=bc.l;
        (*b)(N-1)=bc.r;
    }
    else{//natural        
        if(!reused){
            //add A
            for(int j=0;j<n;j++){
                (*A)(N,j)=((*bases)[j]).derivativeValue(fList[0].x,2);
            }
            for(int j=N-1;j<N+n-1;j++){
                (*A)(N+1,j)+=((*bases)[j]).derivativeValue(fList.back().x,2);
            }
        }
        //add b: do nothing.
    }
}
