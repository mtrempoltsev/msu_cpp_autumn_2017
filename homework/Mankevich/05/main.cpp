#include <iostream>
#include <vector>
#include "matrix.cpp"

void check(bool value){
    if (!value){
        std::cout << "error" << std::endl;
    }
}

void check_get_set(){
    Matrix<int> m(2, 3);
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
    Matrix<int> m(3, 3), matr(3, 3);
    m.set_value(10);
    matr.set_value(10);
    
    check(m == matr);
    
    matr.set_value(5);
    
    check(m != matr);
    std::cout << std::endl;
}

void check_mul(){
    Matrix<int> m(3, 3), matr(3,3);
    m.set_value(10);
    matr.set_value(30);
    
    check((m *= 3) == matr);
    m[0][0] = 1;
    check(m != matr);
    
    std::vector<int> vec(3, 1);
    Matrix<int> mat(3, 1);
    vec[0] = 3;
    mat[0][0] = 63;
    mat[1][0] = mat[2][0] = 150;
    check((m *= vec) == mat);
    std::cout << std::endl;
}

void check_get_size(){
    Matrix<int> m(3, 2);
    check(m.get_row_size() == 3);
    check(m.get_col_size() == 2);
    std::cout << std::endl;
}

void check_copy(){
    Matrix<int> m(3, 2);
    m.set_value(10);
    
    Matrix<int> matr(m);
    check(matr == m);
    Matrix<int> new_matr(3, 2);
    
    new_matr = m;
    check(new_matr == m);
    std::cout << std::endl;
}

void check_move(){
    Matrix<int> m(3, 2);
    m.set_value(10);
    Matrix<int> matr = m;
    Matrix<int> move_m(std::move(m));
    check(move_m != m);
    check(move_m == matr);
    
    Matrix<int> new_move(3, 3);
    new_move = std::move(move_m);
    check(new_move != move_m);
    check(new_move == matr);
    std::cout << std::endl;
}

int main(){
    try{
        std::cout << "\nCheck get set:\n" << std::endl;
        check_get_set();
        std::cout << "Check quality:\n" << std::endl;
        check_equal();
        std::cout << "Check multiplication:\n" << std::endl;
        check_mul();
        std::cout << "Check shape:\n" << std::endl;
        check_get_size();
        std::cout << "Check copy oper/constr:\n" << std::endl;
        check_copy();
        std::cout << "Check move oper/constr:\n" << std::endl;
        check_move();
    }
    catch(std::invalid_argument& e){
        std::cout << e.what() << std::endl;
    }
    return 0;
}
