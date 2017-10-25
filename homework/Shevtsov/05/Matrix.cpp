#include <iostream>
#include <vector>
#include <cassert>
#include <assert.h>

using namespace std;

template <class T>
class Matrix {
private:
  size_t row_matrix;
  size_t col_matrix;
  vector<vector<T> > data_column;


  /// прокси-класс отвечающий за строки
  class MatrixRow {
  public:
    MatrixRow(const size_t size, typename vector<T>::iterator it_row):
                                  size_row(size), data_row(it_row) {};
    T& operator[](size_t row_index){
      if (row_index >= size_row){
        cerr << "Error: Index out of range" << endl;
      }
      return data_row[row_index];
    }
  private:
    const size_t size_row;
    typename vector<T>::iterator data_row;
  };
  ///


public:


  Matrix(size_t row, size_t column): row_matrix(row), col_matrix(column){
    data_column.resize(row_matrix); // длина вектора
    for (size_t i = 0; i < row_matrix; i++)
      data_column[i].resize(col_matrix);
  }


  Matrix (){
    row_matrix = 1;
    col_matrix = 1;
    data_column.resize(row_matrix); // длина вектора
    for (size_t i = 0; i < row_matrix; i++)
      data_column[i].resize(col_matrix);
    data_column[0][0] = 0;
  }

  ~Matrix() {
    this->Clear();
  }


  // присваивание
  MatrixRow operator[](const size_t column_index){
    if(column_index >= row_matrix){
      cerr << "Error: Index out of range" << endl;
    }
    return Matrix::MatrixRow(col_matrix, data_column[column_index].begin());
  }


  // методы:
  size_t Row(); // получение числа рядов
  size_t Column(); // Получение числа столбцов
  vector<T> operator*(const vector<T> v); // умножение справа    M * v = v_1, M - матрица,
                                          //v - вектор
  void operator*=(double number);
  bool operator==(const Matrix& M);
  bool operator!=(const Matrix& M);


  Matrix(const Matrix& M){ // copy-constructor
    row_matrix = M.row_matrix;
    col_matrix = M.col_matrix;
    data_column = M.data_column;
  }


  Matrix& operator=(const Matrix& M){ // copy
    if (this == &M)
      return *this;
    this->Clear();
    row_matrix = M.row_matrix;
    col_matrix = M.col_matrix;
    data_column = M.data_column;
    return *this;
  }


  Matrix(Matrix&& M) { // move-constructor
      row_matrix = M.row_matrix;
      col_matrix = M.col_matrix;
      data_column = M.data_column;
      M.Clear();
  }


  Matrix& operator=(Matrix&& M) { // move
      if (this == &M) {
          return *this;
      }
      //data_column.clear();
      this->Clear();
      row_matrix = M.row_matrix;
      col_matrix = M.col_matrix;
      data_column = M.data_column;
      M.Clear();
      return *this;
  }


  Matrix& operator*(double number){ // умножение матрицы на число
    for (size_t i = 0; i < row_matrix; i++)
      for (size_t j = 0; j < col_matrix; j++)
        data_column[i][j] = data_column[i][j]*number;
    return *this;
  }

  void PrintMatrix();
  void Clear();
};


template <class T>
size_t Matrix<T>::Row(){
  return row_matrix;
}


template <class T>
size_t Matrix<T>::Column(){
  return col_matrix;
}


template <class T>
void Matrix<T>::operator*=(double number){
  for (size_t i = 0; i < row_matrix; i++)
    for (size_t j = 0; j < col_matrix; j++)
      data_column[i][j] = data_column[i][j]*number;
}


//
//  (###)   (|)   ()
//  (   ) * (|) = () Матрица 2 на 3 умноженная на вектор размера 3 будет вектор размера 2
//          (|)
//


template <class T>
vector<T> Matrix<T>::operator*(const vector<T> v){
  if(v.size() != col_matrix)
    cerr << "Error: incorrect size of vector" << endl;
  vector<T> result(row_matrix);
  for (size_t i = 0; i < row_matrix; i++){
    double sum = 0;
    for (size_t j = 0; j < col_matrix; j++)
      sum = sum + data_column[i][j]*v[j];
    result[i] = sum;
  }
  return result;
}


template <class T>
bool Matrix<T>::operator==(const Matrix& M){
  if(row_matrix != M.row_matrix || col_matrix != M.col_matrix)
    cerr << "wrong size" << endl;

  for (size_t i=0; i < row_matrix; i++)
    for (size_t j = 0; j < col_matrix; j++ )
      if(data_column[i][j]!=M.data_column[i][j])
        return false;
  return true;
}


template <class T>
bool Matrix<T>::operator!=(const Matrix& M){
  return !(*this==M);
}


template <class T>
void Matrix<T>::Clear(){
  for (size_t i = 0; i < row_matrix; i++)
    for (size_t j = 0; j < col_matrix; j++)
      data_column[i][j] = 0;
}

template <class T>
void Matrix<T>::PrintMatrix(){
  for(size_t i = 0; i < row_matrix; i++)
    for (size_t j = 0; j < col_matrix; j++)
      cout << data_column[i][j] << endl;
}


void check(bool value)
{
    if (!value)
        std::cout << "error" << std::endl;
}

template <class T>
void checkGetSet()
{
    Matrix<T> m(2, 3);
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

template <class T>
void checkVectAndMult()
{
  Matrix<T> m(2, 3);
  m[0][0] = 1;
  m[0][1] = 2;
  m[0][2] = 3;
  m[1][0] = 4;
  m[1][1] = 5;
  m[1][2] = 6;

  //(1 2 3) (1)  (14)
  //(4 5 6)*(2) =(32)
  //        (3)

  vector<T> v = { 1, 2, 3 };
  v = m*v;
  check(v[0] == 14);
  check(v[1] == 32);
  m*=2;
  Matrix<T> m2 = m*2;
  check(m == m2);

}

template <class T>
void CopyMove()
{
  Matrix<T> m(2, 3);
  m[0][0] = 1;
  m[0][1] = 2;
  m[0][2] = 3;
  m[1][0] = 4;
  m[1][1] = 5;
  m[1][2] = 6;

  Matrix<T> m2 = m*2;
  Matrix<T> m4(m2); // copy-constructor
  Matrix<T> m3;
  m3 = std::move(m);
  check(m2 == m3);
  check(m4 == m2);
}


int main() {
  checkGetSet<int>();
  checkVectAndMult<double>();
  CopyMove<int>();
  return 0;
}
