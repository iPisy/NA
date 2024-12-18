#include"PpFormSpline_3^2.hpp"

void PFS3::generate_A(const FunctionPointList& fList,const BoundaryCondition& boundaryCondition,const IndependentVariableList& knotList){
    A=new Eigen::MatrixXd(Eigen::MatrixXd::Zero(N,N));
    for(int r=0;r<N-2;r++){
        int c_start=r;
        (*A)(r,c_start)=(fList[r+1].x-fList[r].x)/(fList[r+2].x-fList[r].x);
        (*A)(r,c_start+1)=2;
        (*A)(r,c_start+2)=(fList[r+2].x-fList[r+1].x)/(fList[r+2].x-fList[r].x);
    }
}

Eigen::VectorXd PFS3::generate_b(const FunctionPointList& fList){
    Eigen::VectorXd ret=Eigen::VectorXd::Zero(N);
    DifferenceQuotientTable DQT(N,vector<double>(3));
    //init
    for(int r=0;r<N;r++) DQT[r][0]=fList[r].value[0];

    //dp
    for(int c=1;c<=2;c++){
        for(int r=c;r<N;r++){
            DQT[r][c]=(DQT[r][c-1]-DQT[r-1][c-1])/(fList[r].x-fList[r-c].x);
        }
    }

    //gen b
    for(int r=0;r<N-2;r++){
        ret(r)=6*DQT[r+2][2];
    }

    return ret;
}

void PFS3::addBoundaryCondition(Eigen::MatrixXd* A,Eigen::VectorXd* b,const BoundaryCondition& boundaryCondition,const FunctionPointList& fList){
    if(boundaryCondition.type==BoundaryCondition::Type::Theorem3_58){
        cerr<<"Invalid boundary condition!"<<endl;
        throw InvalidInputException{};
    }
    if(boundaryCondition.type==BoundaryCondition::Type::Complete){
        const BoundaryCondition_Complete& bc=static_cast<const BoundaryCondition_Complete&>(boundaryCondition);
        if(!reused){
            //add A
            (*A)(N-2,0)=2;
            (*A)(N-2,1)=1;
            (*A)(N-1,N-2)=1;
            (*A)(N-1,N-1)=2;
        }
        double ld1=bc.lv,rd1=bc.rv;
        //add b
        (*b)(N-2)=6*((fList[1].value[0]-fList[0].value[0])/(fList[1].x-fList[0].x)-ld1)/(fList[1].x-fList[0].x);
        (*b)(N-1)=6*(rd1-(fList[N-1].value[0]-fList[N-2].value[0])/(fList[N-1].x-fList[N-2].x))/(fList[N-1].x-fList[N-2].x);
    }
    else if(boundaryCondition.type==BoundaryCondition::Type::Natural){
        if(!reused){
            //add A
            (*A)(N-2,0)=1;
            (*A)(N-1,N-1)=1;
        }
        //add b: do nothing.
    }
    else if(boundaryCondition.type==BoundaryCondition::Type::D2){
        const BoundaryCondition_D2& bc=static_cast<const BoundaryCondition_D2&>(boundaryCondition);
        if(!reused){
            //add A
            (*A)(N-2,0)=1;
            (*A)(N-1,N-1)=1;
        }
        (*b)(N-2)=bc.l;
        (*b)(N-1)=bc.r;
    }
    else{//periodic
        if(!reused){
            //add A
            (*A)(N-2,0)=1;
            (*A)(N-2,N-1)=-1;

            (*A)(N-1,N-2)=(fList[N-1].x-fList[N-2].x)/(fList[1].x-fList[0].x+fList[N-1].x-fList[N-2].x);
            (*A)(N-1,N-1)=2;
            (*A)(N-1,1)=(fList[1].x-fList[0].x)/(fList[1].x-fList[0].x+fList[N-1].x-fList[N-2].x);
        }
        //add b
        double dq_latter=(fList[1].value[0]-fList[0].value[0])/(fList[1].x-fList[0].x);
        double dq_former=(fList[N-1].value[0]-fList[N-2].value[0])/(fList[N-1].x-fList[N-2].x);
        (*b)(N-1)=6*(dq_latter-dq_former)/(fList[1].x-fList[0].x+fList[N-1].x-fList[N-2].x);
    }
}

void PFS3::generate_PiecePoly(const Eigen::VectorXd& b,const FunctionPointList& fList,const BoundaryCondition& boundaryCondition){
    vector<Polynomial> foo;

    for(int i=0;i<N-1;i++){
        Polynomial pushee(DefinitionDomain{fList[i].x,fList[i+1].x});
        Polynomial unit(vector<double>{-fList[i].x,1});
        pushee+=fList[i].value[0];
        pushee+=(
            ((fList[i+1].value[0]-fList[i].value[0]))/((fList[i+1].x-fList[i].x))
            -
            (b(i+1)+2*b(i))*(fList[i+1].x-fList[i].x)/6
        )*unit;
        pushee+=(b(i)/2)*unit*unit;
        pushee+=(b(i+1)-b(i))/(6*(fList[i+1].x-fList[i].x))*unit*unit*unit;
        foo.push_back(pushee);
    }

    piecewisePolynomial=PiecewisePolynomial(foo);
}