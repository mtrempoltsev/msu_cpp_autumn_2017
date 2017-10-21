//
//  main.cpp
//  matrix
//
//  Created by Павел Адаменко on 10/19/17.
//  Copyright © 2017 Павел Адаменко. All rights reserved.
//

#include <iostream>
#include <assert.h>
#include <vector>

class Matrix{
public:
    class column{
    public:
        double *t;
        column(int M){ t = new double[M]; };
        column(){}; //default constructor
        double& operator[](int i){ return t[i]; };
        int get_elem(int i){ return t[i]; };
    };
    
    int N,M;
    column *a;
    Matrix(int N_temp, int M_temp){
        N = N_temp;
        M = M_temp;
        a = new column[N];
        for(int i=0; i<N; i++){
            a[i] = column(M);
        }
    };
    
    void print_matrix(){
        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++){
                std::cout << a[i][j] <<"\t";
            }
            std::cout << "\n";
        }
    }
    int get_columns(){return N;}
    int get_rows()   {return M;}
    
    //Indexation operation
    column& operator[](int i){ return a[i]; };
    
    //Matrix[NxM] * number -> Matrix[NxM]
    Matrix& operator*(double b){
        Matrix& c = *(new Matrix(this->N, this->M));
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                c[i][j] = b * this->a[i][j];
            }
        }
        return c;
    };
    
    //Matrix[NxM] + Matrix[NxM] -> Matrix[NxM]
    Matrix& operator+(Matrix b){ // M + M
        assert((this -> N == b.N) and (this -> M == b.M));
        
        Matrix& c = *(new Matrix(this->N, this->M));
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                c[i][j] = b[i][j]+this->a[i][j];
            }
        }
        return c;
    };
    
    //Matrix[NxM] * Matrix[MxK] -> Matrix[NxK]
    Matrix& operator*(Matrix b){
        assert(this -> M == b.N);
        Matrix& c = *(new Matrix(this -> N, b.M));
        for(int i=0; i<this -> N; i++){
            for(int j=0; j<b.M; j++){
                double sum = 0;
                for(int k=0; k<this -> M; k++){
                    sum += this -> a[i][k] * b[k][i];
                }
                c[i][j] = sum;
            }
        }
        return c;
    }
    //Matrix[NxM] * vect[Mx1] -> Matrix[Nx1]
    Matrix& operator*(const std::vector<double> &v){
        assert(this -> M == v.size());
        Matrix& c = *(new Matrix(this -> N, 1));
        for(int i=0; i<this->N; i++){
            double sum = 0.0;
            for(int j=0; j <this->M; j++){
                sum += this -> a[i][j] * v[j];
            }
            c[i][0] = sum;
        }
        return c;
    }
    
    //Matrix += Matrix
    Matrix& operator+=(Matrix b){ // M +=b
        assert((this -> N == b.N) and (this -> M ==b.M));
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                this->a[i][j] = b[i][j]+this->a[i][j];
            }
        }
        return *this;
    }
    
    //Matrix -= Matrix
    Matrix& operator-=(Matrix b){ // M +=b
        assert((this -> N == b.N) and (this -> M ==b.M));
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                this->a[i][j] = -b[i][j]+this->a[i][j];
            }
        }
        return *this;
    };
    //equal Matrix
    bool operator==(Matrix a){
        bool equal = true;
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                if (this->a[i][j] != a[i][j])
                    equal = false;
            }
        }
        return equal;
    }
    
};

class run_test{
private:
    bool currentTest;
    bool allPassed;
public:
    void check(bool value)
    {
        if (!value)
        {
            std::cout << "error" << std::endl<<"\n";
            allPassed = false;
            currentTest = false;
        }
    }
    
    void checkGetSet()
    {
        currentTest = true;
        std::cout << "checkGetSet tests passed :       \t";
        Matrix m(2, 3);
        m[0][0] = 1;
        m[0][1] = 2;
        m[0][2] = 3;
        m[1][0] = 4;
        m[1][1] = 5;
        m[1][2] = 6;
        
        check(m[0][0] == 1);
        check(m[0][1] == 2);
        check(m[0][2] == 3);
        check(m[1][0] == 4);
        check(m[1][1] == 5);
        check(m[1][2] == 6);
        
        m[1][2] = 100;
        check(m[1][2] == 100);
        std :: cout << (currentTest ? "true" : "false") <<"\n";
    }
    void checkGetRowsColumns()
    {
        currentTest = true;
        std::cout << "checkGetRowsColumns test passed : \t";
        Matrix m(2, 2);
        check(m.get_rows() == 2);
        check(m.get_columns() == 2);
        std :: cout << (currentTest ? "true" : "false") <<"\n";
    }
    
    void checkMatrixDotNum()
    {
        this -> currentTest = true;
        std::cout << "checkMatrixDotNum test passed : \t";
        Matrix m(2, 2);
        m[0][0] = 1;
        m[0][1] = 2;
        m[1][0] = 3;
        m[1][1] = 4;
        
        m = m * 4;
        
        check(m[0][0] == 4);
        check(m[0][1] == 8);
        check(m[1][0] == 12);
        check(m[1][1] == 16);

        std :: cout << (currentTest ? "true" : "false") <<"\n";
    }
    void checkMatrixDotVect()
    {
        currentTest = true;
        std::cout << "checkMatrixDotVect test passed : \t";
        Matrix m(2, 2);
        m[0][0] = 1;
        m[0][1] = 2;
        m[1][0] = 3;
        m[1][1] = 4;
        
        std::vector<double> v = {-1,1};
        m = m*v;
        
        check(m[0][0] == 1);
        check(m[1][0] == 1);
        check(m.get_rows() == 1);
        check(m.get_columns() == 2);
        
        std :: cout <<  (currentTest ? "true" : "false") <<"\n";
    }
    void checkEqual(){
        currentTest = true;
        std::cout << "checkMatrixDotVect test passed : \t";
        
        Matrix m(2, 2);
        m[0][0] = 1;
        m[0][1] = 2;
        m[1][0] = 3;
        m[1][1] = 4;
        Matrix n(2, 2);
        n[0][0] = 1;
        n[0][1] = 2;
        n[1][0] = 3;
        n[1][1] = 4;
        check(n == m);
        std::cout << (currentTest ? "true" : "false") << "\n";
    }
    run_test(){
        currentTest = true;
        allPassed   = true;
        checkGetSet();
        checkGetRowsColumns();
        checkMatrixDotNum();
        checkMatrixDotVect();
        checkEqual();
        std :: cout << "All test passed : \t" << (allPassed ? "true" : "false") <<"\n";
    }
};

int main(int argc, const char * argv[]) {
    run_test();
    return 0;
};
