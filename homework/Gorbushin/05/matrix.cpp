#include <iostream>
#include <vector>
#include <string>

template <class T>
class ProxyMatrix {
public:
    // Constructor from array (in fact - row of matrix) and size of this row
    ProxyMatrix (T *array, size_t size) {
        _array = array;
        _size = size;
    }

    // get elem by index const
    const T & operator[] (size_t j) const {
        if (j >= _size) {
            char error[200];
            sprintf(error, "%s%zu%s%zu\n", "index out of range, try get: ", j, " max: ", _size);
            throwError(std::string(error));
        }

        return _array[j];
    }
    
    // non const
    T & operator[] (size_t j) {
        if (j >= _size) {
            char error[200];
            sprintf(error, "%s%zu%s%zu\n", "index out of range, try get: ", j, " max: ", _size);
            throwError(std::string(error));
        }

        return _array[j];
    }

    // destructor
    ~ProxyMatrix() {}
private:
    size_t _size;
    T *_array;
    static void throwError(std::string &&s) {
        throw s;
    }
};

template <class T>
class Matrix {
public:
    // Empty constructor
    Matrix(): _rows(0), _cols(0), _array(nullptr) {}

    // By dimension
    Matrix(size_t r, size_t c): _rows(r), _cols(c) {
        _array = new T[r * c];
    }

    // Copy constructor
    Matrix(const Matrix & copy_from) {
        _rows = copy_from._rows;
        _cols = copy_from._cols;
        _array = new T[_rows * _cols];
        for (size_t i = 0; i < _rows * _cols; i++) {
            _array[i] = copy_from._array[i];
        }
    }


    // move constructor
    Matrix (Matrix && from) {
        _array = from._array;
        _rows = from._rows;
        _cols = from._cols;

        from._array = nullptr;
		
        return *this;
    }

    // move assignment
    Matrix& operator=(Matrix && from) {
        if (this == &from)
            return *this;

        _array = from._array;
        _rows = from._rows;
        _cols = from._cols;

        from._array = nullptr;

        return *this;
    }

    // Assigment opertor
    Matrix& operator=(const Matrix & move_from) {
        if (this == &move_from)
            return *this;

        delete[] _array;
        _rows = move_from._rows;
        _cols = move_from._cols;
        _array = new T[_rows * _cols];
        for (size_t i = 0; i < _rows * _cols; i++) {
            _array[i] = move_from._array[i];
        }
        return *this;
    }

    // For output matrix
    friend std::ostream & operator<<(std::ostream & out, const Matrix & matrix) {
        for (size_t i = 0; i < matrix._rows; i++) {
            for (size_t j = 0; j < matrix._cols; j++) {
                out << matrix._array[i * matrix._cols + j] << " ";
            }
            out << std::endl;
        }
        return out;
    }

    // Get [i][j] element
    const ProxyMatrix<T> operator[] (size_t row_num) const {
        if (row_num >= _rows) {
            char error[200];
            sprintf(error, "%s%lu%s%zu\n", "index out of range in row, try get: ", row_num, " max: ", _rows);
            throwError(std::string(error));
        }
     
        return ProxyMatrix<T>(_array + (row_num * _cols), _cols);
    }

    ProxyMatrix<T> operator[] (size_t row_num) {
        if (row_num >= _rows) {
            char error[200];
            sprintf(error, "%s%lu%s%zu\n", "index out of range in row, try get: ", row_num, " max: ", _rows);
            throwError(std::string(error));
        }

        return ProxyMatrix<T>(_array + (row_num * _cols), _cols);
    }

    // Multiply by number
    Matrix operator*= (T k) {
        for (size_t i = 0; i < _rows * _cols; i++) {
            this->_array[i] *= k;
        }
        return *this;
    }
    
    Matrix operator* (T k) {
        Matrix res(*this);
        res *= k;
        return res;
    }

    // Multiply by vector
    Matrix operator*= (const std::vector<T> &v) {
        if (_cols != v.size()) {
            char error[200];
            sprintf(error, "%s%lu%s%zu\n", "Dimension of vector is not equal columns in matrix, vector: ", v.size(), " matrix: ", _cols);
            throwError(std::string(error));
        }

        T * new_array = new T[_rows];
        for (size_t i = 0; i < _rows; i++) {
            T to_add = T();
            for (size_t j = 0; j < _cols; j++) {
                to_add += _array[i * _cols + j] * v[j];
            }
            new_array[i] = to_add;
        }
        delete[] _array;
        _array = new_array;
        _cols = 1;
        return *this;
    }

    Matrix operator* (const std::vector<T> &v) {
        if (_cols != v.size()) {
            char error[200];
            sprintf(error, "%s%lu%s%zu\n", "Dimension of vector is not equal columns in matrix, vector: ", v.size(), " matrix: ", _cols);
            throwError(std::string(error));
        }

        Matrix res(*this);
        res *= v;
        return res;
    }
    
    // Compare operator
    bool operator== (Matrix & matrix) {
        if (_cols != matrix._cols || _rows != matrix._rows) {
            return false;
        }

        for (size_t i = 0; i < _rows * _cols; i++) {
            if (_array[i] != matrix._array[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!= (Matrix & matrix) {
        return !(*this == matrix);
    }

    // Getters
    size_t cols() const {
        return _cols;
    } 

    size_t rows() const {
        return _rows;
    }

    // destructor
    ~Matrix() {
        delete[] _array;
    }
private:
    size_t _rows, _cols;
    T *_array;
    static void throwError(std::string &&s) {
        throw s;
    }
};
