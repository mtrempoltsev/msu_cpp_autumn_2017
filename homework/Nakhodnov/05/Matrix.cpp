#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <random>
#include <complex>
using namespace std;


uniform_int_distribution<> dist(0, 1000);
mt19937 mers_tw;

template<class T>
class Matrix {
public:
    Matrix(size_t n, size_t m) : n_row(n), n_col(m) {
        arr = new T[n_row * n_col];
    }

    Matrix(const Matrix& m) {
        n_row = m.n_row;
        n_col = m.n_col;
        arr = new T[n_row * n_col];
        for (size_t i = 0; i < n_row * n_col; ++i) {
            arr[i] = m.arr[i];
        }
    }

    Matrix(Matrix&& m) {
        n_row = m.n_row;
        n_col = m.n_col;
        arr = m.arr;
        m.arr = nullptr;
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

    Matrix& operator*=(vector<T>& v) {
        if (n_col != v.size()) {
            assert(!"incompatible sizes");
        }
        T *tmp_arr = new T[n_row];
        for (size_t i = 0; i < n_row; ++i) {
            T buff = 0;
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

    Matrix& operator*=(T val) {
        for (size_t i = 0; i < n_row * n_col; ++i) {
            arr[i] *= val;
        }
        return *this;
    }

    Matrix& operator=(const Matrix& m) {
        if (this != &m) {
            if (n_row != m.n_row || n_col != m.n_col) {
                n_row = m.n_row;
                n_col = m.n_col;
                delete[] arr;
                arr = new T[n_row * n_col];
            }
            for (size_t i = 0; i < n_row * n_col; ++i) {
                arr[i] = m.arr[i];
            }
        }
        return *this;
    }

    Matrix& operator=(Matrix&& m) {
        if (this != &m) {
            n_row = m.n_row;
            n_col = m.n_col;
            delete[] arr;
            arr = m.arr;
            m.arr = nullptr;
        }
        return *this;
    }


private:
    class Row {
    public:
        Row(size_t l = 0, T *a = nullptr) : len(l), arr(a) {}

        ~Row() {}

        T& operator[](size_t n) {
            if (n >= len) {
                assert(!"index out of range");
            }
            return arr[n];
        }

        const T& operator[](size_t n) const {
            if (n >= len) {
                assert(!"index out of range");
            }
            return arr[n];
        }
    private:
        size_t len;
        T *arr;
    };
    size_t n_row, n_col;
    T *arr;

public:

    Row operator[](size_t n) {
        if (n >= n_row) {
            assert(!"index out of range");
        }
        return Row(n_col, &arr[n * n_col]);
    }

    const Row operator[](size_t n) const {
        if (n >= n_row) {
            assert(!"index out of range");
        }
        return Row(n_col, &arr[n * n_col]);
    }
};

template<class T>
ostream& operator<<(ostream& stream, const Matrix<T>& m) {
    for (size_t i = 0; i < m.get_n_row(); ++i) {
        for (size_t j = 0; j < m.get_n_col(); ++j) {
            stream << m[i][j] << ' ';
        }
        stream << endl;
    }
    return stream;
}

template<class T>
class Matrix_Checker {

public:
    void prepare_tests() {
        CheckGetSet();
        CheckGetShape();
        CheckMultOnVec();
        CheckMultOnVal();
        CheckCmp();
        CheckCopy();
        if (!error_flag) {
            cout << typeid(Matrix<T>(0, 0)).name() << " passed all tests\n";
        }
        else {
            cout << typeid(Matrix<T>(0, 0)).name() << " works incorrectly\n";
        }
    }

private:
    bool error_flag = false;

    void CheckResult(bool value)
    {
        if (!value) {
            error_flag = true;
            std::cout << "error" << std::endl;
        }
    }

    void CheckGetSet() {
        Matrix<T> m(2, 3);
        m[0][0] = 1;
        m[0][1] = 2;
        m[0][2] = 3;
        m[1][0] = 4;
        m[1][1] = 5;
        m[1][2] = 6;

        CheckResult(m[0][0] == 1);
        CheckResult(m[0][1] == 2);
        CheckResult(m[0][2] == 3);
        CheckResult(m[1][0] == 4);
        CheckResult(m[1][1] == 5);
        CheckResult(m[1][2] == 6);

        m[1][2] = 100;

        CheckResult(m[1][2] == 100);
    }

    void CheckGetShape() {
        Matrix<T> m(9, 11);
        CheckResult(m.get_n_row() == 9);
        CheckResult(m.get_n_col() == 11);
    }

    void CheckMultOnVec() {
        Matrix<T> m(3, 5);
        vector<T> v1 = { 3, 4, 5, 6, 7 }, v2 = { 7 };
        for (size_t i = 0; i < m.get_n_row(); ++i) {
            for (size_t j = 0; j < m.get_n_col(); ++j) {
                m[i][j] = i + j;
            }
        }
        m *= v1;
        CheckResult(m[0][0] == 60);
        CheckResult(m[1][0] == 85);
        CheckResult(m[2][0] == 110);

        m *= v2;
        CheckResult(m[0][0] == 420);
        CheckResult(m[1][0] == 595);
        CheckResult(m[2][0] == 770);
    }

    void CheckMultOnVal() {
        Matrix<T> m(3, 7);
        T val = 13;
        for (size_t i = 0; i < m.get_n_row(); ++i) {
            for (size_t j = 0; j < m.get_n_col(); ++j) {
                m[i][j] = i + j;
            }
        }
        m *= val;
        for (size_t i = 0; i < m.get_n_row(); ++i) {
            for (size_t j = 0; j < m.get_n_col(); ++j) {
                CheckResult(m[i][j] == val * (int)(i + j));
            }
        }
    }

    void CheckCmp() {
        Matrix<T> m1(3, 5), m2(4, 2), m3(3, 5), m4(4, 6);
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
        CheckResult((m1 == m2) == false);
        CheckResult((m1 != m2) == true);

        CheckResult((m1 == m3) == true);
        CheckResult((m1 != m3) == false);

        m3[0][4] += 10;
        CheckResult((m1 == m3) == false);
        CheckResult((m1 != m3) == true);

        CheckResult((m4 == m4) == true);
        CheckResult((m4 != m4) == false);
    }

    void CheckCopy() {
        Matrix<T> m1(2, 2), m2(4, 6);
        for (size_t i = 0; i < m1.get_n_row(); ++i) {
            for (size_t j = 0; j < m1.get_n_col(); ++j) {
                m1[i][j] = dist(mers_tw);
            }
        }

        for (size_t i = 0; i < m2.get_n_row(); ++i) {
            for (size_t j = 0; j < m2.get_n_col(); ++j) {
                m2[i][j] = dist(mers_tw);
            }
        }
        //Check copy operator
        m1 = m2;
        CheckResult(m1 == m2);

        //Check copy constructor
        Matrix<T> m3 = m2;
        CheckResult(m2 == m3);

    }


};

class Test_Matr_Pair {
public:
    Test_Matr_Pair(int a1, int b1) : a(a1), b(b1) {  }
    Test_Matr_Pair(int c = 0) : a(c), b(c) {  }
    Test_Matr_Pair operator+(const Test_Matr_Pair& P) {
        return Test_Matr_Pair(a + P.a, b + P.b);
    }

    Test_Matr_Pair operator*(const Test_Matr_Pair& P) {
        return Test_Matr_Pair(a * P.a, b * P.b);
    }

    bool operator<(const Test_Matr_Pair& P) {
        return (a < P.a) && (b < P.b);
    }

    bool operator>(const Test_Matr_Pair& P) {
        return (a > P.a) && (b > P.b);
    }

    bool operator==(const Test_Matr_Pair& P) {
        return (a == P.a) && (b == P.b);
    }

    bool operator!=(const Test_Matr_Pair& P) {
        return (a != P.a) && (b != P.b);
    }

    Test_Matr_Pair& operator=(int c) {
        a = c;
        b = c;
        return *this;
    }

    Test_Matr_Pair& operator+=(int c) {
        a += c;
        b += c;
        return *this;
    }

    Test_Matr_Pair& operator+=(const Test_Matr_Pair& P) {
        a += P.a;
        b += P.b;
        return *this;
    }

    Test_Matr_Pair& operator*=(int c) {
        a *= c;
        b *= c;
        return *this;
    }

    Test_Matr_Pair& operator*=(const Test_Matr_Pair& P) {
        a *= P.a;
        b *= P.b;
        return *this;
    }

private:
    int a, b;
};


int main()
{
    Matrix_Checker<double> mch_d;
    Matrix_Checker<int> mch_i;
    Matrix_Checker<Test_Matr_Pair> mch_comp;
    mch_d.prepare_tests();
    mch_i.prepare_tests();
    mch_comp.prepare_tests();
    return 0;
}