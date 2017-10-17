#include <iostream>
#include <vector>
#include <cassert>

class Matrix {
std::vector<double> matrix;
    size_t rows;
    size_t cols;

public:

    class ProxMatrix {
        std::vector<double> &m; //stores ref to the whole matrix
        size_t size; // size of a Proxy Matrix, colunms amount actually
        size_t row; // beginning of a Proxy Matrix in m
    public:
        ProxMatrix(std::vector<double> &matrix, size_t row, size_t cols) : m(matrix) {
            size = cols;
            this->row = row;
        }

        double &operator[](size_t i) { //[] overload for Proxy Matrix
            if (this->size <= i) {
                assert(!"Index out of range");
            }
            return m[row * size + i];
        }
    };

    Matrix(size_t rows, size_t cols) {
        matrix.resize(rows * cols);
        this->rows = rows;
        this->cols = cols;
    }

    const size_t get_rows_amount() const {
        return this->rows;
    }

    const size_t get_cols_amount() const {
        return this->cols;
    }
    
    friend bool operator==(const Matrix &l, const Matrix &r); // friend -> easy to compare matrices as vectors

    bool operator!=(const Matrix &other) const {
        return !(*this == other);
    }

    Matrix &operator*=(const double &num) { // Matrix * double
        for(auto it = matrix.begin(); it < matrix.end(); it++) {
            (*it) *= num;
        }
        return (*this);
    }

    std::vector<double> operator*=(const std::vector<double> &v) { // Matrix * vector
        if (v.size() != this->cols) {
            assert(!"Vector size does not match");
        }
        std::vector<double> result_v;
        result_v.resize(this->rows);

        auto it = matrix.begin();
        auto vt = result_v.begin();
        
        for(;
            it < matrix.end(), vt < result_v.end();
            vt++) {

            double new_value = 0;
            for(auto jt = v.begin(); jt < v.end(); jt++, it++) {
                new_value += (*it) * (*jt);
            }
            (*vt) = new_value;
        }

        return result_v;
    }

    ProxMatrix operator[](size_t i) { //[] overload for Matrix
        if (this->rows <= i) {
            assert(!"Index out of range");
        }
        return ProxMatrix(this->matrix, i, this->cols);
    }
};

bool operator==(const Matrix &l, const Matrix &r) { //Matrix friend overload[] method
    if (l.rows != r.rows || l.cols != l.cols) {
            return false; 
    }
    auto it_l = l.matrix.begin();
    auto it_r = r.matrix.begin();
    for(; it_l < l.matrix.end(), it_r < r.matrix.end(); it_l++, it_r++) {
        if (*it_l != *it_r) {
            return false;
        }
    }
    return true;
}

//==============v test v==============\\

int check(bool value, const char *msg)
{
    if (!value) {
        std::cout << msg << " error" << std::endl;
        return 1;
    }
    return 0;
}

int checkGetSizes() {
    Matrix m(2, 3);
    return check(m.get_rows_amount() == 2, "Row get") +
           check(m.get_cols_amount() == 3, "Col get");
}

int checkGetSet()
{
    int errors = 0;    
    Matrix m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;
    
    errors += 
        check(m[0][0] == 1, "Get set") +
        check(m[0][1] == 2, "Get set") +
        check(m[0][2] == 3, "Get set") +
        check(m[1][0] == 4, "Get set") +
        check(m[1][1] == 5, "Get set") +
        check(m[1][2] == 6, "Get set");
    
    m[1][2] = 100;
    
    errors += check(m[1][2] == 100, "Lvalue assigning");

    double x = m[1][2];

    errors += check(x == 100, "Rvalue assigning");

    return errors;
}

int checkVectMult() {
    
    Matrix m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    std::vector<double> v = {1, 2, 3};
    std::vector<double> v1 = m *= v;

    return check(v1 == std::vector<double>{14, 32}, "Vect mult");
}

int checkNumMult() {
    
    Matrix m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    m *= 3;

    return 
        check(m[0][0] == 3, "Num mult")  +
        check(m[0][1] == 6, "Num mult")  +
        check(m[0][2] == 9, "Num mult")  +
        check(m[1][0] == 12, "Num mult") +
        check(m[1][1] == 15, "Num mult") +
        check(m[1][2] == 18, "Num mult");

}

int chechEqualMatrices() {
    Matrix m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    Matrix m1(2, 3); // same matrix
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[0][2] = 3;
    m1[1][0] = 4;
    m1[1][1] = 5;
    m1[1][2] = 6;

    Matrix m2(2, 3); // same size, different values
    m2[0][0] = 1;
    m2[0][1] = 2;
    m2[0][2] = 3;
    m2[1][0] = 4;
    m2[1][1] = 5;
    m2[1][2] = 61;

    Matrix m3(1, 3); // different size
    m3[0][0] = 1;
    m3[0][1] = 2;
    m3[0][2] = 3;

    return check(m == m1, "Equality") + check(m != m2, "Inequality") + check(m != m3, "Inequality");
}

int main() {

    int errors = 0;

    errors +=
        checkGetSizes() +
        checkGetSet()   +
        checkVectMult() +
        checkNumMult()  +
        chechEqualMatrices();

    std::cout << errors << " error(s) found\n";

    return 0;
}
