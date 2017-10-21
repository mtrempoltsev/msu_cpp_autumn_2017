#include <iostream>
#include "matrix.h"

void check_get_set();
void check_get_rows_number();
void check_get_columns_number();
void check_multiplication();
void check_vector_multiplication();
void check_vector_multiplication_assignment();
void check_equality();
void check_non_equality();

int main() {
    std::cout << "Test" << std::endl;
    std::cout << "Get set" << std::endl;
    check_get_set();
    std::cout << "Get rows number" << std::endl;
    check_get_rows_number();
    std::cout << "Get columns number" << std::endl;
    check_get_columns_number();
    std::cout << "Multiplication" << std::endl;
    check_multiplication();
    std::cout << "Vector multiplication" << std::endl;
    check_vector_multiplication();
    std::cout << "Vector multiplication with assignment" << std::endl;
    check_vector_multiplication_assignment();
    std::cout << "Equality" << std::endl;
    check_equality();
    std::cout << "Non-equality" << std::endl;
    check_non_equality();

    return 0;
}

void check(bool value) {
    if (!value) std::cout << "error" << std::endl;
}

void check_get_set() {
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

void check_get_rows_number() {
    Matrix m(2, 3);
    check(m.get_rows_number() == 2);
}

void check_get_columns_number() {
    Matrix m(2, 3);
    check(m.get_columns_number() == 3);
}

void check_multiplication() {
    Matrix m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;
    m *= 2;
    check(m[0][0] == 2);
    check(m[0][1] == 4);
    check(m[0][2] == 6);
    check(m[1][0] == 8);
    check(m[1][1] == 10);
    check(m[1][2] == 12);
}

void check_vector_multiplication() {
    Matrix m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;
    std::vector<double> v = {1, 2, 3};
    std::vector<double> v1 = (m * v);
    check(v1 == std::vector<double> ({14, 32}));
}

void check_vector_multiplication_assignment() {
    Matrix m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;
    std::vector<double> v = {1, 2, 3};
    m *= v;
    check(m.get_columns_number() == 1);
    check(m.get_rows_number() == 2);
    check(m[0][0] == 14);
    check(m[1][0] == 32);
}

void check_equality() {
    Matrix m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    Matrix m1(2, 3);
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[0][2] = 3;
    m1[1][0] = 4;
    m1[1][1] = 5;
    m1[1][2] = 6;

    Matrix m2(2, 3);
    m2[0][0] = 100500;
    m2[0][1] = 2;
    m2[0][2] = 3;
    m2[1][0] = 4;
    m2[1][1] = 5;
    m2[1][2] = 6;

    Matrix m3(1, 3);

    check(m == m);
    check(m == m1);
    check(!(m == m2));
    check(!(m == m3));
}
void check_non_equality() {
    Matrix m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    Matrix m1(2, 3);
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[0][2] = 3;
    m1[1][0] = 4;
    m1[1][1] = 5;
    m1[1][2] = 6;

    Matrix m2(2, 3);
    m2[0][0] = 100500;
    m2[0][1] = 2;
    m2[0][2] = 3;
    m2[1][0] = 4;
    m2[1][1] = 5;
    m2[1][2] = 6;

    Matrix m3(1, 3);
    check(!(m != m));
    check(!(m != m1));
    check(m != m2);
    check(m != m3);
}
