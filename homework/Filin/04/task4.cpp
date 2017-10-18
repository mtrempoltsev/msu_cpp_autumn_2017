//
//  main.cpp
//  Task4
//
//  Created by Максим on 17.10.17.
//  Copyright © 2017 Максим. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;
using std::ostream;
using std::istream;

void checkGetSet();
void checkGetRowsColumns();
void check(bool value);
void checkMulVec();
void checkMulNumber();
void checkEqual();


//прокси-класс для рядов матрицы Matrix
class Array {
private:
    double *arr;
    int N;
    //проверка на выход за границы массива
    void check(int index) const {
        if (index >= this->N) {
            cerr << "Index out of range" << endl;
            exit(1);
        }
    }
public:
    Array(int n) {
        N = n;
        arr = new double [N];
    }
    
    Array() {
        N = 0;
        arr = NULL;
    }
    
    Array (const Array & source) { //конструктор копирование
        N = source.N;
        arr = new double [N];
        for (int i = 0; i < N; i++) {
            arr[i] = source.arr[i];
        }
    }
    
    ~Array() { //деструктор
        delete [] arr;
    }
    
    friend std::ostream& operator<<(std::ostream& out, const Array& arr) {
        for (int i = 0; i < arr.N; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        return out;
    }
    
    double& operator [] (int i) {
        check(i);
        return arr[i];
    }
    
    const double& operator [] (int i) const {
        check(i);
        return arr[i];
    }
};

class Matrix {
private:
    int num_rows;
    int num_columns;
    
    Array* matr;
    void check(int index) const {
        if (index >= this->num_rows) {
            cerr << "Index out of range" << endl;
            exit(1);
        }
    }
public:
    Matrix() {
        num_columns = 0;
        num_rows = 0;
        matr = NULL;
    }
    
    Matrix(int m, int n) {
        num_rows = m;
        num_columns = n;
        
        matr = new Array [m];
        for (int i = 0; i < m; i++)
            matr[i] = *new Array(n);
    }
    
    Matrix (const Matrix & source) { //конструктор копирования
        num_rows = source.num_rows;
        num_columns = source.num_columns;
        
        matr = new Array [source.num_rows];
        for (int i = 0; i < source.num_rows; i++) {
            matr[i] = *new Array(source.num_columns);
        }
        
        for (int i = 0; i < source.num_rows; i++) {
            for (int j = 0; j < source.num_columns; j++) {
                matr[i][j] = source[i][j];
            }
        }
    }
    
    bool operator==(const Matrix& other) const {
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_columns; j++) {
                if (matr[i][j] != other[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    
    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }
    
    friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
        for (int i = 0; i < matrix.num_rows; i++) {
            for (int j = 0; j < matrix.num_columns; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        return out;
    }
    
    // умножение матрицы на число
    Matrix& operator*=(const double x) {
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_columns; j++) {
                matr[i][j] *= x;
            }
        }
        return *this;
    }
    
    Array& operator [] (int i) {
        check(i);
        return matr[i];
    }
    
    // умножение матрицы на вектор
    Matrix& operator*=(const vector<double>& vec) {
        Matrix newMatr = Matrix(num_rows, 1);
        for (int i = 0; i < newMatr.num_rows; i++) {
            newMatr[i][0] = 0;
        }
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_columns; j++) {
                newMatr[i][0] += matr[i][j] * vec[j];
            }
        }
        *this = newMatr;
        return *this;
    }
    
    const Array& operator [] (int i) const {
        check(i);
        return matr[i];
    }
    
    ~Matrix () {
    }
    
    int get_rows_number() {
        return this->num_rows;
    }
    
    int get_columns_number() {
        return this->num_columns;
    }
};

const size_t rows = 5;
const size_t cols = 3;

int main(int argc, const char * argv[]) {
    
//    int m = 4, n = 5;
//    Matrix matr(m,n);
//
//    for (int i = 0; i < m; i++) {
//        for (int j = 0; j < n; j++) {
//            matr[i][j] = i + j;
//        }
//    }
//    cout << matr;
    
    checkGetSet();
    checkGetRowsColumns();
    checkMulVec();
    checkMulNumber();
    checkEqual();

    return 0;
}



////////////////////////////// Tests ////////////////////////////////
void checkEqual() {
    
    int m = arc4random() % 100;
    int n = arc4random() % 100;
    Matrix matr(m, n);
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matr[i][j] = arc4random() % 100;
        }
    }
    
    Matrix tmp = matr;
    
    check(tmp == matr);
    
    tmp *= 2;
    
    check(tmp != matr);
}

void checkMulNumber() {
    Matrix m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;
    
    m *= 10;
    
    check(m[0][0] == 10);
    check(m[0][1] == 20);
    check(m[0][2] == 30);
    check(m[1][0] == 40);
    check(m[1][1] == 50);
    check(m[1][2] == 60);

}

void checkMulVec() {
    Matrix m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;
    
    vector<double> vec = {2, 4, -1};
    
    m *= vec;
    
    check(m[0][0] = 7);
    check(m[1][0] = 22);
}

void checkGetRowsColumns() {
    int m = arc4random() % 100;
    int n = arc4random() % 100;
    Matrix matr(m, n);
    
    check(matr.get_rows_number() == m);
    check(matr.get_columns_number() == n);
}


void check(bool value) {
    if (!value)
        std::cout << "error" << std::endl;
}

void checkGetSet() {
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
}


