#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

template <class T>
class Matrix {
private:
    class MatrixColumn {
    public:
        MatrixColumn(const size_t col, typename vector<T>::iterator it):
        n_(col) {
            data_ = it;
        }
        
        ~MatrixColumn() {}
        
        T& operator[](const size_t index)  {
            if (index >= n_) {
                cout << "index out of range" << endl;
            }
            return *(data_ + index);
        }
    private:
        const size_t n_;
        typename vector<T>::iterator data_;
    };
    
    size_t row_;
    size_t col_;
    vector<T> data_;
    
public:
    Matrix(size_t row, size_t col) {
        row_ = row;
        col_ = col;
        data_.assign(row*col, 0);
    }
    
    ~Matrix() {
        data_.clear();
    }
    
    Matrix(const Matrix& copied) {
        row_ = copied.row_;
        col_ = copied.col_;
        data_ = copied.data_;
    }
    
    Matrix& operator=(const Matrix& copied) {
        if (this == &copied) {
            return *this;
        }
        data_.clear();
        row_ = copied.row_;
        col_ = copied.col_;
        data_ = copied.data_;
        return *this;
    }
    
    Matrix(Matrix&& movied) {
        row_ = movied.row_;
        col_ = movied.col_;
        data_ = movied.data_;
        movied.data_.clear();
    }
    
    Matrix& operator=(Matrix&& movied) {
        if (this == &movied) {
            return *this;
        }
        data_.clear();
        row_ = movied.row_;
        col_ = movied.col_;
        data_ = movied.data_;
        movied.data_.clear();
        return *this;
    }
    
    size_t getRows() const {
        return row_;
    }
    
    size_t getCols() const {
        return col_;
    }
    
    vector<T> operator*(const vector<T> vec) const {
        if (vec.size() != col_) {
            cout << "vector size is incorrect!" << endl;
        }
        
        vector<T> res(row_);
        for (int i = 0; i < row_; i++) {
            res[i] = 0.;
            for (int j = 0; j < col_; j++) {
                res[i] += data_[i*col_+j] * vec[j];
            }
        }
        
        return res;
    }
    
    Matrix& operator*=(const double factor) {
        for (auto it = data_.begin(); it < data_.end(); ++it) {
            *it *= factor;
        }
        
        return *this;
    }
    
    Matrix::MatrixColumn& operator[](const size_t index) {
        if (index >= row_) {
            cout << "index out of range" << endl;
        }
        
        return *(new Matrix::MatrixColumn(col_, data_.begin() + index*col_));
    }
    
    bool operator==(const Matrix& mat) const {
        if ((mat.getRows() != row_) && (mat.getCols() != col_)) {
            return false;
        }
        
        auto it2 = mat.data_.begin();
        for (auto it = data_.begin(); it < data_.end(); ++it, ++it2) {
            if (*it != *it2) {
                return false;
            }
        }
        return true;
    }
    
    bool operator!=(const Matrix& mat) const {
        return !(*this == mat);
    }
};

void check(bool value) {
    if (!value)
        cout << "error" << endl;
}

template <class T>
void checkGetSet() {
    Matrix<T> m(2, 3);
    check(m.getRows() == 2);
    check(m.getCols() == 3);
    
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

template <class T>
void checkMul() {
    Matrix<T> m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;
    Matrix<T> m2(2, 3);
    m2[0][0] = 1;
    m2[0][1] = 2;
    m2[0][2] = 3;
    m2[1][0] = 4;
    m2[1][1] = 5;
    m2[1][2] = 6;
    check(m == m2);
    
    m[1][2] = 100;
    check(m != m2);
    
    m *= 3;
    check(m[0][0] == 3);
    check(m[0][1] == 6);
    check(m[0][2] == 9);
    check(m[1][0] == 12);
    check(m[1][1] == 15);
    check(m[1][2] == 300);
    
    vector<T> v = {1, 2, 3};
    check(v.size() == 3);
    v = m * v;
    check(v.size() == 2);
    check(v[0] == 42);
    check(v[1] == 942);
}

template <class T>
void checkConstructors() {
    Matrix<T> m1 = Matrix<T>(3,2);
    m1[0][0] = 0;
    m1[0][1] = 1;
    m1[1][0] = 2;
    m1[1][1] = 3;
    m1[2][0] = 4;
    m1[2][1] = 5;
    Matrix<T> m2 = m1;
    check(m2[0][0] == 0);
    check(m2[0][1] == 1);
    check(m2[1][0] == 2);
    check(m2[1][1] == 3);
    check(m2[2][0] == 4);
    check(m2[2][1] == 5);
    
    Matrix<T> m3 = Matrix<T>(3,2);
    m3[0][0] = 0;
    m3[0][1] = 1;
    m3[1][0] = 2;
    m3[1][1] = 3;
    m3[2][0] = 4;
    m3[2][1] = 5;
    Matrix<T> m4(1,1);
    m4 = m3;
    check(m4[0][0] == 0);
    check(m4[0][1] == 1);
    check(m4[1][0] == 2);
    check(m4[1][1] == 3);
    check(m4[2][0] == 4);
    check(m4[2][1] == 5);
    
    Matrix<T> m5 = Matrix<T>(3,2);
    m5[0][0] = 0;
    m5[0][1] = 1;
    m5[1][0] = 2;
    m5[1][1] = 3;
    m5[2][0] = 4;
    m5[2][1] = 5;
    Matrix<T> m6 = std::move(m5);
    check(m6[0][0] == 0);
    check(m6[0][1] == 1);
    check(m6[1][0] == 2);
    check(m6[1][1] == 3);
    check(m6[2][0] == 4);
    check(m6[2][1] == 5);
    
    Matrix<T> m7 = Matrix<T>(3,2);
    m7[0][0] = 0;
    m7[0][1] = 1;
    m7[1][0] = 2;
    m7[1][1] = 3;
    m7[2][0] = 4;
    m7[2][1] = 5;
    Matrix<T> m8 = Matrix<T>(3,2);
    m8[0][0] = 6;
    m8[0][1] = 7;
    m8[1][0] = 8;
    m8[1][1] = 9;
    m8[2][0] = 10;
    m8[2][1] = 11;
    m8 = std::move(m7);
    check(m8[0][0] == 0);
    check(m8[0][1] == 1);
    check(m8[1][0] == 2);
    check(m8[1][1] == 3);
    check(m8[2][0] == 4);
    check(m8[2][1] == 5);
}

int main() {
    checkGetSet<int>();
    checkMul<int>();
    checkConstructors<int>();
    checkGetSet<double>();
    checkMul<double>();
    checkConstructors<double>();
    return 0;
}
