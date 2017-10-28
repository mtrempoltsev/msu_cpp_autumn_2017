#include<iostream>
#include<cstdlib>
#include<vector>
#include<cstring>
#include<cassert>
#include<string>
template <typename T>
class Matrix {
    protected:
        size_t row_count,
            column_count;
        class Matrix_row {
            T *arr;
            size_t len;
            
            public:
            Matrix_row() 
            {
                len = 0;
                arr = (T*)malloc(1);
            }
            Matrix_row(size_t colc)
            {
                len = colc;
                arr = (T*)calloc(colc, sizeof(arr[0]));
            }
            Matrix_row(size_t size, T *in_arr)
            {
                len = size;
                arr = (T*)malloc(size * sizeof(in_arr[0]));
                memcpy(arr, in_arr, size * sizeof(in_arr[0]));
            }
            Matrix_row&
            operator=(const Matrix_row &copied)
            {
                free(arr);
                len = copied.len;
                arr = (T*)malloc(len*sizeof(arr));
                memcpy(arr, copied.arr, len * sizeof(arr[0]));
                return *this;
            }
            T& 
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
        Matrix(size_t rowsc, size_t colsc, T *arr)
        { 
            row_count = rowsc;
            column_count = colsc;
            for (size_t i = 0; i < rowsc; i++) {
                rows.push_back(new Matrix_row(colsc, (arr + i * colsc)));
            }
        }
        Matrix(const Matrix<T>& m) = default;
        Matrix(Matrix<T>&& m) = default;

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
        

        Matrix<T>&
        operator=(const Matrix<T> &copied)
        {
            for (auto o : rows) {
                delete o;
            }
            size_t rc = copied.row_count,
                   cc = copied.column_count;
            row_count = rc;
            column_count = cc;
            rows.resize(0);
            for (size_t i = 0; i < rc; i++) {
                Matrix_row *mtr = new Matrix_row();
                *mtr = copied[i];
                rows.push_back(mtr);
            }
            
            return *this;                                
        }

        Matrix<T>& 
        operator=(Matrix<T> &&movied)
        {
            for (auto o : rows) {
                delete o;
            }
            size_t rc = movied.get_row_count(),
                   cc = movied.get_column_count();
            row_count = rc;
            column_count = cc;
            rows = movied.rows;
            movied.rows.clear();
            return *this;                           
        }

        const Matrix_row& 
        operator[](size_t i) const
        {
            assert(!(i >= row_count));
            return *rows[i]; 
        }
        
        bool
        operator==(const Matrix<T>& other) const 
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
        operator!=(const Matrix<T>& other) const
        {
            return !(*this == other);
        }

        Matrix<T>
        operator *(const T b) const
        { 
            Matrix<T> result = Matrix<T>(row_count, column_count);
            for (size_t i = 0; i < row_count; i++) {
                for (size_t j = 0; j < column_count; j++) {
                    result[i][j] = (*this)[i][j] * b;
                }
            }
            return result;
        }

        // assert vector is matrix n*1
        Matrix<T>
        operator*(const std::vector<T> b) const
        {
            assert(!(b.size() != column_count));
            Matrix<T> result = Matrix<T>(row_count, 1);
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
    Matrix<double> m = Matrix<double>(2, 3);
    m[0][0] = 1.5;
    m[0][1] = 2.5;
    m[0][2] = 3.5;
    m[1][0] = 4.5;
    m[1][1] = 5.5;
    m[1][2] = 6.5;

    check(m[0][0] == 1.5);
    check(m[0][1] == 2.5);
    check(m[0][2] == 3.5);
    check(m[1][0] == 4.5);
    check(m[1][1] == 5.5);
    check(m[1][2] == 6.5);

    m[1][2] = 100;

    check(m[1][2] == 100, "error in reset");
    double a[2][3] = {{1,2,3},{4,5,6}};
    Matrix<double> m1 = Matrix<double>(2, 3, (double *)a);
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
    Matrix<double> m1 = Matrix<double>(2, 3, (double *)a);
    Matrix<double> m2 = m1 * 2;
    check(m2[0][0] == 2, "m1");
    check(m2[0][1] == 4, "m2");
    check(m2[0][2] == 6, "m3");
    check(m2[1][0] == 8, "m4");
    check(m2[1][1] == 10, "m5");
    check(m2[1][2] == 12, "m6");
    
    std::vector<double> tst = {2, 2, 2};
    Matrix<double> m3 = m1 * tst; 
    check(m3[0][0] == 12, "v1");
    check(m3[1][0] == 30, "v2");
}

void
check_equation()
{
    
    double a[2][3] = {{1,2,3},{4,5,6}};
    Matrix<double> m1 = Matrix<double>(2, 3, (double *)a);
    Matrix<double> m2 = Matrix<double>(2, 3, (double *)a);
    check(m1 == m2, "e1");
    m1[0][0] = 0;
    check(m1 != m2, "e2");
}

void
check_move()
{
    double a[2][3] = {{1,2,3},{4,5,6}};
    Matrix<double> *m1 = new Matrix<double>(2, 3, (double *)a);
    Matrix<double> m2 = Matrix<double>(2, 3);
    m2 = std::move(*m1);
    check(m2[0][0] == 1, "move1");
    check(m2[0][1] == 2, "move2");
    check(m2[0][2] == 3, "move3");
    check(m2[1][0] == 4, "move4");
    check(m2[1][1] == 5, "move5");
    check(m2[1][2] == 6, "move6"); 
    delete m1;
    check(m2[0][0] == 1, "2move1");
    check(m2[0][1] == 2, "2move2");
    check(m2[0][2] == 3, "2move3");
    check(m2[1][0] == 4, "2move4");
    check(m2[1][1] == 5, "2move5");
    check(m2[1][2] == 6, "2move6"); 
}

void
check_copy()
{
    double a[2][3] = {{1,2,3},{4,5,6}};
    Matrix<double> *m1 = new Matrix<double>(2, 3, (double *)a);
    
    Matrix<double> m2 = Matrix<double>(2, 3);
    
    m2 = *m1;
    check(m2[0][0] == 1, "copy1");
    check(m2[0][1] == 2, "copy2");
    check(m2[0][2] == 3, "copy3");
    check(m2[1][0] == 4, "copy4");
    check(m2[1][1] == 5, "copy5");
    check(m2[1][2] == 6, "copy6"); 
    (*m1)[0][0] = 100;
    check(m2[0][0] == 1, "2copy1");
}

int
main()
{
    std::cout << "Tests starts" << std::endl;
    check_get_set();
    check_multiplication();
    check_equation();
    check_move();
    check_copy();
    std::cout << "Tests ends" << std::endl;
    return 0;
}
