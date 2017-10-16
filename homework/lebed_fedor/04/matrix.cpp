#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

/**
 * Represents matrix of type double
 */ 
class Matrix
{
    /**
     * Proxy class for access row elements (read/modify)
     */
    class MatrixRowView
    {
    public:
        MatrixRowView(Matrix& m, size_t row): source(m), choosen_row(row) {
        }

        double& operator[](size_t col_idx) {
            if (col_idx >= source.n_cols) {
                assert(!"column index out of range");
            }
            return source.data[choosen_row*source.n_cols + col_idx];
        }

    private:
        Matrix& source;
        size_t choosen_row;
    };

    /**
     * Proxy class for access row elements (read)
     */
    class ConstMatrixRowView
    {
    public:
        ConstMatrixRowView(const Matrix& m, size_t row): source(m), choosen_row(row) {
        }

        const double& operator[](size_t col_idx) const {
            if (col_idx >= source.n_cols) {
                assert(!"column index out of range");
            }
            return source.data[choosen_row*source.n_cols + col_idx];
        }

    private:
        const Matrix& source;
        size_t choosen_row;
    };

public:
    Matrix(size_t n_rows, size_t n_cols): n_rows(n_rows), n_cols(n_cols), data(n_rows*n_cols) {
    }

    ConstMatrixRowView operator[](size_t row_idx) const {
        if (row_idx >= n_rows) {
            assert(!"index out of range");
        }
        return ConstMatrixRowView(*this, row_idx);
    }

    MatrixRowView operator[](size_t row_idx) {
        if (row_idx >= n_rows) {
            assert(!"row index out of range");
        }
        return MatrixRowView(*this, row_idx);
    }

    size_t rows() const {
        return n_rows;
    }

    size_t cols() const {
        return n_cols;
    }

    /**
     * returns matrix Nx1, 
     * where matrix[i,0] = dot product of row i of this matrix and given vector v 
     */
    Matrix operator*(const vector<double>& v) const {
        if(v.size() != n_cols) {
            assert(!"vector dim does not match matrix dim");
        }
        
        Matrix result(n_rows, 1);
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
    Matrix& operator*=(const vector<double>& v) {
        if (v.size() != n_cols) {
            assert(!"vector dim does not match matrix dim");
        }
        
        for (size_t i = 0; i < n_rows; i++) {
            double sum = 0;
            for (size_t j = 0; j < n_cols; j++) {
                sum += data[i*n_cols + j]*v[j];
            }
            data[i] = sum;
        }
        data.resize(v.size());
        n_cols = 1;
        return *this;
    }

    /**
     * returns scalar product of this matrix and given scalar x
     */
    Matrix operator*(double x) const {
        Matrix result(n_rows, n_cols);
        for (size_t i = 0; i < data.size(); i++) {
            result.data[i] = data[i]*x;
        }
        return result;
    }

    /**
     * same as scalar operator*, but now result is stored in this matrix
     */ 
    Matrix& operator*=(double x) {
        for (size_t i = 0; i < data.size(); i++) {
            data[i] *= x;
        }
        return *this;
    }

    /**
     * indicates if this and given matrixes are equal
     * NOTE: doubles are compared by bits
     */ 
    bool operator==(const Matrix& m) const {
        if (m.n_rows != n_rows || m.n_cols != n_cols) {
            return false;
        }

        return memcmp((char *) m.data.data(), (char *) data.data(), sizeof(data[0])*data.size()) == 0;
    }

    /**
     * indicats if this and given matrixes are distinct
     * NOTE: doubles are compared by bits
     */
    bool operator!=(const Matrix& m) const {
        return !(m == *this);
    }

private:
    size_t n_rows;
    size_t n_cols;
    vector<double> data;
};

/**
 * Prints matrix in human readable form
 */
ostream& operator<<(ostream& stream, const Matrix& m)
{
    for (size_t i = 0; i < m.rows(); i++) {
        for (size_t j = 0; j < m.cols(); j++) {
            stream << setw(5) << m[i][j] << " ";
        }
        stream << endl;
    }
    return stream;
}
