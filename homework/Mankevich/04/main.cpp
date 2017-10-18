#include "matrix.hpp"


void check(bool value){
    if (!value){
        std::cout << "error" << std::endl;
    }
}

void check_get_set(){
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
    
    m.set_value(10);
    check(m[0][0] == 10);
    check(m[0][1] == 10);
    check(m[0][2] == 10);
    check(m[1][0] == 10);
    check(m[1][1] == 10);
    check(m[1][2] == 10);
    std::cout << std::endl;
}

void check_equal(){
    Matrix m(3, 3), matr(3, 3);
    m.set_value(10);
    matr.set_value(10);
    
    check(m == matr);
    
    matr.set_value(5);
    
    check(m != matr);
    std::cout << std::endl;
}

void check_mul(){
    Matrix m(3, 3), matr(3,3);
    m.set_value(10);
    matr.set_value(30);
    
    check((m *= 3) == matr);
    m[0][0] = 1;
    check(m != matr);
    
    std::vector<double> vec(3, 1);
    Matrix mat(3, 1);
    vec[0] = 3;
    mat[0][0] = 63;
    mat[1][0] = mat[2][0] = 150;
    check((m *= vec) == mat);
    std::cout << std::endl;
}

void check_get_size(){
    Matrix m(3, 2);
    check(m.get_row_size() == 3);
    check(m.get_col_size() == 2);
    std::cout << std::endl;
}

int main(){
    std::cout << "\nCheck get set:\n" << std::endl;
    check_get_set();
    std::cout << "Check quality:\n" << std::endl;
    check_equal();
    std::cout << "Check multiplication:\n" << std::endl;
    check_mul();
    std::cout << "Check shape:\n" << std::endl;
    check_get_size();
    return 0;
}