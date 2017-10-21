#include<iostream>
#include<cstdlib>
#include<vector>
#include<cstring>
#include<cassert>
#include<string>
class Matrix {
    protected:
        size_t row_count,
            column_count;

        class Matrix_row {
            double *arr;
            size_t len;
            
            public:
            Matrix_row(size_t colc)
            {
                len = colc;
                arr = (double*)calloc(colc, sizeof(arr[0]));
            }
            Matrix_row(size_t size, double *in_arr)
            {
                len = size;
                arr = (double*)malloc(size * sizeof(in_arr[0]));
                memcpy(arr, in_arr, size * sizeof(in_arr[0]));
            }
            double& 
            operator[](size_t j) const
            {
                assert(!(j >= len));
                return arr[j];
            }
            ~Matrix_row() {
                free(arr);
            }
        };
        std::vector<Matrix_row*> rows;
    public:
        Matrix(size_t rowc, size_t colc)
        {
            row_count = rowc;
            column_count = colc;
            for (size_t i = 0; i < rowc; i++) {
                rows.push_back(new Matrix_row(colc));
            }
        }
        Matrix(size_t rowsc, size_t colsc, double *arr)
        { 
            row_count = rowsc;
            column_count = colsc;
            for (size_t i = 0; i < rowsc; i++) {
                rows.push_back(new Matrix_row(colsc, (arr + i * colsc)));
            }
        }

        size_t 
        get_column_count() const
        {
            return column_count;
        }
        size_t
        get_row_count() const
        {
            return row_count;
        }

        const Matrix_row& 
        operator[](size_t i) const
        {
            assert(!(i >= row_count));
            return *rows[i]; 
        }
        
        bool
        operator==(const Matrix& other) const 
        {
            if (other.get_column_count() != column_count || other.get_row_count() != row_count) {
                return false;
            }
            for (size_t i = 0; i < row_count; i++) {
                for (size_t j = 0; j < column_count; j++) {
                    if ((*this)[i][j] != other[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }

        bool
        operator!=(const Matrix& other) const
        {
            return !(*this == other);
        }

        Matrix
        operator *(const double b) const
        { 
            Matrix result = Matrix(row_count, column_count);
            for (size_t i = 0; i < row_count; i++) {
                for (size_t j = 0; j < column_count; j++) {
                    result[i][j] = (*this)[i][j] * b;
                }
            }
            return result;
        }

        // assert vector is matrix n*1
        Matrix
        operator*(const std::vector<double> b) const
        {
            assert(!(b.size() != column_count));
            Matrix result = Matrix(row_count, 1);
            for (size_t i = 0; i < row_count; i++) {
                for (size_t j = 0; j < column_count; j++) {
                    result[i][0] += (*this)[i][j] * b[j];
                }
            }
            return result;
        }

        ~Matrix()
        {
            for (auto o : rows) {
                delete o;
            }
        }
};

void
check(bool value, std::string s = "error")
{
    if (!value)
        std::cout << s << std::endl;
}

void
check_get_set()
{
    Matrix m = Matrix(2, 3);
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

    check(m[1][2] == 100, "error in reset");
    double a[2][3] = {{1,2,3},{4,5,6}};
    Matrix m1 = Matrix(2, 3, (double *)a);
    check(m1[0][0] == 1, "a1");
    check(m1[0][1] == 2, "a2");
    check(m1[0][2] == 3, "a3");
    check(m1[1][0] == 4, "a4");
    check(m1[1][1] == 5, "a5");
    check(m1[1][2] == 6, "a6");
   
}

void
check_multiplication() 
{
    double a[2][3] = {{1,2,3},{4,5,6}};
    Matrix m1 = Matrix(2, 3, (double *)a);
    Matrix m2 = m1 * 2;
    check(m2[0][0] == 2, "m1");
    check(m2[0][1] == 4, "m2");
    check(m2[0][2] == 6, "m3");
    check(m2[1][0] == 8, "m4");
    check(m2[1][1] == 10, "m5");
    check(m2[1][2] == 12, "m6");
    
    std::vector<double> tst = {2, 2, 2};
    Matrix m3 = m1 * tst; 
    check(m3[0][0] == 12, "v1");
    check(m3[1][0] == 30, "v2");
}

void
check_equation()
{
    
    double a[2][3] = {{1,2,3},{4,5,6}};
    Matrix m1 = Matrix(2, 3, (double *)a);
    Matrix m2 = Matrix(2, 3, (double *)a);
    check(m1 == m2, "e1");
    m1[0][0] = 0;
    check(m1 != m2, "e2");
}

int
main()
{
    std::cout << "Tests starts" << std::endl;
    check_get_set();
    check_multiplication();
    check_equation();
    std::cout << "Tests ends" << std::endl;
    return 0;
}
