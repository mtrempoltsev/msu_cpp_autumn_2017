#include <iostream>
#include <vector>
#include <algorithm>

template <class T>
class Matrix {
std::vector<T> matrix_;
    size_t rows_;
    size_t cols_;

public:

    class ProxMatrix {
        std::vector<T>& m_; //stores ref to the whole matrix
        size_t size_; // size of a Proxy Matrix, colunms amount actually
        size_t row_; // beginning of a Proxy Matrix in m
    public:
        ProxMatrix(std::vector<T>& matrix, size_t size, size_t row) : 
            m_(matrix), size_(size), row_(row) {
        }

        T& operator[](size_t j) {
            if (size_ <= j) {
                throw("Index out of range");
            }
            return m_[row_ * size_ + j];
        }

    };

    class ConstProxMatrix {
        const std::vector<T>& const_m_; //stores const ref to the whole matrix
        size_t size_; // size of a Proxy Matrix, colunms amount actually
        size_t row_; // beginning of a Proxy Matrix in m
    public:
        ConstProxMatrix(const std::vector<T>& matrix, size_t size, size_t row) : 
            const_m_(matrix), size_(size), row_(row) {
        }

        const T& operator[](size_t j) const {
            if (size_ <= j) {
                throw("Index out of range");
            }
            return const_m_[row_ * size_ + j];
        }
    };

    Matrix(size_t rows, size_t cols) : 
        rows_(rows), cols_(cols) {
        
        matrix_.resize(rows * cols);
    }

    Matrix(const Matrix& copied) {
        rows_ = copied.get_rows_amount();
        cols_ = copied.get_cols_amount();

        matrix_.resize(rows_ * cols_);

        auto it = matrix_.begin();        
        for(size_t i = 0; i < rows_; i++) {
            for(size_t j = 0; j < cols_; j++) {
                *it++ = copied[i][j];
            }
        }
    }

    Matrix(Matrix&& moved) {
        rows_ = moved.get_rows_amount();
        cols_ = moved.get_cols_amount();

        matrix_.resize(rows_ * cols_);

        auto it = matrix_.begin();        
        for(size_t i = 0; i < rows_; i++) {
            for(size_t j = 0; j < cols_; j++) {
                *it++ = std::move(moved[i][j]);
            }
        }

    }

    Matrix& operator=(const Matrix& copied) {
        if (this == &copied) {
            return *this;
        }

        matrix_.clear();

        rows_ = copied.get_rows_amount();
        cols_ = copied.get_cols_amount();

        matrix_.resize(rows_ * cols_);

        auto it = matrix_.begin();        
        for(size_t i = 0; i < rows_; i++) {
            for(size_t j = 0; j < cols_; j++) {
                *it++ = copied[i][j];
            }
        }
        
        return *this;
    }

    Matrix& operator=(Matrix&& moved) {
        if (this == &moved) {
            return *this;
        }

        matrix_.clear();

        rows_ = moved.get_rows_amount();
        cols_ = moved.get_cols_amount();

        matrix_.resize(rows_ * cols_);

        auto it = matrix_.begin();        
        for(size_t i = 0; i < rows_; i++) {
            for(size_t j = 0; j < cols_; j++) {
                *it++ = std::move(moved[i][j]);
            }
        } 
        
        return *this;
    }

    const size_t get_rows_amount() const {
        return rows_;
    }

    const size_t get_cols_amount() const {
        return cols_;
    }
    
    friend bool operator==(const Matrix& l, const Matrix& r) { // friend -> easy to compare matrices as vectors
        if (l.rows_ != r.rows_ || l.cols_ != l.cols_) {
                return false; 
        }
        auto it_l = l.matrix_.begin();
        auto it_r = r.matrix_.begin();
        for(; (it_l < l.matrix_.end() && it_r < r.matrix_.end()); it_l++, it_r++) {
            if (*it_l != *it_r) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }

    Matrix& operator*=(const T& num) { // Matrix * T
        for(auto it = matrix_.begin(); it < matrix_.end(); it++) {
            (*it) *= num;
        }
        return (*this);
    }

    std::vector<T>& operator*=(const std::vector<T>& v) { // Matrix * vector
        if (v.size() != cols_) {
            std::cerr << "Vector size does not match. Doing nothing. Continue\n";
        }
        std::vector<T> result_v;
        result_v.resize(rows_);

        auto it = matrix_.begin();
        auto vt = result_v.begin();
        
        for(;
            (it < matrix_.end() && vt < result_v.end());
            vt++) {

            double new_value = 0;
            for(auto jt = v.begin(); jt < v.end(); jt++, it++) {
                new_value += (*it) * (*jt);
            }
            (*vt) = new_value;
        }

        matrix_.resize(result_v.size());
        matrix_ = result_v;

        cols_ = 1;

        return matrix_;
    }

    const ConstProxMatrix operator[](size_t i) const {
        if (rows_ <= i) {
            throw("Index out of range");
        }
        return ConstProxMatrix(matrix_, cols_, i);
    }

    ProxMatrix operator[](size_t i) {
        if (rows_ <= i) {
            throw("Index out of range");
        }
        return ProxMatrix(matrix_, cols_, i);
    }

};

/*==============v test v==============*/

int check(bool value, const char *msg)
{
    if (!value) {
        std::cout << msg << " error" << std::endl;
        return 1;
    }
    return 0;
}

int checkGetSizes() {
    Matrix<double> m(2, 3);
    return check(m.get_rows_amount() == 2, "Row get") +
           check(m.get_cols_amount() == 3, "Col get");
}

int checkGetSet()
{
    int errors = 0;    
    Matrix<int> m(2, 3);
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

    int x = m[1][2];

    errors += check(x == 100, "Rvalue assigning");

    return errors;
}

int checkVectMult() {
    
    Matrix<double> m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    std::vector<double> v = {1, 2, 3};
    m *= v;

    return check(m[0][0] == 14, "Vect mult") +
           check(m[1][0] == 32, "Vect mult");
}

int checkNumMult() {
    
    Matrix<int> m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    m *= 3;

    return 
        check(m[0][0] == 3, "T mult")  +
        check(m[0][1] == 6, "T mult")  +
        check(m[0][2] == 9, "T mult")  +
        check(m[1][0] == 12, "T mult") +
        check(m[1][1] == 15, "T mult") +
        check(m[1][2] == 18, "T mult");

}

int chechEqualMatrices() {
    Matrix<int> m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    Matrix<int> m1(2, 3); // same matrix
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[0][2] = 3;
    m1[1][0] = 4;
    m1[1][1] = 5;
    m1[1][2] = 6;

    Matrix<int> m2(2, 3); // same size, different values
    m2[0][0] = 1;
    m2[0][1] = 2;
    m2[0][2] = 3;
    m2[1][0] = 4;
    m2[1][1] = 5;
    m2[1][2] = 61;

    Matrix<int> m3(1, 3); // different size
    m3[0][0] = 1;
    m3[0][1] = 2;
    m3[0][2] = 3;

    return check(m == m1, "Equality") + check(m != m2, "Inequality") + check(m != m3, "Inequality");
}

int checkCopy() {
    Matrix<std::string> m2(2, 3);
    m2[0][0] = "1 ";
    m2[0][1] = "2 ";
    m2[0][2] = "3 ";
    m2[1][0] = "4 ";
    m2[1][1] = "5 ";
    m2[1][2] = "6 ";

    Matrix<std::string> m3 = m2;
    Matrix<std::string> m4(m2);

    return 
        check(m2.get_rows_amount() == 2, "Copied changed") +
        check(m2.get_cols_amount() == 3, "Copied changed") +
        check(m2[0][0] == "1 ", "Copied changed")  +
        check(m2[0][1] == "2 ", "Copied changed")  +
        check(m2[0][2] == "3 ", "Copied changed")  +
        check(m2[1][0] == "4 ", "Copied changed") +
        check(m2[1][1] == "5 ", "Copied changed") +
        check(m2[1][2] == "6 ", "Copied changed") +

        check(m3.get_rows_amount() == 2, "Copy assignment") +
        check(m3.get_cols_amount() == 3, "Copy assignment") +
        check(m3[0][0] == "1 ", "Copy assignment")  +
        check(m3[0][1] == "2 ", "Copy assignment")  +
        check(m3[0][2] == "3 ", "Copy assignment")  +
        check(m3[1][0] == "4 ", "Copy assignment") +
        check(m3[1][1] == "5 ", "Copy assignment") +
        check(m3[1][2] == "6 ", "Copy assignment") +

        check(m4.get_rows_amount() == 2, "Copy constructor") +
        check(m4.get_cols_amount() == 3, "Copy constructor") +
        check(m4[0][0] == "1 ", "Copy constructor")  +
        check(m4[0][1] == "2 ", "Copy constructor")  +
        check(m4[0][2] == "3 ", "Copy constructor")  +
        check(m4[1][0] == "4 ", "Copy constructor") +
        check(m4[1][1] == "5 ", "Copy constructor") +
        check(m4[1][2] == "6 ", "Copy constructor");
}

int checkMove() {
    Matrix<std::string> m1(2, 3);
    m1[0][0] = "1 ";
    m1[0][1] = "2 ";
    m1[0][2] = "3 ";
    m1[1][0] = "4 ";
    m1[1][1] = "5 ";
    m1[1][2] = "6 ";

    Matrix<std::string> m2(2, 3);
    m2[0][0] = "1 ";
    m2[0][1] = "2 ";
    m2[0][2] = "3 ";
    m2[1][0] = "4 ";
    m2[1][1] = "5 ";
    m2[1][2] = "6 ";

    Matrix<std::string> m3 = std::move(m1);
    Matrix<std::string> m4(std::move(m2));

    return

        check(m3.get_rows_amount() == 2, "Move assignment") +
        check(m3.get_cols_amount() == 3, "Move assignment") +
        check(m3[0][0] == "1 ", "Move assignment")  +
        check(m3[0][1] == "2 ", "Move assignment")  +
        check(m3[0][2] == "3 ", "Move assignment")  +
        check(m3[1][0] == "4 ", "Move assignment") +
        check(m3[1][1] == "5 ", "Move assignment") +
        check(m3[1][2] == "6 ", "Move assignment") +

        check(m4.get_rows_amount() == 2, "Move constructor") +
        check(m4.get_cols_amount() == 3, "Move constructor") +
        check(m4[0][0] == "1 ", "Move constructor")  +
        check(m4[0][1] == "2 ", "Move constructor")  +
        check(m4[0][2] == "3 ", "Move constructor")  +
        check(m4[1][0] == "4 ", "Move constructor") +
        check(m4[1][1] == "5 ", "Move constructor") +
        check(m4[1][2] == "6 ", "Move constructor");

}

int main() {

    try {
        int errors = 0;
        errors +=
            checkGetSizes() +
            checkGetSet()   +
            checkVectMult() +
            checkNumMult()  +
            chechEqualMatrices() +
            checkCopy() +
            checkMove();

        std::cout << errors << " error(s) found\n";

    } catch (const char *exeption) {
        std::cerr << exeption << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Ooops! Something unexpected" << std::endl;
        return 2;
    }

    return 0;
}
