#include"BFormSpline.hpp"
#include"BFormSplineRecursionBase.hpp"

void BFormSpline::generate_A(const FunctionPointList& fList,const BoundaryCondition& boundaryCondition,const IndependentVariableList& knotList){
    if(boundaryCondition.type!=BoundaryCondition::Type::Theorem3_58){
        if(!knotList.empty()) throw UnimplementedException{};
        else generate_bases(fList);
    }
    else generate_bases(knotList);
    ///
    ///
    ///
    ///
    ///
    ///
    ///
    ///
    ///
    ///
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
        for(int j=0;j<2*n-2+N-i;j++){
            PP_GenerationTable[i][j]=PP_GenerationTable[i-1][j]*(Polynomial(vector<double>{-extendedKnotList[j],1})/(extendedKnotList[j+i]-extendedKnotList[j]))+PP_GenerationTable[i-1][j+1]*(Polynomial(vector<double>{extendedKnotList[i+j+1],-1})/(extendedKnotList[i+j+1]-extendedKnotList[j+1]));
        }
    }

    bases=new vector<PiecewisePolynomial>(N+n-1);
    for(int i=0;i<N+n-1;i++){
        (*bases)[i]=PP_GenerationTable[n][i];
    }
}

Eigen::VectorXd BFormSpline::generate_b(const FunctionPointList& fList,const BoundaryCondition& boundaryCondition){

}

void BFormSpline::generate_piecePoly(const Eigen::VectorXd& b){

}