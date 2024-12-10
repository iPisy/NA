#include"PpFormSpline.hpp"

void PpFormSpline::generate_A(const FunctionPointList& fList,const BoundaryCondition& boundaryCondition,const IndependentVariableList& knotList){
    A=new Eigen::MatrixXd(Eigen::MatrixXd::Zero((N-1)*(n+1),(N-1)*(n+1)));

    //interepolation condition
    for(int i=0;i<N-1;i++){
        int r=2*i;
        double p1=1,p2=1;
        for(int c=i*(n+1);c<(i+1)*(n+1);c++){
            (*A)(r,c)=p1;
            (*A)(r+1,c)=p2;
            p1*=fList[i].x;
            p2*=fList[i+1].x;
        }
    }
    //continuous condition: N-2 equations with n-1 order.
    for(int i=0;i<N-2;i++){
        //between Polynomial i and i+1, at point i+1.
        int r_start=2*(N-1)+i*(n-1);

        vector<Polynomial> coef;
        Polynomial it(vector<double>{1});
        const Polynomial unit(vector<double>{0,1});
        for(int order=0;order<=n;order++){
            coef.push_back(it);
            it*=unit;
        }

        for(int order=1;order<=n-1;order++){
            int r=r_start+order-1;
            for(auto& it:coef) it=it.getDerivative();
            for(int c=i*(n+1);c<(i+1)*(n+1);c++){
                //Poly i
                (*A)(r,c)=coef[c-i*(n+1)](fList[i+1].x);
                //Poly i+1
                (*A)(r,c+n+1)=-coef[c-i*(n+1)](fList[i+1].x);
            }
        }
    }
}

Eigen::VectorXd PpFormSpline::generate_b(const FunctionPointList& fList){
    Eigen::VectorXd ret=Eigen::VectorXd::Zero((n+1)*(N-1));
    ret(0)=fList[0].value[0];
    for(int i=1;i<N-1;i++){
        ret(1+(i-1)*2)=fList[i].value[0];
        ret(1+(i-1)*2+1)=fList[i].value[0];
    }
    ret(2*N-3)=fList[N-1].value[0];
    return ret;
}

void PpFormSpline::addBoundaryCondition(Eigen::MatrixXd* A,Eigen::VectorXd* b,const BoundaryCondition& boundaryCondition,const FunctionPointList& fList){
    if(boundaryCondition.type==BoundaryCondition::Type::Periodic) periodicBoundaryCondition(A,b,fList);
    else{
        cerr<<"Only periodic boundary condition are implemented in pp-form spline of order n, where n is arbitrary."<<endl;
        throw UnimplementedException{};
    }
}

void PpFormSpline::periodicBoundaryCondition(Eigen::MatrixXd* A,Eigen::VectorXd* b,const FunctionPointList& fList){
    //between Polynomial 1 and N-1, at point 1 and N.

    vector<Polynomial> coef;
    Polynomial it(vector<double>{1});
    const Polynomial unit(vector<double>{0,1});
    for(int order=0;order<=n;order++){
        coef.push_back(it);
        it*=unit;
    }

    for(int order=1;order<=n-1;order++){
        int r=(n+1)*(N-1)-(n-1)+order-1;
        for(auto& it:coef) it=it.getDerivative();
        for(int c=0;c<n+1;c++){
            //Poly i
            (*A)(r,c)=coef[c](fList[0].x);
            //Poly i+1
            (*A)(r,(n+1)*(N-1)-1-n+c)=-coef[c](fList[N-1].x);
        }
    }
}

void PpFormSpline::generate_piecePoly(Eigen::VectorXd& b,const FunctionPointList& fList){
    vector<Polynomial> foo;
    for(int i=0;i<N-1;i++){
        int r=i*(n+1);
        vector<double> polyCoef;
        for(int order=0;order<=n;order++){
            polyCoef.push_back(b(r+order));
        }
        foo.push_back(Polynomial(polyCoef,DefinitionDomain{fList[i].x,fList[i+1].x}));
    }
    piecewisePolynomial=PiecewisePolynomial(foo);
}