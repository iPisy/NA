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
        (*b)(N)=bc.l;
        (*b)(N+1)=bc.r;
    }
    else if(boundaryCondition.type==BoundaryCondition::Type::NotAKnot){
        if(fList.size()<4){
            cerr<<"When using not-a-knot boundary condition, the number of knots should >=4!"<<endl;
            throw InvalidInputException{};
        }
        if(!reused){
            //add A
            int foo[2]={1,N-2};
            for(int i=0;i<2;i++){
                int knotIndex_start=foo[i];
                int row=N+i;
                double bar[3]={fList[knotIndex_start+1].x-fList[knotIndex_start].x,fList[knotIndex_start-1].x-fList[knotIndex_start+1].x,fList[knotIndex_start].x-fList[knotIndex_start-1].x};
                for(int j=0;j<3;j++){
                    int knotIndex=knotIndex_start+j;
                    for(int c=knotIndex-1;c<=knotIndex+n-2;c++){
                        (*A)(row,c)+=bar[j]*(*bases)[c].derivativeValue(fList[knotIndex-1].x,2);
                    }
                }
            }
        }
        //add b: do nothing.
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
