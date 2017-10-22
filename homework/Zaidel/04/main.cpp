#include <iostream>
#include "Matrix.h"


void check(bool value)
{
    if (!value)
        std::cout << "error" << std::endl;
}

void checkGetSet()
{
    Matrix m(2, 3);
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
    Matrix m(2, 3);
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
    Matrix mat = Matrix::ones(2);
    mat[0][1] = -1;
    mat[1][0] = -1;

    std::vector<double> vec(2);

    vec[0] = 1;
    vec[1] = 0;

    Matrix res = vec * mat;

    check(res[0][0] == 1);
    check(res[1][0] == -1);
}

void checkVectorRightMul()
{
    Matrix mat = Matrix::ones(2);
    mat[0][1] = -1;
    mat[1][0] = -1;

    std::vector<double> vec(2);

    vec[0] = 1;
    vec[1] = 0;

    Matrix res = mat * vec;

    check(res[0][0] == 1);
    check(res[0][1] == -1);
}

void checkMatrixEq()
{
    Matrix mat1 = Matrix::ones(2);
    mat1[0][1] = -1;
    mat1[1][0] = -1;

    Matrix mat2 = Matrix::ones(2);

    check(mat1!=mat2);

    mat1 = mat2;

    check(mat1[0][0] == 1);
    check(mat1[0][1] == 0);
    check(mat1[1][1] == 1);
    check(mat1[1][0] == 0);

    check(mat1 == mat2);

}




int main() {

    checkGetSet();
    checkDoubleMult();
    checkVectorLeftMul();
    checkVectorRightMul();
    checkMatrixEq();

//    Matrix mat = Matrix::ones(3);
//    mat[0][0] = 2;
//
//    std::vector<double> vec = {1,0,0};
//
//    std::cout<<mat;
//    std::cout<<mat*10;
//    std::cout<< mat * vec;
//    std::cout<< vec * mat;
//
//    mat *= vec;
//    std::cout<< mat;

    return 0;
}