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

    check(m.rows() == 2);
    check(m.columns() == 3);
}

template <typename T>
void checkTemplate()
{
    Matrix<T> m(4, 10);
    m[3][5] = 32;
    m[1][7] = 62;
    check(m.rows() == 4);
    check(m.columns() == 10);

    Matrix<T> n = m;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 10; ++j)
            check(m[i][j] == n[i][j]);

    Matrix<T> c(0, 0);
    c = m;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 10; ++j)
            check(m[i][j] == c[i][j]);

    c = c;
    check(c[3][5] == 32);
    Matrix<T> d = std::move(c);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 10; ++j)
            check(d[i][j] == m[i][j]);



    d = std::move(n);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 10; ++j)
            check(d[i][j] == m[i][j]);
}

void checkMul()
{
    Matrix<double> m(2, 2);
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
    Matrix<double> m(2, 2);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            m[i][j] = 2*i + j;

    Matrix<double> n(2, 2);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            n[i][j] = 2*i + j;

    check(n == m);
    //m.print(1, "% 6.2lf ");
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
   // m.print(1, "% 6.2lf ");
}


int main()
{
    checkGetSet();
    checkMul();
    checkEqual();
    checkTemplate<int>();
    checkTemplate<char>();
    checkTemplate<double>();
    return 0;
}
