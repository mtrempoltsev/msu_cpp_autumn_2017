//
//  main.cpp
//  calculation
//
//  Created by Артем Кашипов on 10.12.17.
//  Copyright © 2017 Артем Кашипов. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <assert.h>

using namespace std;

template<class T>
class Row{
private:
    int len;
    T* vec;
public:
    Row(){
        len = 1;
        vec = new T[len];
    }
    Row(T* buf, int len_){
        vec=buf;
        len = len_;
    }
    //обращение к элементу в строке
    T& operator[](const int& j){
        if ((j>=len)||(j<0)){
            assert(!"Index of matrix row out of range (cols)");
        }
        return vec[j];
    }
    
};


template<class T>
class Matrix
{
private:
    int rows;
    int cols;
    Row<T> row;
    T *matrix;
public:
    //конструктор
    Matrix(int rows_, int cols_)
    {
        if ((rows_<1)&&(cols_<1))
        {
            assert(!"Invalid size of matrix");
        }
        rows=rows_;
        cols=cols_;
        matrix = new T[rows*cols];
    }
    //конструктор копирования
    Matrix(const Matrix& matrix_)
    {
        cols = matrix_.cols;
        rows = matrix_.rows;
        matrix = new T[rows*cols];
        if (typeid(matrix_.matrix)!=typeid(matrix))
            cout << "Choice other type, please" << endl;
        else {
            for (int i=0;i<rows*cols;i++)
            {
                matrix[i]=matrix_.matrix[i];
            }
        }
    }
    //конструктор перемещения
    Matrix(Matrix&& matrix_): cols(std::move(matrix_.cols)) , rows(std::move(matrix_.rows)), matrix(std::move(matrix_.matrix))
    {
        if (typeid(matrix_.matrix)!=typeid(matrix))
            cout << "Choice other type, please" << endl;
        else
            matrix_.matrix = nullptr;
    }
    //деструктор
    ~Matrix()
    {
        delete[] matrix;
    }
    //обращение к строке
    Row<T>& operator[](const int& i){
        if ((i>=rows)&&(i<0)){
            assert(!"Index of matrix out of range (rows)");
        }
        row = Row<T>(matrix + (i*cols), cols);
        return row;
    }
    //умножение матрицы на число
    Matrix& operator*=(const double& num){
        if (typeid(T)==typeid(int) || typeid(T)==typeid(double))
            for (int i=0;i<rows*cols;i++){
                matrix[i]*=num;
            }
        return *this;
    }
    
    // умножение на вектор матрицу
    Matrix& operator*=(const vector<double>& vec){
        if (cols!=vec.size())
            assert(!"Matrix and vector aren't compatable");
        if (typeid(T)==typeid(int) || typeid(T)==typeid(double)){

            double* vec_new = new double[rows];
            for(int i=0;i<rows;i++)
                vec_new[i] = 0;
            for (int i=0;i<rows;i++)
                for (int j=0;j<cols;j++)
                    vec_new[i]+=matrix[i*cols + j]*vec[j];
            delete[] matrix;
            cols = 1;
            matrix = new T[rows];
            for (int i=0;i<rows;i++)
                matrix[i] = vec_new[i];
            delete[] vec_new;
            }
        return *this;
    }
    // опреатор приравнивание
    Matrix& operator=(const Matrix& matrix_){
        if (this == &matrix_)
            return *this;
        if (typeid(matrix_.matrix)!=typeid(matrix)){
            cout << "Choice other type, please" << endl;
            return *this;
        }

        delete[] matrix;
        cols = matrix_.cols;
        rows = matrix_.rows;
        double* matrix = new double[rows*cols];
        for (int i=0;i<cols*rows;i++)
            matrix[i]=matrix_.matrix[i];
        return *this;
    }
    //оператор перемещения
    Matrix& operator=(Matrix&& matrix_){
        if (typeid(matrix_.matrix)!=typeid(matrix)){
            cout << "Choice other type, please" << endl;
            return *this;
        }
        delete[] matrix;
        cols = std::move(matrix_.cols);
        rows = std::move(matrix_.rows);
        matrix = std::move(matrix_.matrix);
        matrix_.matrix = nullptr;
        return *this;
    }
    // оператор сравнения
    bool operator==(const Matrix& matrix_){
        if ((cols!=matrix_.cols)||(rows!=matrix_.rows)){
            return false;
        }
        for (int i=0;i<cols*rows;i++)
            if(matrix[i]!=matrix_.matrix[i]){
                return false;
            }
        return true;
    }
    // проверка на неравенство
    bool operator!= (const Matrix& matrix_){
        return !(*this == matrix_);
    }
    int sizeRows(){
        return rows;
    }
    int sizeCols(){
        return cols;
    }
    T* mat(){
        return matrix;
    }
    void print(){
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                cout << matrix[j + i*cols] << "  ";
            }
            cout << endl;
        }
    }
};



bool checkMatrixCreation(){
    Matrix<double> m(2, 2);
    for (int i = 0; i < m.sizeRows(); i++){
        for (int j = 0; j < m.sizeCols(); j++){
            m[i][j] = i*m.sizeRows() + j;
            
        }
    }
    int columns = m.sizeCols();
    int rows = m.sizeRows();
    if ((m[0][0]==0)&&(m[0][1]==1)&&(m[1][0]==2)&&(m[1][1]==3)&&(columns==2)&&(rows==2)){
        return true;
    }
    else{
        return false;
    }
}
bool checkMatrixMultiplyByNumber(){
    Matrix<double> m(2, 2);
    for (int i = 0; i < m.sizeRows(); i++){
        for (int j = 0; j < m.sizeCols(); j++){
            m[i][j] = i*m.sizeRows() + j;
        }
    }
    m*=2;
    if ((m[0][0]==0)&&(m[0][1]==2)&&(m[1][0]==4)&&(m[1][1]==6)){
        return true;
    }
    else{
        return false;
    }
}
bool checkMatrixMultiplyByVector(){
    Matrix<double> m(2, 3);
    for (int i = 0; i < m.sizeRows(); i++){
        for (int j = 0; j < m.sizeCols(); j++){
            m[i][j] = i*m.sizeCols() + j;
        }
    }
    vector<double> v(3);
    v[0]=0;
    v[1] = 1;
    v[2] = 0;
    m*=v;
    if ((m[0][0]==1)&&(m[1][0]==4)){
        return true;
    }
    else{
        return false;
    }
}
bool checkEqualMatrix(){
    Matrix<double> m1(2,2);
    Matrix<double> m2(2,2);
    for (int i = 0; i < m1.sizeRows(); i++){
        for (int j = 0; j < m1.sizeCols(); j++){
            m1[i][j] = i*m1.sizeRows() + j;
            m2[i][j] = i*m2.sizeRows() + j;
        }
    }
    if (m1==m2){
        return true;
    }
    else{
        return false;
    }
}
bool checkMoveCopy(){
    Matrix<double> m1(2,2);
    for (int i = 0; i < m1.sizeRows(); i++)
        for (int j = 0; j < m1.sizeCols(); j++)
            m1[i][j] = i*m1.sizeRows() + j;
    Matrix<double> m2 = std::move(m1);
    for (int i = 0; i < m2.sizeRows(); i++)
        for (int j = 0; j < m2.sizeCols(); j++)
            if (m2[i][j]!=i*m2.sizeRows() + j)
                return false;
    if (m1.mat()!=nullptr)
        return false;
    else
        return true;
}

bool checkMove(){
    Matrix<double> m1(2,2);
    Matrix<double> m2(2,2);
    for (int i = 0; i < m1.sizeRows(); i++)
        for (int j = 0; j < m1.sizeCols(); j++)
            m1[i][j] = i*m1.sizeRows() + j;
    m2 = move(m1);
    for (int i = 0; i < m2.sizeRows(); i++)
        for (int j = 0; j < m2.sizeCols(); j++)
            if (m2[i][j]!=i*m2.sizeRows() + j)
                return false;
    if (m1.mat()!=nullptr)
        return false;
    else
        return true;
}

bool checkTemplate(){
    Matrix<int> m1(2,2);
    Matrix<double> m2(2,2);
    Matrix<char> m3(2,2);
    for (int i = 0; i < m1.sizeRows(); i++)
        for (int j = 0; j < m1.sizeCols(); j++){
            m1[i][j] = i*m1.sizeRows() + j;
            m2[i][j] = i*m2.sizeRows() + j+0.5;
            m3[i][j] = '0'+(i+1)*(j+1);
        }
//    m3.print();
//    cout << typeid(m1.mat()).name() << typeid(m2.mat()).name() << typeid(m3.mat()).name() << endl;
    if (!strcmp(typeid(m1.mat()).name(),"Pi") && !strcmp(typeid(m2.mat()).name(),"Pd") && !strcmp(typeid(m3.mat()).name(),"Pc"))
        return true;
    else
        return false;
}
    
int main(){
    if (checkMoveCopy()){
        cout<<"#1 OK"<<endl;
    }
    if (checkMove()){
        cout<<"#1 OK"<<endl;
    }
    if (checkTemplate()){
        cout<<"#1 OK"<<endl;
    }
}
