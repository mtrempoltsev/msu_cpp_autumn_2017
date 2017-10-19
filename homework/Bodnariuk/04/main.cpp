// Vasilii Bodnariuk

#include <iostream>
#include <string>

#include "matrix.hpp"

using namespace std;

void check(bool value)
{
    if (!value)
        std::cout << "error" << std::endl;
}


int main()
{
    Matrix m1(2, 3);
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[0][2] = 3;
    m1[1][0] = 4;
    m1[1][1] = 5;
    m1[1][2] = 6;

    check(m1[0][0] == 1);
    check(m1[0][1] == 2);
    check(m1[0][2] == 3);
    check(m1[1][0] == 4);
    check(m1[1][1] == 5);
    check(m1[1][2] == 6);



    Matrix m2(2, 3);
    m2[0][0] = -1;
    m2[0][1] = -2;
    m2[0][2] = -3;
    m2[1][0] = -4;
    m2[1][1] = -5;
    m2[1][2] = -6;
    m2 *= -1;

    // std::cout << m2[0][0] << '\n';

    check(m2[0][0] == 1);
    check(m2[0][1] == 2);
    check(m2[0][2] == 3);
    check(m2[1][0] == 4);
    check(m2[1][1] == 5);
    check(m2[1][2] == 6);

    check(m1 == m2);

    m2[1][2] = 100;
    check(m2[1][2] == 100);

    Matrix m3(3, 1);
    m3[0][0] = 1;
    m3[1][0] = 2;
    m3[2][0] = 3;

    vector<double> v1 = {11, 7, 5};

    m3 *= v1;

    check(m3[0][0] == 11);
    check(m3[1][0] == 14);
    check(m3[2][0] == 15);

    check(m2 != m3);


    return 0;
}
