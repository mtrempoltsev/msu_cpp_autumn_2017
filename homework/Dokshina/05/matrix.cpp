#include <iostream>
#include <initializer_list>
#include <vector>

template <typename T>
class MatrixRow {
public:
    MatrixRow(T* ptr, size_t _cols)
                            : row(ptr)
                            , cols_num(_cols) {}

    T& operator[](size_t j) {
        if (j < 0 || j >= cols_num) {
            throw "Error: Index out of range";
        }
        return row[j];
    }
private:
    T *row;
    size_t cols_num;
};

template <typename T>
class Matrix {
public:


    Matrix(size_t _rows, size_t _cols)
                            : rows_num(_rows)
                            , cols_num(_cols) {
        values = new T [rows_num * cols_num];
        for (size_t k = 0; k < rows_num * cols_num; k++) {
            values[k] = 0;
        }
    }

    Matrix(std::initializer_list<T> store) {
        auto it = store.begin();
        rows_num = size_t(*it++);
        cols_num = size_t(*it++);

        values = new T [rows_num * cols_num];

        for (size_t i = 0; i < rows_num; i++) {
            for (size_t j = 0; j < cols_num; j++) {
                values[i * cols_num + j] = *it++;
            }
        }
    }

    Matrix(const Matrix<T>& other) {
        rows_num = other.rows_num;
        cols_num = other.cols_num;
        values = new T[rows_num * cols_num];

        std::copy(other.values, other.values + rows_num * cols_num, values);
    }

    Matrix(Matrix<T>&& movied) {
        values = movied.values;
        rows_num = movied.rows_num;
        cols_num = movied.cols_num;

        movied.values = nullptr;
        movied.rows_num = movied.cols_num = 0;

    }

    Matrix<T>& operator=(Matrix<T>&& movied) {
        if (this == &movied) {
            return *this;
        }
        delete[] values;
        values = movied.values;

        rows_num = movied.rows_num;
        cols_num = movied.cols_num;

        movied.values = nullptr;
        movied.rows_num = movied.cols_num = 0;
        return *this;
    }

    ~Matrix() {
        delete [] values;
    }

    size_t get_rows_num() {
        return rows_num;
    }

    size_t get_cols_num() {
        return cols_num;
    }

    Matrix<T>& operator=(const Matrix<T>& copied) {
        if (this == &copied) {
            return *this;
        }
        delete[] values;
        rows_num = copied.rows_num;
        cols_num = copied.cols_num;

        values = new T[rows_num * cols_num];
        std::copy(copied.values, copied.values + rows_num * cols_num, values);
        return *this;

    }

    MatrixRow<T> operator[](size_t i) {
        if (i < 0 || i >= rows_num) {
            throw "Error: Index out of range";
        }
        MatrixRow<T> result = MatrixRow<T>(values + i * cols_num, cols_num);
        return result;
    }

    bool operator==(const Matrix<T>& other) {
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

    bool operator!=(const Matrix<T>& other) {
        return !(*this == other);
    }

    Matrix<T>& operator*=(T a) {
        for (size_t k = 0; k < rows_num * cols_num; k++) {
            values[k] *= a;
        }
        return *this;
    }

    Matrix<T>& operator*=(std::vector<T> vect) {
        if (vect.size() != cols_num) {
            throw "Error: Bad vector size";
        }

        T* tmp_values = new T [rows_num];

        for (size_t i = 0; i < rows_num; i++) {
            tmp_values[i] = 0;
            for (size_t k = 0; k < vect.size(); k++) {
                tmp_values[i] += (*this)[i][k] * vect[k];
            }
        }
        delete[] values;
        values = tmp_values;
        cols_num = 1;

        return *this;
    }

    template<typename M>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<M>& value);

private:
    size_t rows_num;
    size_t cols_num;
    T* values;
};

template<typename M>
std::ostream& operator<<(std::ostream& out, const Matrix<M>& value) {
    out << "size:" << value.rows_num << ' ' << value.cols_num << std::endl;
    for (size_t i = 0; i < value.rows_num; i++) {
        for (size_t j = 0; j < value.cols_num; j++) {
            out << value.values[i * value.cols_num + j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return out;
}
