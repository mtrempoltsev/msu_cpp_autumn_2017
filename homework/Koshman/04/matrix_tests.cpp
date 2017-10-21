#include "custom_matrix.cpp"

static int error_count = 0;

void check(bool value) {
    if (!value) {
        error_count++;
        std::cout << "error" << std::endl;
    }
}

/*
 * test element assignment
 */
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

/*
 * test matrix operations
 */
void checkMatrixOperations() {

    Matrix m(2, 3);

    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    Matrix m2(m.T());

    check(m2.getRows() == 3);
    check(m2.getCols() == 2);

    check(m2[0][0] == 1);
    check(m2[0][1] == 4);
    check(m2[1][0] == 2);
    check(m2[1][1] == 5);
    check(m2[2][0] == 3);
    check(m2[2][1] == 6);

    Matrix m3(m * m2);

    check(m3.getRows() == 2);
    check(m3.getCols() == 2);

    check(m3[0][0] == 14);
    check(m3[0][1] == 32);
    check(m3[1][0] == 32);
    check(m3[1][1] == 77);

    Matrix m4(m - m);

    check(m4[0][0] == 0);
    check(m4[0][1] == 0);
    check(m4[0][2] == 0);
    check(m4[1][0] == 0);
    check(m4[1][1] == 0);
    check(m4[1][2] == 0);


    Matrix m5(m + m);

    check(m5[0][0] == 2);
    check(m5[0][1] == 4);
    check(m5[0][2] == 6);
    check(m5[1][0] == 8);
    check(m5[1][1] == 10);
    check(m5[1][2] == 12);

    Matrix m7(m / 2);

    check(m7[0][0] == .5);
    check(m7[0][1] == 1);
    check(m7[0][2] == 1.5);
    check(m7[1][0] == 2);
    check(m7[1][1] == 2.5);
    check(m7[1][2] == 3);


}

/*
 * test vector multiplication
 */
void checkVectorOperations() {

    Matrix m(2, 3);

    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    std::vector<double> v{2, 3};

    std::vector<double> v2(v * m);

    check(v2[0] == 14);
    check(v2[1] == 19);
    check(v2[2] == 24);

    std::vector<double> v3{2, 3, 4};

    std::vector<double> v4(m * v3);

    check(v4[0] == 20);
    check(v4[1] == 47);
}

/*
 * test equality operator
 */
void checkComparativeOperators() {

    Matrix m(2, 3);

    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    check(m == m);
    check(m == m.T().T());
    check(m != (m * 2));
    check(m != (2 * m));
    check(m == (2.132 * m / 2.132));
    check(m == ((m.T() * 45.9) / 45.9).T());
    check((m - m) == (0 * m));
    check(-m != m);
    check((-m) == (m * (-1)));
    check((-m) == (m - (m * 2)));
    check((-m) == ((7.3 * m) - (m * 8.3)));
    check((m * m.T())[0][0] == (m[0][0] * m[0][0] + m[0][1] * m[0][1] + m[0][2] * m[0][2]));

    check(m[1] == m[1]);
    check(0.5 * m[1] == (m.T().T()[1] / 2));

    Matrix m8(2, 3);
    m8 = m;
    check(m8[0] == m[0]);
    check(m8 == m);
}


int main(int argc, char const *argv[]) {

    checkGetSet();
    checkMatrixOperations();
    checkVectorOperations();
    checkComparativeOperators();

    if (error_count == 0)
        std::cout << "OK" << std::endl;
    return 0;
}