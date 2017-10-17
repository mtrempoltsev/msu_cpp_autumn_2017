#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <stdio.h>
#include "Matrix.cpp"
using namespace std;



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

    check(m.rows() == 2);
    check(m.columns() == 3);
}

void checkMul()
{
    Matrix m = Matrix(2, 2);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            m[i][j] = 2*i + j;
    vector <double> v;

    v.push_back(4.0);
    v.push_back(5.0);
    m *= v;
    check(m.rows() == 2);
    check(m.columns() == 1);
    check(m[0][0] == 5);
    check(m[1][0] == 23);

    m *= 2.5;
    check(m[0][0] == 12.5);
    check(m[1][0] == 57.5);
}

void checkEqual()
{
    Matrix m = Matrix(2, 2);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            m[i][j] = 2*i + j;

    Matrix n = Matrix(2, 2);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            n[i][j] = 2*i + j;

    check(n == m);
    n *= 5;
    check(n != m);

    vector <double> v;
    v.push_back(4.0);
    v.push_back(5.0);
    n = m;
    check(n == m);
    n *= v;
    check(n != m);
    m *= v;
    check(n == m);
}


int main()
{
    checkGetSet();
    checkMul();
    checkEqual();
    return 0;
}
