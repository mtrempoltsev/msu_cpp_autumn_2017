#include "custom_Matrix.cpp"

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

/*
 * test Matrix<double> operations
 */
void checkMatrixOperations() {

    Matrix<double> m(2, 3);

    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    Matrix<double> m2(m.Transpose());

    check(m2.getRows() == 3);
    check(m2.getCols() == 2);

    check(m2[0][0] == 1);
    check(m2[0][1] == 4);
    check(m2[1][0] == 2);
    check(m2[1][1] == 5);
    check(m2[2][0] == 3);
    check(m2[2][1] == 6);

    Matrix<double> m3(m * m2);

    check(m3.getRows() == 2);
    check(m3.getCols() == 2);

    check(m3[0][0] == 14);
    check(m3[0][1] == 32);
    check(m3[1][0] == 32);
    check(m3[1][1] == 77);

    Matrix<double> m4(m - m);

    check(m4[0][0] == 0);
    check(m4[0][1] == 0);
    check(m4[0][2] == 0);
    check(m4[1][0] == 0);
    check(m4[1][1] == 0);
    check(m4[1][2] == 0);


    Matrix<double> m5(m + m);

    check(m5[0][0] == 2);
    check(m5[0][1] == 4);
    check(m5[0][2] == 6);
    check(m5[1][0] == 8);
    check(m5[1][1] == 10);
    check(m5[1][2] == 12);

    Matrix<double> m7(m / 2);

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

    Matrix<int> m(2, 3);

    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    std::vector<int> v{2, 3};

    std::vector<int> v2(v * m);

    check(v2[0] == 14);
    check(v2[1] == 19);
    check(v2[2] == 24);

    std::vector<int> v3{2, 3, 4};

    std::vector<int> v4(m * v3);

    check(v4[0] == 20);
    check(v4[1] == 47);
}

/*
 * test equality operator
 */
void checkComparativeOperators() {

    Matrix<double> m(2, 3);

    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    check(m == m);
    check(m == m.Transpose().Transpose());
    check(m != (m * 2));
    check(m != (2 * m));
    check(m == (2.1 * m / 2.1));
    check(m == ((m.Transpose() * 45) / 45).Transpose());
    check((m - m) == (0 * m));
    check(-m != m);
    check((-m) == (m * (-1)));
    check((-m) == (m - (m * 2)));
    check((-m) == ((7 * m) - (m * 8)));
    check((m * m.Transpose())[0][0] == (m[0][0] * m[0][0] + m[0][1] * m[0][1] + m[0][2] * m[0][2]));

    check(m[1] == m[1]);
    check(0.5 * m[1] == (m.Transpose().Transpose()[1] / 2));

    Matrix<double> m8(2, 3);
    m8 = m;
    check(m8[0] == m[0]);
    check(m8 == m);
}

void checkMoveAndCopyOperators() {

    Matrix<std::string> m(2, 3);
    m[0][0] = "test";
    check(m[0][0] == "test");
    m[0][0] += "ing";
    check(m[0][0] == "testing");

    Matrix<std::string> m2(std::move(m));
    check(m2[0][0] == "testing");
    check(m[0][0] == "");

    Matrix<std::string> m3(1, 2);
    m3 = m2;
    check(m3[0][0] == "testing");

    Matrix<std::string> m4(5, 1);
    m4 = std::move(m3);
    check(m4[0][0] == "testing");
    check(m3[0][0] == "");

    Matrix<std::string> m5(m4);
    check(m5[0][0] == "testing");

}

int main(int argc, char const *argv[]) {

    try {
        checkGetSet();
        checkMatrixOperations();
        checkVectorOperations();
        checkComparativeOperators();
        checkMoveAndCopyOperators();
    } catch (std::exception &e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }
    if (error_count == 0)
        std::cout << "OK" << std::endl;
    return 0;
}
