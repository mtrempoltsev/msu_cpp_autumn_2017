#include <iostream>
#include "Matrix.h"


void check(bool value)
{
    if (!value)
        std::cout << "error" << std::endl;
}

void checkGetSet()
{
    std::cout<<"checkGetSet"<< std::endl;
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

void checkDoubleMult()
{
    std::cout<<"checkDoubleMult"<< std::endl;
    Matrix<double> m(2, 3);
    m[0][0] = 1;
    m[0][1] = 1;
    m[0][2] = 1;
    m[1][0] = 1;
    m[1][1] = 1;
    m[1][2] = 1;

    m *= 4;

    for (size_t i = 0; i < m.getWidth(); ++i) {
        for (size_t j = 0; j < m.getHeight(); ++j) {
            check(m[i][j] == 4);
        }
    }
}


void checkVectorLeftMul()
{
    std::cout<<"checkVectorLeftMul"<< std::endl;
    Matrix<double> mat = Matrix<double>::ones(2);
    mat[0][1] = -1;
    mat[1][0] = -1;

    std::vector<double> vec(2);

    vec[0] = 1;
    vec[1] = 0;

    Matrix<double> res = vec * mat;

    check(res[0][0] == 1);
    check(res[1][0] == -1);
}

void checkVectorRightMul()
{
    std::cout<<"checkVectorRightMul"<< std::endl;
    Matrix<double> mat = Matrix<double>::ones(2);
    mat[0][1] = -1;
    mat[1][0] = -1;

    std::vector<double> vec(2);

    vec[0] = 1;
    vec[1] = 0;

    Matrix<double> res = mat * vec;

    check(res[0][0] == 1);
    check(res[0][1] == -1);
}

void checkMatrixEq()
{
    std::cout<<"checkMatrixEq"<< std::endl;
    Matrix<double> mat1 = Matrix<double>::ones(2);
    mat1[0][1] = -1;
    mat1[1][0] = -1;

    Matrix<double> mat2 = Matrix<double>::ones(2);

    check(mat1!=mat2);

    mat1 = mat2;

    check(mat1[0][0] == 1);
    check(mat1[0][1] == 0);
    check(mat1[1][1] == 1);
    check(mat1[1][0] == 0);

    check(mat1 == mat2);

}


void checkMoving()
{
    std::cout<<"checkMoving"<< std::endl;
    Matrix<double> m1 = Matrix<double>::ones(3);

    Matrix<double> m2 = std::move(m1);

    check(m1.isEmpty());
    check(!m2.isEmpty());
    check(m2[0][0] == 1);
    check(m2[0][1] == 0);
    check(m2[1][0] == 0);
    check(m2[1][1] == 1);

    m1 = std::move(m2);

    check(m2.isEmpty());
    check(!m1.isEmpty());
    check(m1[0][0] == 1);
    check(m1[0][1] == 0);
    check(m1[1][0] == 0);
    check(m1[1][1] == 1);
}



int main() {

    checkGetSet();
    checkDoubleMult();
    checkVectorLeftMul();
    checkVectorRightMul();
    checkMatrixEq();
    checkMoving();


    return 0;
}
