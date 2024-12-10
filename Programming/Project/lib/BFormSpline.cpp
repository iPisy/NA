#include"BFormSpline.hpp"
#include"BFormSplineRecursionBase.hpp"
#include"Exceptions.hpp"

void BFormSpline::reuse(const Spline* s){
    A=dynamic_cast<const BFormSpline*>(s)->A;
    bases=dynamic_cast<const BFormSpline*>(s)->bases;
}

void BFormSpline::generate_A(const FunctionPointList& fList,const BoundaryCondition& boundaryCondition,const IndependentVariableList& knotList){
    if(boundaryCondition.type!=BoundaryCondition::Type::Theorem3_58) generate_bases(fList);
    else generate_bases(knotList);
    A=new Eigen::MatrixXd(Eigen::MatrixXd::Zero(N+n-1,N+n-1));

    for(int i=0;i<fList.size();i++){
        //ignore continuous items of 0.
        for(int j=i;j<N+n-1;j++){
            double foo=((*bases)[j])(fList[i].x);
            if(foo==0) break;
            (*A)(i,j)=foo;
        }
    }
}

void BFormSpline::generate_bases(const FunctionPointList& fList){
    IndependentVariableList l;
    for(auto& it:fList) l.push_back(it.x);
    generate_bases(l);
}

void BFormSpline::generate_bases(const IndependentVariableList& knotList){
    vector<vector<PiecewisePolynomial> > PP_GenerationTable(n+1,vector<PiecewisePolynomial>(N+2*n-1));
    
    IndependentVariableList extendedKnotList;
    for(int i=0;i<n;i++){
        extendedKnotList.push_back(knotList[0]-1.0*(n-i)*(knotList.back()-knotList[0])/(N-1));
    }
    extendedKnotList.insert(extendedKnotList.end(),knotList.begin(),knotList.end());
    for(int i=n+N;i<2*n+N;i++){
        extendedKnotList.push_back(knotList.back()+1.0*(i-(n+N)+1)*(knotList.back()-knotList[0])/(N-1));
    }

    //init
    for(int i=0;i<2*n+N-1;i++){
        PP_GenerationTable[0][i]=BFSRB(extendedKnotList[i],extendedKnotList[i+1]);
    }

    //dp
    for(int i=1;i<=n;i++){
        //i is the order.
        for(int j=0;j<2*n-1+N-i;j++){
            PP_GenerationTable[i][j]=PP_GenerationTable[i-1][j]*(Polynomial(vector<double>{-extendedKnotList[j],1})/(extendedKnotList[j+i]-extendedKnotList[j]))+PP_GenerationTable[i-1][j+1]*(Polynomial(vector<double>{extendedKnotList[i+j+1],-1})/(extendedKnotList[i+j+1]-extendedKnotList[j+1]));
        }
    }

    //assign
    bases=new vector<PiecewisePolynomial>(N+n-1);
    for(int i=0;i<N+n-1;i++){
        (*bases)[i]=PP_GenerationTable[n][i];
    }
}

Eigen::VectorXd BFormSpline::generate_b(const FunctionPointList& fList){
    Eigen::VectorXd ret=Eigen::VectorXd::Zero(N+n-1);
    for(int i=0;i<fList.size();i++){
        ret(i)=fList[i].value[0];
    }
    return ret;
}

void BFormSpline::addBoundaryCondition(Eigen::MatrixXd* A,Eigen::VectorXd* b,const BoundaryCondition& boundaryCondition,const FunctionPointList& fList){
    if(boundaryCondition.type==BoundaryCondition::Type::Periodic) periodicBoundaryCondition(A,b,fList);
    else{
        cerr<<"Only periodic boundary condition are implemented in B-form spline of order n, where n is arbitrary."<<endl;
        throw UnimplementedException{};
    }
}

void BFormSpline::periodicBoundaryCondition(Eigen::MatrixXd* A,Eigen::VectorXd* b,const FunctionPointList& fList){
    if(!reused){
        //add A
        for(int i=1;i<n;i++){
            //line N-1+i
            for(int j=0;j<n;j++){
                (*A)(N-1+i,j)=((*bases)[j]).derivativeValue(fList[0].x,i);
            }
            for(int j=N-1;j<N+n-1;j++){
                (*A)(N-1+i,j)-=((*bases)[j]).derivativeValue(fList.back().x,i);
            }
        }
    }
    //add b: do nothing.
}

void BFormSpline::generate_piecePoly(Eigen::VectorXd& b){
    for(int i=0;i<N+n-1;i++){
        piecewisePolynomial+=(*bases)[i]*b[i];
    }
}

void BFormSpline::draw_GivenCoef(const vector<double>& coefs,const IndependentVariableList& knotList,const string& filename){
    N=knotList.size();
    if(coefs.size()!=N+n-1) throw InvalidInputException{};
    generate_bases(knotList);
    for(int i=0;i<N+n-1;i++){
        piecewisePolynomial+=(*bases)[i]*coefs[i];
    }
    piecewisePolynomial.print_Latex(filename,n,"$B\\text{-}form\\text{ }spline\\in \\mathbb{S}_{"+to_string(n)+"}^{"+to_string(k)+"}$");
}