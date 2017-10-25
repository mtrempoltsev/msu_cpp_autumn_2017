#include <iostream>
#include "matrix.h"

using namespace std;

void checkOperatorBrackets(Matrix<double>& m){
    int i = m[0][0];
    m[0][0] = i + 10;
    if(m[0][0] != i + 10){
        cerr<< "operaor [] does not work\n";
    }
}

void checkOperatorMultiply(Matrix<double>& m){
    Matrix<double> matr = m;
    matr *= 10;
    for(int i = 0; i < m.getColumnsNum(); ++i){
        for(int j = 0; j < m.getRowsNum(); ++j){
            if(m[i][j] * 10 != matr[i][j]){
                cerr<< "operaor * on number does not work\n";
                return;
            }
        }
    }
}

void checkOperatorEqualence(Matrix<double>& m){
    Matrix<double> matr = m;
    if(matr == m){

    } else{
        cerr<<"operator == does not work\n";
    }

    if(matr != m){
        cerr<<"operator == does not work\n";
    }
}

void checkOperatorMultiplyOnVec(){
    vector<double> myvec;
    Matrix<double> m(2, 2);
    m[0][0] = 1;
    m[1][0] = 2;
    m[0][1] = 3;
    m[1][1] = 4;
    myvec.push_back(5);
    myvec.push_back(6);
    vector<double> res = m * myvec;
    if(res[0] != 17){
        cerr<<res[0];
        return;
    }
    if(res[1] != 15 + 24){
        cerr<<"operator * on vector does not work";
    }
}

int main()
{
    Matrix<double>* m = new Matrix<double>(3,2);

    //Matrix m(2, 2);
    //vector<double> v(2);
    checkOperatorBrackets(*m);
    checkOperatorEqualence(*m);
    checkOperatorMultiply(*m);
    checkOperatorMultiplyOnVec();
    cout<<"end checks\n";
    return 0;
}

