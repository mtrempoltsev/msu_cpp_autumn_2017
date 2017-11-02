// Vasilii Bodnariuk

#include <iostream>
#include <string>

#include "matrix.cpp"

using namespace std;

void check(bool value)
{
    if (!value)
        std::cout << "error" << std::endl;
}


int main()
{
    Matrix<int> m1(2, 3);

    check(m1.rows() == 2);
    check(m1.cols() == 3);

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



    Matrix<int> m2(2, 3);
    m2[0][0] = -1;
    m2[0][1] = -2;
    m2[0][2] = -3;
    m2[1][0] = -4;
    m2[1][1] = -5;
    m2[1][2] = -6;
    m2 *= -1;

    check(m2[0][0] == 1);
    check(m2[0][1] == 2);
    check(m2[0][2] == 3);
    check(m2[1][0] == 4);
    check(m2[1][1] == 5);
    check(m2[1][2] == 6);

    check(m1 == m2);

    m2[1][2] = 100;
    check(m2[1][2] == 100);

    Matrix<int> m3(3, 1);
    m3[0][0] = 1;
    m3[1][0] = 2;
    m3[2][0] = 3;

    // check((10 * m3)[0][0] == 10);
    check((m3 * 10)[0][0] == 10);

    vector<int> v1 = {11, 7, 5};

    m3 *= v1;

    check(m3[0][0] == 11);
    check(m3[1][0] == 14);
    check(m3[2][0] == 15);

    check(m2 != m3);

    Matrix<int> m4(4,2);
    m4 = std::move(m3);
    check(m4[2][0] == 15);

    Matrix<int> m5 = std::move(m4);
    check(m5[2][0] == 15);

    Matrix<bool> m6(1, 1);
    m6[0][0] = true;
    check(m6[0][0] == true);


    std::cout << "tests ended" << '\n';
    return 0;
}
