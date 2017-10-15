#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;



class Matrix {
public:
    Matrix(size_t n, size_t m) : n_row(n), n_col(m) {
        arr = new double[n_row * n_col];
    }

    ~Matrix() {
        delete[] arr;
    }

    size_t get_n_row() const {
        return n_row;
    }

    size_t get_n_col() const {
        return n_col;
    }

    bool operator==(const Matrix& m) const {
        if (n_row != m.n_row || n_col != m.n_col) {
            return false;
        }
        for (size_t i = 0; i < n_row * n_col; ++i) {
            if (arr[i] != m.arr[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Matrix& m) const {
        return !(*this == m);
    }

    Matrix& operator*=(vector<double>& v) {
        if (n_col != v.size()) {
            assert(!"incompatible sizes");
        }
        double *tmp_arr = new double[n_row];
        for (size_t i = 0; i < n_row; ++i) {
            double buff = 0;
            for (size_t j = 0; j < n_col; ++j) {
                buff += arr[i * n_col + j] * v[j];
            }
            tmp_arr[i] = buff;
        }
        delete[] arr;
        arr = tmp_arr;
        n_col = 1;
        return *this;
    }

    Matrix& operator*=(double val) {
        for (size_t i = 0; i < n_row * n_col; ++i) {
            arr[i] *= val;
        }
        return *this;
    }

    Matrix& operator=(const Matrix& m) {
        if (this != &m) {
            n_row = m.n_row;
            n_col = m.n_col;
            delete[] arr;
            arr = new double[n_row * n_col];
            for (size_t i = 0; i < n_row * n_col; ++i) {
                arr[i] = m.arr[i];
            }
        }
        return *this;
    }

    Matrix(const Matrix& m) {
        n_row = m.n_row;
        n_col = m.n_col;
        arr = new double[n_row * n_col];
        for (size_t i = 0; i < n_row * n_col; ++i) {
            arr[i] = m.arr[i];
        }
    }


private:
    class Row {
    public:
        Row(size_t l = 0, double *a = nullptr) : len(l), arr(a) {}

        ~Row() {}

        double& operator[](size_t n) {
            if (n >= len) {
                assert(!"index out of range");
            }
            return arr[n];
        }

        const double& operator[](size_t n) const {
            if (n >= len) {
                assert(!"index out of range");
            }
            return arr[n];
        }

        void set_len(size_t l) {
            len = l;
        }

        void set_arr(double *a) {
            arr = a;
        }
    private:
        size_t len;
        double *arr;
    };
    mutable Row tmp_row;
    size_t n_row, n_col;
    double *arr;

public:
    Row& operator[](size_t n) {
        if (n >= n_row) {
            assert(!"index out of range");
        }
        tmp_row.set_len(n_col);
        tmp_row.set_arr(&arr[n * n_col]);
        return tmp_row;
    }

    const Row& operator[](size_t n) const {
        if (n >= n_row) {
            assert(!"index out of range");
        }
        tmp_row.set_len(n_col);
        tmp_row.set_arr(&arr[n * n_col]);
        return tmp_row;
    }
};

ostream& operator<<(ostream& stream, const Matrix& m) {
    for (size_t i = 0; i < m.get_n_row(); ++i) {
        for (size_t j = 0; j < m.get_n_col(); ++j) {
            stream << m[i][j] << ' ';
        }
        stream << endl;
    }
    return stream;
}

void check(bool value)
{
    if (!value)
        std::cout << "error" << std::endl;
}

void CheckGetSet() {
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

void CheckGetShape() {
    Matrix m(9, 11);
    check(m.get_n_row() == 9);
    check(m.get_n_col() == 11);
}

void CheckMultOnVec() {
    Matrix m(3, 5);
    vector<double> v1 = { 3, 4, 5, 6, 7 }, v2 = {7};
    for (size_t i = 0; i < m.get_n_row(); ++i) {
        for (size_t j = 0; j < m.get_n_col(); ++j) {
            m[i][j] = i + j;
        }
    }
    m *= v1;
    check(m[0][0] == 60);
    check(m[1][0] == 85);
    check(m[2][0] == 110);
    
    m *= v2;
    check(m[0][0] == 420);
    check(m[1][0] == 595);
    check(m[2][0] == 770);
}

void CheckMultOnVal() {
    Matrix m(3, 7);
    double val = 13;
    for (size_t i = 0; i < m.get_n_row(); ++i) {
        for (size_t j = 0; j < m.get_n_col(); ++j) {
            m[i][j] = i + j;
        }
    }
    m *= val;
    for (size_t i = 0; i < m.get_n_row(); ++i) {
        for (size_t j = 0; j < m.get_n_col(); ++j) {
            check(m[i][j] == val * (i + j));
        }
    }
}

void CheckCmp() {
    Matrix m1(3, 5), m2(4, 2), m3(3, 5), m4(4, 6);
    vector<double> v1 = { 1, 1, 1, 1, 1 }, v2 = { 1, 1 };
    for (size_t i = 0; i < m1.get_n_row(); ++i) {
        for (size_t j = 0; j < m1.get_n_col(); ++j) {
            m1[i][j] = i + j;
        }
    }
    for (size_t i = 0; i < m2.get_n_row(); ++i) {
        for (size_t j = 0; j < m2.get_n_col(); ++j) {
            m2[i][j] = i + j;
        }
    }
    for (size_t i = 0; i < m3.get_n_row(); ++i) {
        for (size_t j = 0; j < m3.get_n_col(); ++j) {
            m3[i][j] = i + j;
        }
    }
    for (size_t i = 0; i < m4.get_n_row(); ++i) {
        for (size_t j = 0; j < m4.get_n_col(); ++j) {
            m4[i][j] = i + j;
        }
    }
    check((m1 == m2) == false);
    check((m1 != m2) == true);

    check((m1 == m3) == true);
    check((m1 != m3) == false);

    m3[0][4] += 10;
    check((m1 == m3) == false);
    check((m1 != m3) == true);

    check((m4 == m4) == true);
    check((m4 != m4) == false);
}

int main()
{
    CheckGetSet();
    CheckGetShape();
    CheckMultOnVec();
    CheckMultOnVal();
    CheckCmp();
    return 0;
}

