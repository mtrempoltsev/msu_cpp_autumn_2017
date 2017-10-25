#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

template <typename T>
class Matrix {
    
public:
    Matrix(int rows, int cols);
    int get_rows();
    int get_cols();
    vector<T>&operator[](int row);
    vector<T> operator*(vector<T> multiplier);
    Matrix operator*(T multiplier);
    bool operator==(Matrix &right);
    bool operator!=(Matrix &right);
    
    Matrix(const Matrix& M);
    Matrix& operator=(const Matrix& M);
    
    Matrix(Matrix&& M);
    Matrix& operator=(Matrix&& M);
    
private:
    vector<vector<T>> elem;
    int number_of_cols;
    int number_of_rows;
};

template <typename T>
Matrix<T>::Matrix(int rows, int cols)
{
    elem.resize(rows);
    for (int i = 0; i < rows; i++)
        elem[i].resize(cols);
    number_of_cols = cols;
    number_of_rows = rows;
}

template <typename T>
int Matrix<T>::get_rows()
{
    return number_of_rows;
}

template <typename T>
int Matrix<T>::get_cols()
{
    return number_of_cols;
}

template <typename T>
vector<T>& Matrix<T>::operator[](int row)
{
    if (row >= number_of_rows)
        assert(!"index out of range");
    return elem[row];
}

template <typename T>
vector<T> Matrix<T>::operator*(vector<T> multiplier)
{
    if (number_of_cols != multiplier.size())
        assert(!"index out of range");
    vector<T> result(number_of_rows);
    for (int i = 0; i < number_of_rows; i++)
        for (int j = 0; j <number_of_cols; j++)
            result[i] += elem[i][j] * multiplier[j];
    return result;
}


template <typename T>
Matrix<T> Matrix<T>::operator*(T multiplier)
{
    Matrix result(number_of_rows, number_of_cols);
    for (int i = 0; i < number_of_rows; i++)
        for (int j = 0; j <number_of_cols; j++)
            result[i][j] = elem[i][j] * multiplier;
    return result;
}

template <typename T>
bool Matrix<T>::operator==(Matrix<T> &right)
{
    if (number_of_rows != right.get_rows() || number_of_cols != right.get_cols())
        return 0;
    for (int i = 0; i < number_of_rows; i++)
        for (int j = 0; j <number_of_cols; j++)
            if (elem[i][j] != right[i][j])
                return 0;
    return 1;
}


template <typename T>
Matrix<T>::Matrix(const Matrix& M) //конструктор копирования
{
    number_of_cols = M.number_of_cols;
    number_of_rows = M.number_of_rows;
    elem = M.elem;
}

template <typename T> //оператор копирования
Matrix<T>& Matrix<T>:: operator=(const Matrix& M)
{
    if (this == &M)
        return *this;
    this->elem.clear();
    number_of_cols = M.number_of_cols;
    number_of_rows = M.number_of_rows;
    elem = M.elem;
    return *this;
}


template <typename T>
Matrix<T>::Matrix(Matrix&& M) //конструктор перемещения
{
    number_of_cols = M.number_of_cols;
    number_of_rows = M.number_of_rows;
    elem = M.elem;
    
    M.elem.clear();
    M.number_of_cols = 0;
    M.number_of_rows = 0;
}


template <typename T>
Matrix<T>& Matrix<T>:: operator=(Matrix&& M) //оператор перемещения
{
    if (this == &M) {
        return *this;
    }
    number_of_cols = M.number_of_cols;
    number_of_rows = M.number_of_rows;
    elem = M.elem;
    
    M.elem.clear();
    M.number_of_cols = 0;
    M.number_of_rows = 0;
    return *this;
}


template <typename T>
bool Matrix<T>::operator!=(Matrix &right)
{
    return !(*this == right);
}

int numb_of_err;
void check(bool value)
{
    numb_of_err++;
    if (!value)
        cout << "error " << numb_of_err << endl;;
}

void checkGetSet()
{
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
    
    Matrix<int> m2(2, 3);
    m2[0][0] = 1;
    m2[0][1] = 2;
    m2[0][2] = 3;
    m2[1][0] = 4;
    m2[1][1] = 5;
    m2[1][2] = 6;
    
    check(m2[0][0] == 1);
    check(m2[0][1] == 2);
    check(m2[0][2] == 3);
    check(m2[1][0] == 4);
    check(m2[1][1] == 5);
    check(m2[1][2] == 6);
    
    m2[1][2] = 100;
    
    check(m2[1][2] == 100);
}

void checkGetRowsCols()
{
    Matrix<double> m(0, 0);
    check(m.get_rows() == 0);
    check(m.get_cols() == 0);
    
    Matrix<double> m1(3, 4);
    check(m1.get_rows() == 3);
    check(m1.get_cols() == 4);
}

void checkMul()
{
    Matrix<double> m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    vector<double> v{0, 1, 2};
    
    vector<double> mul1 = m*v;
    Matrix<double> mul2 = m*2;
    
    check(mul1[0] == 8);
    check(mul1[1] == 17);
    
    check(mul2[0][0] == 2);
    check(mul2[0][1] == 4);
    check(mul2[0][2] == 6);
    check(mul2[1][0] == 8);
    check(mul2[1][1] == 10);
    check(mul2[1][2] == 12);
}

void checkComp()
{
    Matrix<double> m1(2, 3);
    Matrix<double> m2(3, 2);
    
    check(!(m1 == m2));
    check(m1 != m2);
    
    Matrix<double> m3(2, 2);
    m3[0][0] = 1;
    m3[0][1] = 2;
    m3[1][0] = 3;
    m3[1][1] = 4;
    
    Matrix<double> m4(2, 2);
    m4[0][0] = 1;
    m4[0][1] = 2;
    m4[1][0] = 3;
    m4[1][1] = 4;
    
    check(m3 == m4);
    check(!(m3 != m4));
    
    m3[0][0] = 0;
    
    check(m3 != m4);
    check(!(m3 == m4));
}


void checkMoveConstructor()
{
    Matrix<double> m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;
    Matrix<double> m2 = m;
    Matrix<double> m1 = move(m);
    check(m1 != m);
    check (m != m2);
    check (m1 == m2);
    
}

void checkMoveOperator()
{
    Matrix<double> m1(1,1);
    m1[0][0] = 1;
    Matrix<double> m2 = m1;
    Matrix<double> m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;
    m = move(m1);
    check(m != m1);
    check(m1 != m2);
    check(m == m2);
}

void checkCopyConstructor()
{
    Matrix<double> m2(1,1);
    m2[0][0] = 1;
    Matrix<double> m1 = m2;
    check(m1 == m2);
}

void checkCopyOperator()
{
    Matrix<double> m1(2, 3);
    Matrix<double> m2(1,1);
    m2[0][0] = 1;
    m1 = m2;
    check(m1 == m2);
}

int main(int argc, const char * argv[])
{
    checkGetSet();
    checkGetRowsCols();
    checkMul();
    checkComp();
    
    checkMoveConstructor();
    checkMoveOperator();
    checkCopyOperator();
    checkCopyConstructor();
    return 0;
}


