#include "matrix.hpp"

MatrixRow::MatrixRow(double* ptr, size_t _cols)
                        : row(ptr), cols_num(_cols) {}

double& MatrixRow::operator[](size_t j) {
    if (j >= cols_num) {
        throw "Error: Index out of range";
    }
    return row[j];
}

Matrix::Matrix(size_t _rows, size_t _cols)
                : rows_num(_rows), cols_num(_cols){
    values = new double [rows_num * cols_num];
    for (size_t k = 0; k < rows_num * cols_num; k++) {
        values[k] = 0;
    }
}

Matrix::Matrix(const Matrix& other) {
    rows_num = other.rows_num;
    cols_num = other.cols_num;

    values = new double [rows_num * cols_num];

    for (size_t k = 0; k < rows_num * cols_num; k++) {
        values[k] = other.values[k];
    }
}

Matrix::Matrix(initializer_list<double> store) {
    auto it = store.begin();
    rows_num = size_t(*it++);
    cols_num = size_t(*it++);

    values = new double [rows_num * cols_num];

    for (size_t i = 0; i < rows_num; i++) {
        for (size_t j = 0; j < cols_num; j++) {
            values[i * cols_num + j] = *it++;
        }
    }
}

Matrix::~Matrix() {
    delete [] values;
}

size_t Matrix::get_rows_num() {
    return rows_num;
}

size_t Matrix::get_cols_num() {
    return cols_num;
}

MatrixRow Matrix::operator[](size_t i) {
    if (i >= rows_num) {
        throw "Error: Index out of range";
    }
    MatrixRow result = MatrixRow(values + i * cols_num, cols_num);
    return result;
}

bool Matrix::operator==(const Matrix& other) {
    if (rows_num != other.rows_num) {
        return false;
    }
    if (cols_num != other.cols_num) {
        return false;
    }
    for (size_t k = 0; k < rows_num * cols_num; k++) {
        if (values[k] != other.values[k]) {
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) {
    return !(*this == other);
}

Matrix& Matrix::operator*=(double a) {
    for (size_t k = 0; k < rows_num * cols_num; k++) {
        values[k] *= a;
    }
    return *this;
}

Matrix& Matrix::operator*=(vector<double> vect) {
    if (vect.size() != cols_num) {
        throw "Error: Bad vector size";
    }
    Matrix old(*this);

    delete [] values;
    cols_num = 1;
    values = new double [rows_num * cols_num];

    for (size_t i = 0; i < rows_num; i++) {
        (*this)[i][0] = 0;
        for (size_t k = 0; k < vect.size(); k++) {
            (*this)[i][0] += old[i][k] * vect[k];
        }
    }
    return *this;
}

ostream& operator<<(ostream& out, const Matrix& value) {
    out << "size:" << value.rows_num << ' ' << value.cols_num << endl;
    for (size_t i = 0; i < value.rows_num; i++) {
        for (size_t j = 0; j < value.cols_num; j++) {
            out << value.values[i * value.cols_num + j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
    return out;
}
