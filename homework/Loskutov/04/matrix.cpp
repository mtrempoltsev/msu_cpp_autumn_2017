#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Matrix {
public:
private:
    class MatrixColumn {
    public:
        MatrixColumn(const size_t col, vector<double>::iterator);
        ~MatrixColumn();
        double& operator[](const size_t index);
    private:
        const size_t n_;
        vector<double>::iterator data_;
    };
    
    const size_t row_;
    const size_t col_;
    vector<double> data_;
public:
    Matrix(size_t row, size_t col);
    ~Matrix();
    
    size_t getRows() const;
    size_t getCols() const;
    
    vector<double> operator*(const vector<double> vec) const;
    Matrix& operator*=(const double factor);
    MatrixColumn& operator[](const size_t index);
    bool operator==(const Matrix& mat) const;
    bool operator!=(const Matrix& mat) const;
};

Matrix::MatrixColumn::MatrixColumn(const size_t col, vector<double>::iterator it):
n_(col) {
    data_ = it;
}

Matrix::MatrixColumn::~MatrixColumn() {}

double& Matrix::MatrixColumn::operator[](const size_t i) {
    if (i >= n_) {
        cout << "index out of range" << endl;
    }
    return *(data_ + i);
}

Matrix::Matrix(size_t row, size_t col):
row_(row), col_(col) {
    data_.assign(row*col, 0);
}

Matrix::~Matrix() {
    data_.clear();
}

size_t Matrix::getRows() const {
    return row_;
}

size_t Matrix::getCols() const {
    return col_;
}

vector<double> Matrix::operator*(const vector<double> vec) const {
    if (vec.size() != col_) {
        cout << "vector size is incorrect!" << endl;
    }
    
    vector<double> res(row_);
    for (int i = 0; i < row_; i++) {
        res[i] = 0.;
        for (int j = 0; j < col_; j++) {
            res[i] += data_[i*col_+j] * vec[j];
        }
    }
    
    return res;
}

Matrix& Matrix::operator*=(const double factor) {
    for (auto it = data_.begin(); it < data_.end(); ++it) {
        *it *= factor;
    }
    
    return *this;
}

Matrix::MatrixColumn& Matrix::operator[](const size_t i) {
    if (i >= row_) {
        cout << "index out of range" << endl;
    }
    
    return *(new Matrix::MatrixColumn(col_, data_.begin() + i*col_));
}

bool Matrix::operator==(const Matrix& mat) const {
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

bool Matrix::operator!=(const Matrix& mat) const {
    return !(*this == mat);
}

void check(bool value) {
    if (!value)
        cout << "error" << endl;
}

void checkGetSet() {
    Matrix m(2, 3);
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

void checkMul() {
    Matrix m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;
    Matrix m2(2, 3);
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
    
    vector<double> v = {1, 2, 3};
    check(v.size() == 3);
    v = m * v;
    check(v.size() == 2);
    check(v[0] == 42);
    check(v[1] == 942);
}

int main() {
    checkGetSet();
    checkMul();
    return 0;
}
