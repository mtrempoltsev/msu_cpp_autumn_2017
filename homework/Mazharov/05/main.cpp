#include <iostream>
#include "matrix.h"

void check(bool value) {
    if (!value)
        std::cout << "error" << std::endl;
}

//check Get number of cols/rows
void checkGetRows_GetCols() {
    Matrix<double> m(2, 3);
    check(m.get_rows() == 2);
    check(m.get_cols() == 3);
}

//check Get element by index
void checkGetSet() {
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
}

//check Multiply by vector
void checkMulVec() {
    Matrix<double> m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    std::vector<double> v = {7, 8, 9};

    auto res = m * v;

    check(res.size() == 2);
    check(res[0] == 50);
    check(res[1] == 122);
}

//check Multiply by number
void checkMulNum() {
    Matrix<double> m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    m = m * 10;

    check(m[0][0] == 10);
    check(m[0][1] == 20);
    check(m[0][2] == 30);
    check(m[1][0] == 40);
    check(m[1][1] == 50);
    check(m[1][2] == 60);
}

//check Matrix comparison
void checkComp() {
    Matrix<double> m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    Matrix<double> n(2, 3);
    n[0][0] = 1;
    n[0][1] = 2;
    n[0][2] = 3;
    n[1][0] = 4;
    n[1][1] = 5;
    n[1][2] = 6;

    check((m == n) == 1);
    check((m != n) == 0);

    m[0][0] = 10;

    check((m == n) == 0);
    check((m != n) == 1);
}

//check Copy / Move
void checkConstructs() {
    // Copy constructor
    Matrix<double> m1 = Matrix<double>(2,2);
    m1[0][0] = 0;
    m1[0][1] = 1;
    m1[1][0] = 2;
    m1[1][1] = 3;

    Matrix<double> m2 = m1;
    check(m2[0][0] == 0);
    check(m2[0][1] == 1);
    check(m2[1][0] == 2);
    check(m2[1][1] == 3);

    // Copy operator
    Matrix<double> m3 = Matrix<double>(2,2);
    m3[0][0] = 0;
    m3[0][1] = 1;
    m3[1][0] = 2;
    m3[1][1] = 3;

    Matrix<double> m4;
    m4 = m3;
    check(m4[0][0] == 0);
    check(m4[0][1] == 1);
    check(m4[1][0] == 2);
    check(m4[1][1] == 3);

    // Move constructor
    Matrix<double> m5 = Matrix<double>(2,2);
    m5[0][0] = 0;
    m5[0][1] = 1;
    m5[1][0] = 2;
    m5[1][1] = 3;

    Matrix<double> m6 = std::move(m5);

    check(m6[0][0] == 0);
    check(m6[0][1] == 1);
    check(m6[1][0] == 2);
    check(m6[1][1] == 3);


    // Move operator
    Matrix<double> m7 = Matrix<double>(2,2);
    m7[0][0] = 0;
    m7[0][1] = 1;
    m7[1][0] = 2;
    m7[1][1] = 3;

    Matrix<double> m8 = Matrix<double>(2,2);
    m8[0][0] = 4;
    m8[0][1] = 5;
    m8[1][0] = 6;
    m8[1][1] = 7;

    m8 = std::move(m7);

    check(m8[0][0] == 0);
    check(m8[0][1] == 1);
    check(m8[1][0] == 2);
    check(m8[1][1] == 3);
}

int main() {

    checkGetRows_GetCols();
    checkGetSet();
    checkMulVec();
    checkMulNum();
    checkComp();
    checkConstructs();

    return 0;
}