#include <iostream>
#include "Matrix.h"

void check(bool value) {
    if (!value)
        std::cout << "error" << std::endl;
}

//check Get number of cols/rows
void checkGetRows_GetCols() {
    Matrix m(2, 3);
    check(m.get_rows() == 2);
    check(m.get_cols() == 3);
}

//check Get element by index
void checkGetSet() {
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

//check Multiply by vector
void checkMulVec() {
    Matrix m(2, 3);
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
    Matrix m(2, 3);
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
    Matrix m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    Matrix n(2, 3);
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

int main() {

    checkGetRows_GetCols();
    checkGetSet();
    checkMulVec();
    checkMulNum();
    checkComp();

    return 0;
}