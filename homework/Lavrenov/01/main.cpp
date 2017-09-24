
#include <cstdlib>
#include <chrono>
#include <iostream>

using namespace std;

struct Matrix{
    Matrix(int colnum, int rownum);
    ~Matrix();
    int** values;
    int colnum, rownum;
};

int summ_by_rows(Matrix* matrix){
    int res = 0;
    for(int i = 0; i < matrix->rownum ;++i){
        for(int j = 0; j < matrix->colnum ;++j){
            res += matrix->values[j][i];
        }
    }
    return res;
}

int summ_by_column(Matrix* matrix){
    int res = 0;
    for(int i = 0; i < matrix->colnum ;++i){
        for(int j = 0; j < matrix->rownum ;++j){
            res += matrix->values[i][j];
        }
    }
    return res;
}

int main(int argc, char** argv){
    Matrix* m = new Matrix(10000, 10000);

    auto start = chrono::high_resolution_clock::now();
    int res = summ_by_column(m);
    auto finish = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<std::chrono::microseconds>(finish - start).count() <<" us summ by columns. res="<<res << endl;

    start = chrono::high_resolution_clock::now();
    res = summ_by_rows(m);
    finish = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<std::chrono::microseconds>(finish - start).count() <<" us summ by rows. res="<<res<< endl;
    delete m;
    system("pause");
    return 0;
}

Matrix::Matrix(int colnum, int rownum){
    this->colnum = colnum;
    this->rownum = rownum;
    values = new int* [colnum];
    for(int i = 0; i < colnum; ++i){
        values[i] = new int[rownum];
    }
}

Matrix::~Matrix(){
    for(int i = 0; i < colnum; ++i){
        delete[] values[i];
    }
    delete[] values;
}
