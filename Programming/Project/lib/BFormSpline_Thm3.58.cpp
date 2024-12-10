#include"BFormSpline_Thm3.58.hpp"

void BFS_Thm3_58::addBoundaryCondition(Eigen::MatrixXd* A,Eigen::VectorXd* b,const BoundaryCondition& boundaryCondition,const FunctionPointList& fList){
    if(boundaryCondition.type!=BoundaryCondition::Type::Theorem3_58){
        cerr<<"You should offer boundary condition in Theorem 3.58."<<endl;
        throw InvalidInputException{};
    }
    
    if(fList.size()!=N-1){
        cerr<<"In spline of Theorem 3.58, number of interpolation points should be N-1."<<endl;
        throw InvalidInputException{};
    }

    const BoundaryCondition_Theorem3_58& foo=static_cast<const BoundaryCondition_Theorem3_58&>(boundaryCondition);
    double l=foo.l,r=foo.r,lv=foo.lv,rv=foo.rv;
    if(!reused){
        //add A
        for(int j=0;j<n;j++){
            (*A)(N-1,j)=((*bases)[j])(l);
        }
        for(int j=N-1;j<N+n-1;j++){
            (*A)(N,j)+=((*bases)[j])(r);
        }
    }
    
    //add b
    (*b)(N-1)=lv;
    (*b)(N)=rv;
    
}