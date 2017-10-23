#include "matrix.cpp"

int check(bool value) {
    return int(!value);
}

void test_matrix() {
    int num_of_errors = 0;

    // Constructor with initializer_list tests
    Matrix<double> m1 = {4, 3,
                         7.5, 8.5, 9,
                         10, 11.8, 12,
                         13.9, 14.0, 15.6,
                         16.1, 17, 18.7};

    num_of_errors += check(m1.get_rows_num() == 4);
    num_of_errors += check(m1.get_cols_num() == 3);
    num_of_errors += check(m1[0][0] == 7.5);
    num_of_errors += check(m1[0][1] == 8.5);
    num_of_errors += check(m1[0][2] == 9);
    num_of_errors += check(m1[1][0] == 10);
    num_of_errors += check(m1[1][1] == 11.8);
    num_of_errors += check(m1[1][2] == 12);
    num_of_errors += check(m1[2][0] == 13.9);
    num_of_errors += check(m1[2][1] == 14);
    num_of_errors += check(m1[2][2] == 15.6);
    num_of_errors += check(m1[3][0] == 16.1);
    num_of_errors += check(m1[3][1] == 17);
    num_of_errors += check(m1[3][2] == 18.7);

    m1[1][1] = 111;
    num_of_errors += check(m1[1][1] == 111);

    // Constructor with rows_num and cols_num tests
    Matrix<double>m2(2, 3);
    m2[0][0] = 1;
    m2[0][1] = 2.5;
    m2[0][2] = 3.6;
    m2[1][0] = 4;
    m2[1][1] = 5.3;
    m2[1][2] = 6.7;

    Matrix<double> m3 = {2, 3,
                         1, 2.5, 3.6,
                         4, 5.3, 6.7};
    num_of_errors += check(m2 == m3);

    // Copy constructor
    Matrix<double> m4 = m3;
    num_of_errors += check(m4 == m3);
    m4[1][1] = -15;
    num_of_errors += check(m4 != m3);

    // Multiplication by a number
    Matrix<double> m5 = {3, 6,
                         1, 2, 3, 4, 5, 6,
                         7, 8, 9, 10, 11, 12,
                         13, 14, 15, 16, 17, 18};
    m5 *= 2.5;
    Matrix<double> m6 = {3, 6,
                         2.5, 5, 7.5, 10, 12.5, 15,
                         17.5, 20, 22.5, 25, 27.5, 30,
                         32.5, 35, 37.5, 40, 42.5, 45};
    num_of_errors += check(m5 == m6);

    // Multiplication by a vector
    std::vector<double> v1 = {2.5, 3, 4};
    m1 *= v1;
    Matrix<double> m7 = {4, 1,
                         80.25,
                         406,
                         139.15,
                         166.05};
    num_of_errors += check(m1 == m7);

    m3 *= v1;
    Matrix<double> m8 = {2, 1,
                         24.4,
                         52.7};
    num_of_errors += check(m3 == m8);

    // Copy asiignment operator
    Matrix<double> m9 = {2, 3,
                         1, 2, 3,
                         4, 5, 6};

    m8 = m9;
    num_of_errors += check(m8 == m9);

    // Move constructor
    Matrix<double> old_m9 = m9;
    Matrix<double> m10 = std::move(m9);
    num_of_errors += check(m10 == old_m9);

    //Move asiignment operator
    Matrix<double> old_m8 = m8;
    m10 = std::move(m8);
    num_of_errors += check(m10 == old_m8);

    //Template with int
    Matrix<int> m11 = {2, 3,
                       4, 5, 6,
                       7, 8, 9};
    std::vector<int> v2 = {1, 2, 3};
    m11 *= v2;
    Matrix<int> m12 = {2, 1,
                       32,
                       50};

    num_of_errors += check(m11 == m12);
    m12 *= 2;
    Matrix<int> m13 = {2, 1,
                       64,
                       100};

    num_of_errors += check(m13 == m12);

    // Number of failed tests
    if (num_of_errors == 0) {
        std::cout << "All tests passed" << std::endl;
    } else {
        std::cout << "Tests faild with " << num_of_errors << " errors" << std::endl;
    }
}

int main() {
    try {
        test_matrix();
    } catch (const char* err) {
        std::cout << err << std::endl;
        return 1;
    }

    return 0;
}
