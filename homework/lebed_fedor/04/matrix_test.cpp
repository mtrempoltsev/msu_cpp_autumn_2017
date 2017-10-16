#include <iostream>
#include <cassert>
#include <vector>
#include "matrix.cpp"

#define check(expr) check_(expr, __LINE__, __func__)
void check_(bool value, int line, const char *func_name)
{
    if (!value) {
        std::cout << "Error " << func_name << ":" << line << endl;
    }
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

void checkRowsColsCount()
{
    Matrix m(0, 0);
    check(m.rows() == 0);
    check(m.cols() == 0);

    Matrix n(10, 20);
    check(n.rows() == 10);
    check(n.cols() == 20);
}

void checkMulNew()
{
    Matrix m(3, 3);
    m[0][0] = 1;
    m[1][1] = 2;
    m[2][2] = 4;

    vector<double> v{4, 2, 1};
    
    Matrix vector_mul = m*v;
    Matrix scalar_mul = m*3;

    for (size_t i  = 0; i < m.rows(); i++) {
        check(vector_mul[i][0] == 4);
        check(scalar_mul[i][i] == 3*m[i][i]);
    }
}

void checkVectorMulSelf()
{
    Matrix m(3, 3);
    m[0][0] = 1;
    m[1][1] = 2;
    m[2][2] = 4;

    vector<double> v{4, 2, 1};
    m *= v;
    
    for (size_t i  = 0; i < m.rows(); i++) {
        check(m[i][0] == 4);
    }
}

void checkScalarMulSelf()
{
    Matrix m(3, 3);
    m[0][0] = 1;
    m[1][1] = 2;
    m[2][2] = 3;

    m *= 3;
    
    for (size_t i  = 0; i < m.rows(); i++) {
        check(m[i][i] == 3*(i+1));
    }   
}

void checkComp()
{
    Matrix m1(2, 3);
    Matrix m2(3, 2);

    check(!(m1 == m2));
    check(m1 != m2);

    Matrix m3(2, 3);
    Matrix m4(2, 3);
    for (size_t i = 0; i < m1.rows(); i++) {
        for (size_t j = 0; j < m1.cols(); j++) {
            m1[i][j] = i - j;
            m3[i][j] = i + j;
            m4[i][j] = i + j;
        }
    }
    check(m1 != m3);
    check(!(m1 == m3));
    check(m1 != m4);
    check(!(m1 == m4));
    check(m3 == m4);
    check(!(m3 != m4));
}

int main()
{
    checkGetSet();
    checkRowsColsCount();
    checkMulNew();
    checkVectorMulSelf();
    checkScalarMulSelf();
    checkComp();
}
