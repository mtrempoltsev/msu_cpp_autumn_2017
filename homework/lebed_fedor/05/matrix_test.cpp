#include <iostream>
#include <cassert>
#include <vector>
#include "matrix.cpp"

#define check(expr) check_(expr, __LINE__, __func__)
void check_(bool value, int line, const char *func_name)
{
    if (!value) {
        std::cout << "Error " << func_name << ":" << line << endl;
    }
}

/**
 * Class allowed to access internals of Matrix
 * and provides tests for numberic Matrixes 
 */
class MatrixTest
{
public:
   template<typename T>
   static void checkGetSet()
        {
            Matrix<double> m(2, 3);
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

   template<typename T>
   static void checkRowsColsCount()
        {
            Matrix<T> m(0, 0);
            check(m.rows() == 0);
            check(m.cols() == 0);

            Matrix<T> n(10, 20);
            check(n.rows() == 10);
            check(n.cols() == 20);
        }

   template<typename T>
   static void checkMulNew()
        {
            Matrix<T> m(3, 3);
            m[0][0] = 1;
            m[1][1] = 2;
            m[2][2] = 4;

            vector<T> v{4, 2, 1};
    
            Matrix<T> vector_mul = m*v;
            Matrix<T> scalar_mul = m*3;

            for (size_t i  = 0; i < m.rows(); i++) {
                check(vector_mul[i][0] == 4);
                check(scalar_mul[i][i] == 3*m[i][i]);
            }
        }

   template<typename T>
   static void checkVectorMulSelf()
        {
            Matrix<T> m(3, 3);
            m[0][0] = 1;
            m[1][1] = 2;
            m[2][2] = 4;

            vector<T> v{4, 2, 1};
            m *= v;
    
            for (size_t i  = 0; i < m.rows(); i++) {
                check(m[i][0] == 4);
            }
        }

   template<typename T>
   static void checkScalarMulSelf()
        {
            Matrix<T> m(3, 3);
            m[0][0] = 1;
            m[1][1] = 2;
            m[2][2] = 3;

            m *= 3;
    
            for (size_t i  = 0; i < m.rows(); i++) {
                check(m[i][i] == T(3*(i+1)));
            }   
        }

   template<typename T>
   static void checkComp()
        {
            Matrix<T> m1(2, 3);
            Matrix<T> m2(3, 2);

            check(!(m1 == m2));
            check(m1 != m2);

            Matrix<T> m3(2, 3);
            Matrix<T> m4(2, 3);
            for (size_t i = 0; i < m1.rows(); i++) {
                for (size_t j = 0; j < m1.cols(); j++) {
                    m1[i][j] = T(i - j);
                    m3[i][j] = T(i + j);
                    m4[i][j] = T(i + j);
                }
            }
            check(m1 != m3);
            check(!(m1 == m3));
            check(m1 != m4);
            check(!(m1 == m4));
            check(m3 == m4);
            check(!(m3 != m4));
        }

   template<typename T>
   static void checkCopy()
        {
            Matrix<T> m1(2, 3);
            m1[1][1] = 5;
            Matrix<T> m2 = m1;
            check(m1 == m2);
        }

   template<typename T>
   static void checkMove() {
        Matrix<T> m1(2, 3);
        m1[1][1] = 5;
        Matrix<T> m2 = move(m1);
        check(m1.data == nullptr);
        check(m2[1][1] == 5);
    }

    template<typename T>
    static void checkAssignCopy() {
        Matrix<T> m1(2, 3);
        Matrix<T> m2(3, 2);

        check(m1 != m2);
        m1 = m2;
        check(m1 == m2);
        m1[0][0] = 1;
        check(m1 != m2);
    }

    template<typename T>
    static void checkAssignMove() {
        Matrix<T> m1(2, 3);
        Matrix<T> m2(3, 2);
        m2[1][1] = 5;

        check(m1 != m2);
        m1 = move(m2);
        check(m2.data == nullptr);
        check(m1[1][1] == 5);
    }
};

template<typename T>
void test()
{
    MatrixTest::checkGetSet<T>();
    MatrixTest::checkRowsColsCount<T>();
    MatrixTest::checkMulNew<T>();
    MatrixTest::checkVectorMulSelf<T>();
    MatrixTest::checkScalarMulSelf<T>();
    MatrixTest::checkComp<T>();
    MatrixTest::checkCopy<T>();
    MatrixTest::checkMove<T>();
    MatrixTest::checkAssignCopy<T>();
    MatrixTest::checkAssignMove<T>();
}

int main()
{
    test<double>();
    test<int>();
    test<char>();
}
