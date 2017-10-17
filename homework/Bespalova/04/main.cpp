#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

class Matrix {
public:
    Matrix(int rows, int cols);
    int get_rows();
    int get_cols();
    vector<double>&operator[](int row);
    vector<double> operator*(vector<double> multiplier);
    Matrix operator*(double multiplier);
    bool operator==(Matrix &right);
    bool operator!=(Matrix &right);
    
private:
    vector< vector<double> > elem;
    int number_of_cols;
    int number_of_rows;
};


Matrix::Matrix(int rows, int cols)
{
    elem.resize(rows);
    for (int i = 0; i < rows; i++)
        elem[i].resize(cols);
    number_of_cols = cols;
    number_of_rows = rows;
}

int Matrix::get_rows()
{
    return number_of_rows;
}

int Matrix::get_cols()
{
    return number_of_cols;
}

vector<double>& Matrix::operator[](int row)
{
    if (row >= number_of_rows)
        assert(!"index out of range");
    return elem[row];
}


vector<double> Matrix::operator*(vector<double> multiplier)
{
    if (number_of_cols != multiplier.size())
        assert(!"index out of range");
    vector<double> result(number_of_rows);
    for (int i = 0; i < number_of_rows; i++)
        for (int j = 0; j <number_of_cols; j++)
            result[i] += elem[i][j] * multiplier[j];
    return result;
}

Matrix Matrix::operator*(double multiplier)
{
    Matrix result(number_of_rows, number_of_cols);
    for (int i = 0; i < number_of_rows; i++)
        for (int j = 0; j <number_of_cols; j++)
            result[i][j] = elem[i][j] * multiplier;
    return result;
}

bool Matrix::operator==(Matrix &right)
{
    if (number_of_rows != right.get_rows() || number_of_cols != right.get_cols())
        return 0;
    for (int i = 0; i < number_of_rows; i++)
        for (int j = 0; j <number_of_cols; j++)
            if (elem[i][j] != right[i][j])
                return 0;
    return 1;
}

bool Matrix::operator!=(Matrix &right)
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

void checkGetRowsCols()
{
    Matrix m(0, 0);
    check(m.get_rows() == 0);
    check(m.get_cols() == 0);
    
    Matrix m1(3, 4);
    check(m1.get_rows() == 3);
    check(m1.get_cols() == 4);
}

void checkMul()
{
    Matrix m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    vector<double> v{0, 1, 2};
    
    vector<double> mul1 = m*v;
    Matrix mul2 = m*2;
    
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
    Matrix m1(2, 3);
    Matrix m2(3, 2);
    
    check(!(m1 == m2));
    check(m1 != m2);
    
    Matrix m3(2, 2);
    m3[0][0] = 1;
    m3[0][1] = 2;
    m3[1][0] = 3;
    m3[1][1] = 4;
    
    Matrix m4(2, 2);
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

int main(int argc, const char * argv[])
{
    checkGetSet();
    checkGetRowsCols();
    checkMul();
    checkComp();
    return 0;
}


