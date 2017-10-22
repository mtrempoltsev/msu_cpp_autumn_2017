#include <iostream>
#include <vector>
#include <cassert>
#include <assert.h>

using namespace std;

class Matrix {
private:
  const size_t row_matrix;
  const size_t col_matrix;
  vector<vector<double> > data_column;
  /// прокси-класс отвечающий за строки
  class MatrixRow {
  public:
    MatrixRow(const size_t size, vector<double>::iterator it_row): size_row(size), data_row(it_row) {};
    double& operator[](size_t row_index){
      if (row_index >= size_row){
        assert(!"Error: Index out of range");
      }
      return data_row[row_index];
    }
  private:
    const size_t size_row;
    vector<double>::iterator data_row;
  };
  ///
public:
  Matrix(size_t row, size_t column): row_matrix(row), col_matrix(column){
    data_column.resize(row_matrix); // длина вектора
    for (size_t i = 0; i < row_matrix; i++)
      data_column[i].resize(col_matrix);
  }
  // присваивание
  MatrixRow operator[](const size_t column_index){
    if(column_index >= row_matrix){
      assert(!"Error: Index out of range");
    }
    return Matrix::MatrixRow(col_matrix, data_column[column_index].begin());
  }

  // методы:
  size_t Row(); // получение числа рядов
  size_t Column(); // Получение числа столбцов
  Matrix operator*(double number); // умножение матрицы на число
  vector<double> operator*(const vector<double> v); // умножение справа    M * v = v_1, M - матрица, v - вектор
  //void operator*=(const vector<double> v); - так не получится, так как происходит отождествление матрицы вектору
  void operator*=(double number);
  bool operator==(const Matrix& M);
  bool operator!=(const Matrix& M);
};

size_t Matrix::Row(){
  return row_matrix;
}

size_t Matrix::Column(){
  return col_matrix;
}

Matrix Matrix::operator*(double number){
  // создадим новую матицу которой будет присвоена прошлая матица с домноженными на число значениями
  Matrix result(row_matrix, col_matrix);
  for (size_t i = 0; i < row_matrix; i++)
    for (size_t j = 0; j < col_matrix; j++)
      result[i][j] = data_column[i][j]*number;
  return result;
}


void Matrix::operator*=(double number){
  for (size_t i = 0; i < row_matrix; i++)
    for (size_t j = 0; j < col_matrix; j++)
      data_column[i][j] = data_column[i][j]*number;
}
//
//  (###)   (|)   ()
//  (   ) * (|) = () Матрица 2 на 3 умноженная на вектор размера 3 будет вектор размера 2
//          (|)
//
vector<double> Matrix::operator*(const vector<double> v){
  if(v.size() != col_matrix)
    assert(!"Error: incorrect size of vector");
  vector<double> result(row_matrix);
  for (size_t i = 0; i < row_matrix; i++){
    double sum = 0;
    for (size_t j = 0; j < col_matrix; j++)
      sum = sum + data_column[i][j]*v[j];
    result[i] = sum;
  }
  return result;
}

bool Matrix::operator==(const Matrix& M){
  if(row_matrix != M.row_matrix || col_matrix != M.col_matrix)
    assert(!"wrong size");

  for (size_t i=0; i < row_matrix; i++)
    for (size_t j = 0; j < col_matrix; j++ )
      if(data_column[i][j]!=M.data_column[i][j])
        return false;
  return true;
}

bool Matrix::operator!=(const Matrix& M){
  return !(*this==M);
}

void check(bool value)
{
    if (!value)
        std::cout << "error" << std::endl;
}

void checkGetSet()
{
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

void checkVectAndMult()
{
  Matrix m(2, 3);
  m[0][0] = 1;
  m[0][1] = 2;
  m[0][2] = 3;
  m[1][0] = 4;
  m[1][1] = 5;
  m[1][2] = 6;

  //(1 2 3) (1)  (14)
  //(4 5 6)*(2) =(32)
  //        (3)

  vector<double> v = { 1, 2, 3 };
  v = m*v;
  check(v[0] == 14);
  check(v[1] == 32);

  Matrix m2 = m*2;
  m*=2;
  check(m2 == m);

}

int main() {
  checkGetSet();
  checkVectAndMult();
  return 0;
}
