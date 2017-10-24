//
//  main.cpp
//  Task5
//
//  Created by Максим on 24.10.17.
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
void checkConstructs();


//прокси-класс для рядов матрицы Matrix
template <class T>  class Array {
private:
    T *arr;
    int N;
    //проверка на выход за границы массива
    void check(int index) const {
        if (index >= this->N) {
            cerr << "Index out of range" << endl;
        }
    }
public:
    Array<T>(int n) {
        N = n;
        arr = new T [N];
    }
    
    Array<T>() {
        N = 0;
        arr = NULL;
    }
    
    Array<T>(const Array<T>& source) { //конструктор копирование
        N = source.N;
        arr = new T [N];
        copy(source.arr, source.arr + N, arr);
    }
    
    Array<T>& operator=(const Array<T>& source) { //оператор копирования
        if (this == &source) {
            return *this;
        }
        this->~Array<T>();
        arr = new T [source.N];
        N = source.N;
        copy(source.arr, source.arr + N, arr);
        return *this;
    }
    
    Array<T>(Array<T>&& moved) { //конструктор перемещения
        arr = moved.arr;
        N = moved.N;
        
        moved.arr = nullptr;
    }
    
    Array<T>& operator=(Array<T>&& moved) { //оператор перемещения
    
        if (this == &moved) {
            return *this;
        }
        this->~Array<T>();
        
        arr = moved.arr;
        N = moved.N;
        moved.arr = nullptr;
        return *this;
    }
    
    ~Array<T>() { //деструктор
        delete [] arr;
    }
    
    friend std::ostream& operator<<(std::ostream& out, const Array<T>& arr) {
        for (int i = 0; i < arr.N; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        return out;
    }
    
    T& operator [] (int i) {
        check(i);
        return arr[i];
    }
    
    const T& operator [] (int i) const {
        check(i);
        return arr[i];
    }
};

template <class T> class Matrix {
private:
    int num_rows;
    int num_columns;
    
    Array<T>* matr;
    void check(int index) const {
        if (index >= this->num_rows) {
            cerr << "Index out of range" << endl;
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
        
        matr = new Array<T> [m];
        for (int i = 0; i < m; i++)
            matr[i] = *new Array<T>(n);
    }
    
    Matrix(const Matrix & source) { //конструктор копирования
        num_rows = source.num_rows;
        num_columns = source.num_columns;
        
        matr = new Array<T> [source.num_rows];
        for (int i = 0; i < source.num_rows; i++) {
            matr[i] = source[i];
        }
    }
    
    Matrix& operator=(const Matrix& source) { //оператор копирования
        if (this == &source) {
            return *this;
        }
        this->~Matrix();
        
        num_rows = source.num_rows;
        num_columns = source.num_columns;
        
        matr = new Array<T> [source.num_rows];
        for (int i = 0; i < source.num_rows; i++) {
            matr[i] = source[i];
        }
        return *this;
    }
    
    Matrix(Matrix&& moved) { //конструктор перемещения
        matr = new Array<T> [moved.num_rows];
        for (int i = 0; i < moved.num_rows; i++) {
            matr[i] = std::move(moved[i]);
            moved[i].~Array<T>();
        }
        num_rows = moved.num_rows;
        num_columns = moved.num_columns;
    }
    
    Matrix& operator=(Matrix&& moved) { //оператор перемещения
        
        if (this == &moved) {
            return *this;
        }
        this->~Matrix();
        
        matr = new Array<T> [moved.num_rows];
        for (int i = 0; i < moved.num_rows; i++) {
            matr[i] = std::move(moved[i]);
            moved[i].~Array<T>();
        }

        num_rows = moved.num_rows;
        num_columns = moved.num_columns;

        return *this;
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
    Matrix& operator*=(const T x) {
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_columns; j++) {
                matr[i][j] *= x;
            }
        }
        return *this;
    }
    
    Array<T>& operator [] (int i) {
        check(i);
        return matr[i];
    }
    
    // умножение матрицы на вектор
    Matrix& operator*=(const vector<T>& vec) {
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
    
    const Array<T>& operator [] (int i) const {
        check(i);
        return matr[i];
    }
    
    ~Matrix () {

        for (int i = 0; i < num_rows; i++) {
            matr[i].~Array<T>();
        }
    }
    
    int get_rows_number() {
        return this->num_rows;
    }
    
    int get_columns_number() {
        return this->num_columns;
    }
};


int main(int argc, const char * argv[]) {
    
    checkGetSet();
    checkGetRowsColumns();
    checkMulVec();
    checkMulNumber();
    checkEqual();
    checkConstructs();
    cout << "All tests completed" << endl;

    return 0;
}



////////////////////////////// Tests ////////////////////////////////


void checkConstructs() {
    // Копирующий конструктор
    Matrix<double> a1 = Matrix<double>(2,2);
    a1[0][0] = 0;
    a1[0][1] = 1;
    a1[1][0] = 2;
    a1[1][1] = 3;

    Matrix<double> a2 = a1;
    check(a2[0][0] == 0);
    check(a2[0][1] == 1);
    check(a2[1][0] == 2);
    check(a2[1][1] == 3);
    
    
    // Оператор копирования
    Matrix<double> a3 = Matrix<double>(2,2);
    a3[0][0] = 0;
    a3[0][1] = 1;
    a3[1][0] = 2;
    a3[1][1] = 3;
    
    Matrix<double> a4;
    a4 = a3;
    check(a4[0][0] == 0);
    check(a4[0][1] == 1);
    check(a4[1][0] == 2);
    check(a4[1][1] == 3);
    
    Array<double> arr1 = Array<double>(2);
    arr1[0] = 10;
    arr1[1] = 20;
    
    Array<double> arr2 = std::move(arr1);
    check(arr2[0] == 10);
    check(arr2[1] == 20);
    
    Array<double> arr3 = Array<double>(2);
    arr3[0] = 100;
    arr3[1] = 200;
    
    Array<double> arr4 = Array<double>(2);
    arr4[0] = 300;
    arr4[1] = 400;
    
    arr4 = std::move(arr3);
    check(arr4[0] == 100);
    check(arr4[1] == 200);
    
    // Перемещающий конструктор
    Matrix<double> a5 = Matrix<double>(2,2);
    a5[0][0] = 0;
    a5[0][1] = 1;
    a5[1][0] = 2;
    a5[1][1] = 3;

    Matrix<double> a6 = std::move(a5);
    
    check(a6[0][0] == 0);
    check(a6[0][1] == 1);
    check(a6[1][0] == 2);
    check(a6[1][1] == 3);


    // Оператор перемещения
    Matrix<double> a7 = Matrix<double>(2,2);
    a7[0][0] = 0;
    a7[0][1] = 1;
    a7[1][0] = 2;
    a7[1][1] = 3;
    Matrix<double> a8 = Matrix<double>(2,2);
    a8[0][0] = 4;
    a8[0][1] = 5;
    a8[1][0] = 6;
    a8[1][1] = 7;


    a8 = std::move(a7);

    check(a8[0][0] == 0);
    check(a8[0][1] == 1);
    check(a8[1][0] == 2);
    check(a8[1][1] == 3);
}

void checkEqual() {
    
    int m = arc4random() % 100;
    int n = arc4random() % 100;
    Matrix<double> matr(m, n);
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matr[i][j] = arc4random() % 100;
        }
    }
    
    Matrix<double> tmp = matr;
    
    check(tmp == matr);
    
    tmp *= 2;
    
    check(tmp != matr);
}

void checkMulNumber() {
    Matrix<double> m(2, 3);
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
    Matrix<double> m(2, 3);
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
    Matrix<double> matr(m, n);
    
    check(matr.get_rows_number() == m);
    check(matr.get_columns_number() == n);
}


void check(bool value) {
    if (!value)
        std::cout << "error" << std::endl;
}

void checkGetSet() {
    Matrix<double> m(2, 3);
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



