#include <iostream>
#include <exception>
#include <cstdio>
#include <functional>

#include "matrix.h"

using namespace std;
/* Нужно написать класс-матрицу, тип элементов double.
 * В конструкторе задается количество рядов и строк.
 * Поддерживаются оперции:
 *      получить количество строк/столбцов,
 *      получить конкретный элемент,
 *      умножить на вектор (в качестве вектора использовать класс std::vector<double>),
 *      умножить на число,
 *      сравнение на равенство/неравенство.
 * В случае ошибки выхода за границы достаточно такой
 * обработки ошибки: assert(!"index out of range")
 */

// [cols][rows]
//--------------------------------------------

void check_values_equal(double result, int value)
{
    try
    {
        if (almost_equal(result, value))
            std::cout << "Passed: " << result << " = " << value << std::endl;
        else
            std::cout << "Failed: " << result << " (" << value << " expected)" << std::endl;
    }
    catch(char const* msg)
    {
        std::cout << "Failed: " << result << " Exception message: " << msg << " (" << value << " expected)" <<std::endl;
    }
}

void check_invalid(std::function <void ()> func)
{
    try
    {
        func();
    }
    catch(char const* msg)
    {
        std::cout << "Passed: exception message " << msg << std::endl;
        return;
    }
    std::cout << "Failed: exception message expected." <<std::endl;
}

//--------------------------------------------

void check(bool value)
{
    if (!value)
         cout << "error" <<  endl;
}

void checkConstructor()
{
    check_invalid([](){return Matrix(0, 1);});
    check_invalid([](){return Matrix(1, 0);});

    Matrix m = Matrix(3, 2);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;
    check_values_equal(m[0][0], 1);
    check_values_equal(m[0][1], 2);
    check_values_equal(m[0][2], 3);
    check_values_equal(m[1][0], 4);
    check_values_equal(m[1][1], 5);
    check_values_equal(m[1][2], 6);

    check_invalid([&m](){return m[1][3];});
    check_invalid([&m](){return m[2][1];});

    double arr[] = {1, 2, 3, 4, 5, 6};
    m = Matrix(3, 2, arr);
    check_values_equal(m[0][0], 1);
    check_values_equal(m[0][1], 2);
    check_values_equal(m[0][2], 3);
    check_values_equal(m[1][0], 4);
    check_values_equal(m[1][1], 5);
    check_values_equal(m[1][2], 6);

    check_invalid([&m](){return m[1][3];});
    check_invalid([&m](){return m[2][1];});

    Matrix m_copy = Matrix(m);
    check_values_equal(m_copy[0][0], 1);
    check_values_equal(m_copy[0][1], 2);
    check_values_equal(m_copy[0][2], 3);
    check_values_equal(m_copy[1][0], 4);
    check_values_equal(m_copy[1][1], 5);
    check_values_equal(m_copy[1][2], 6);

    check_invalid([&m_copy](){return m_copy[1][3];});
    check_invalid([&m_copy](){return m_copy[2][1];});

    m_copy = m;
    check_values_equal(m_copy[0][0], 1);
    check_values_equal(m_copy[0][1], 2);
    check_values_equal(m_copy[0][2], 3);
    check_values_equal(m_copy[1][0], 4);
    check_values_equal(m_copy[1][1], 5);
    check_values_equal(m_copy[1][2], 6);

    check_invalid([&m_copy](){return m_copy[1][3];});
    check_invalid([&m_copy](){return m_copy[2][1];});

    cout << endl << "----------------" << endl << "Init Passed." << endl << "----------------" << endl;

}


void checkGetSet()
{
    Matrix m = Matrix(3, 2, 1);

    m.set_element(1, 1, 10);
    check_values_equal(m.get_element(1, 1), 10);

    m[1][2] = 100;
    check_values_equal(m[1][2], 100);

    cout << endl << "----------------" << endl << "GetSet Passed." << endl << "----------------" << endl;

}


void checkGetSizes()
{
    Matrix m = Matrix(3, 2, 1);

    check_values_equal(m.get_column_size(), 3); // size of column == number of rows in matrix
    check_values_equal(m.get_rows_size(), 2);

    cout << endl << "----------------" << endl << "GetSizes Passed." << endl << "----------------"  << endl;

}

void checkMult()
{
    double arr[] = {1, 2, 3, 4, 5, 6};
    Matrix m = Matrix(3, 2, arr);
    m *= 10;
    check_values_equal(m[0][0], 10);
    check_values_equal(m[0][1], 20);
    check_values_equal(m[0][2], 30);
    check_values_equal(m[1][0], 40);
    check_values_equal(m[1][1], 50);
    check_values_equal(m[1][2], 60);

    vector<double> vector_right = {1};
    check_invalid([&m, &vector_right](){return m *= vector_right;});

    vector_right = {1, 1};
    m *= vector_right;
    check_values_equal(m[0][0], 50);
    check_values_equal(m[0][1], 70);
    check_values_equal(m[0][2], 90);

    vector_right = {1, 1, 1};
    check_invalid([&m, &vector_right](){return m *= vector_right;});

    cout << endl << "----------------" << endl << "Mult Passed." << endl << "----------------" << endl << endl;

}

void checkComparison()
{
    Matrix m1 = Matrix(3, 2, 1);
    Matrix m2 = Matrix(3, 2, 1);
    Matrix m3 = Matrix(2, 2, 1);
    Matrix m4 = Matrix(3, 2, 10);

    check(m1 == m2);
    check(m1 != m3);

    m2 *= 10;

    check(m1 != m2);
    check(m2 == m4);

    cout << endl << "----------------" << endl << "Comparison Passed." << endl  << "----------------" << endl << endl;

}

//--------------------------------------------
int main()
{
    try
    {
        checkConstructor();
        checkGetSet();
        checkGetSizes();
        checkMult();
        checkComparison();
    }
    catch(char const* msg)
    {
         cout << " Exception message: " << msg << endl;
    }
    return 0;
}
