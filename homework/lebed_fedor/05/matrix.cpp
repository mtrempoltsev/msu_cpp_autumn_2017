#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

/**
 * Represents matrix of type T
 */
template<typename T>
class Matrix
{
    /**
     * Proxy class for access row elements (read/modify)
     * NOTE: E is defined to allow MatrixRowView<const Matrix<E>, const E>
     */
    template<typename M, typename E>
    class MatrixRowView
    {
    public:
        MatrixRowView(M& m, size_t row): source(m), choosen_row(row) {
        }

        E& operator[](size_t col_idx) {
            if (col_idx >= source.n_cols) {
                assert(!"column index out of range");
            }
            return source.data[choosen_row*source.n_cols + col_idx];
        }

    private:
        M& source;
        size_t choosen_row;
    };

public:
    Matrix(size_t n_rows, size_t n_cols): n_rows(n_rows), n_cols(n_cols) {
        data = (T *) calloc(size(), sizeof(T));
    }

    ~Matrix() {
        free(data);
    }

    Matrix(Matrix<T>& other): n_rows(other.n_rows), n_cols(other.n_cols) {
        data = (T *) malloc(sizeof(T)*size());
        memcpy(data, other.data, sizeof(T)*size());
    }

    Matrix(Matrix<T>&& other): n_rows(other.n_rows), n_cols(other.n_cols) {
        data = other.data;
        other.data = nullptr;
    }

    Matrix<T>& operator=(const Matrix& other) {
        free(data);
        n_rows = other.n_rows;
        n_cols = other.n_cols;
        data = (T *) malloc(sizeof(T)*size());
        memcpy(data, other.data, sizeof(T)*size());
        return *this;
    }

    Matrix<T>& operator=(Matrix&& other) {
        free(data);
        n_rows = other.n_rows;
        n_cols = other.n_cols;
        data = other.data;
        other.data = nullptr;
        return *this;
    }

    MatrixRowView<const Matrix<T>, const T> operator[](size_t row_idx) const {
        if (row_idx >= n_rows) {
            assert(!"index out of range");
        }
        return MatrixRowView<const Matrix<T>, const T>(*this, row_idx);
    }

    MatrixRowView<Matrix<T>, T> operator[](size_t row_idx) {
        if (row_idx >= n_rows) {
            assert(!"row index out of range");
        }
        return MatrixRowView<Matrix<T>, T>(*this, row_idx);
    }

    size_t rows() const {
        return n_rows;
    }

    size_t cols() const {
        return n_cols;
    }

    size_t size() const {
        return n_cols*n_rows;
    }

    /**
     * returns matrix Nx1,
     * where matrix[i,0] = dot product of row i of this matrix and given vector v
     */
    Matrix<T> operator*(const vector<T>& v) const {
        if(v.size() != n_cols) {
            assert(!"vector dim does not match matrix dim");
        }

        Matrix<T> result(n_rows, 1);
        for (size_t i = 0; i < n_rows; i++) {
            for (size_t j = 0; j < n_cols; j++) {
                result.data[j] += this->data[i*n_cols + j]*v[j];
            }
        }
        return result;
    }

    /**
     * same as vector operator*, but now result is stored in this matrix
     */
    Matrix<T>& operator*=(const vector<T>& v) {
        if (v.size() != n_cols) {
            assert(!"vector dim does not match matrix dim");
        }

        for (size_t i = 0; i < n_rows; i++) {
            T sum = 0;
            for (size_t j = 0; j < n_cols; j++) {
                sum += data[i*n_cols + j]*v[j];
            }
            data[i] = sum;
        }
        data = (T *) realloc(data, sizeof(T)*n_rows);
        n_cols = 1;
        return *this;
    }

    /**
     * returns scalar product of this matrix and given scalar x
     */
    Matrix<T> operator*(T x) const {
        Matrix<T> result(n_rows, n_cols);
        for (size_t i = 0; i < size(); i++) {
            result.data[i] = data[i]*x;
        }
        return result;
    }

    /**
     * same as scalar operator*, but now result is stored in this matrix
     */
    Matrix<T>& operator*=(T x) {
        for (size_t i = 0; i < size(); i++) {
            data[i] *= x;
        }
        return *this;
    }

    /**
     * indicates if this and given matrixes are equal
     */
    bool operator==(const Matrix<T>& m) const {
        if (m.n_rows != n_rows || m.n_cols != n_cols) {
            return false;
        }

        for (size_t i = 0; i < size(); i++) {
            if (data[i] != m.data[i]) {
                return false;
            }
        }
        return true;
    }

    /**
     * indicats if this and given matrixes are distinct
     */
    bool operator!=(const Matrix<T>& m) const {
        return !(m == *this);
    }

private:
    size_t n_rows;
    size_t n_cols;
    T *data;

    friend class MatrixTest;
};

/**
 * Prints matrix in human readable form
 */
template<typename T>
ostream& operator<<(ostream& stream, const Matrix<T>& m)
{
    for (size_t i = 0; i < m.rows(); i++) {
        for (size_t j = 0; j < m.cols(); j++) {
            stream << setw(5) << m[i][j] << " ";
        }
        stream << endl;
    }
    return stream;
}
