#include"../lib/PiecewisePolynomial.hpp"
#include<vector>

using namespace std;

/**
 * @brief difference quotient table for Theorem 3.32.
 */
class Table{
    using T=vector<vector<PiecewisePolynomial> >;
private:
    int n;
    T t;
public:
    Table(int n):n(n){
        if(n<0) throw InvalidInputException{};
        t=T(n+2,vector<PiecewisePolynomial>(n+2));
    };
    void generate(const vector<double>& t_iList={});
    const T& getTable(){
        return t;
    }
};

void Table::generate(const vector<double>& t_iList){
    bool t_default=0;
    if(t_iList.empty()){
        t_default=1;
    }
    if(t_default==0 && t_iList.size()!=n+2) throw InvalidInputException{};

    //init
    for(int i=0;i<=n+1;i++){
        Polynomial unit(vector<double>{t_default?1.0*i:t_iList[i],-1});
        Polynomial foo=(t_default?n+1:t_iList[n+1]-t_iList[0])*unit;
        cout<<i<<" "<<foo<<endl;
        for(int i=1;i<n;i++) foo*=unit;
        t[i][0]=PiecewisePolynomial(vector<Polynomial>{foo});
    }

    //dp
    for(int j=1;j<=n+1;j++){
        for(int i=j;i<=n+1;i++){
            t[i][j]=(t[i][j-1]-t[i-1][j-1])/(t_default?j:t_iList[i]-t_iList[i-j]);
        }
    }
}

int main(){
    // const int n=2;
    // for(int order=1;order<n;order++){
    //     for(int j=0;j<)
    // }
    Table table(1);
    table.generate();
    LatexOutputer o("n=1.tex");
    o.quickStart();
    cout<<table.getTable()[2][2](1)<<endl;
    table.getTable()[2][2].print_Latex_SolePoly(o);
    o.quickEnd();
}