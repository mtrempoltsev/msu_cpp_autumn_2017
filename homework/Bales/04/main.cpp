#include "TMatrix.h"

void PrintVec(const m_vector& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl << "#####################################" << std::endl << std::endl;
}

void Check(bool predic) {
    if (!predic) {
        std::cout << "error";
    }
}

void InitCheck() {
    TMatrix y(3, 2);
    Check(y.GetSizeCol() == 3 && y.GetSizeRow() == 2);

    TMatrix x(3, 2, TItem(3.14));
    Check(x[0][0] == 3.14 && x[0][1] == 3.14 
            && x[1][0] == 3.14 && x[1][1] == 3.14
            && x[2][0] == 3.14 && x[2][1] == 3.14);
}

void GetSetItemCheck() {
    TMatrix y(3, 2);
    y[2][1] = TItem(100); 
    Check(y[0][0] == TItem(0) && y[0][1] == TItem(0) 
        && y[1][0] == TItem(0) && y[1][1] == TItem(0)
        && y[2][0] == TItem(0) && y[2][1] == TItem(100));
}

void MultCheck() {
    TMatrix x(3, 2, TItem(3));
    Check((x *= 10) == TMatrix(3, 2, TItem(30)));
    Check((x *= m_vector({1, 2, 3})) == m_vector({18, 18}));
}

void IsEqualCheck() {
    TMatrix x(3, 2, TItem(3));
    TMatrix y(3, 2, TItem(3));
    Check(x == y);
}

void IsNonEqualCheck() {
    TMatrix x(3, 2, TItem(3));
    TMatrix y(3, 2, TItem(5));
    TMatrix z(3, 3, TItem(3));
    Check(x != y);
    Check(x != z);
}

int main(int argc, char* argv[]) {
    std::cout << "Start testing:" << std::endl;
    std::cout << "  InitCheck: ";
    InitCheck();
    std::cout << std::endl;
    std::cout << "  GetSetItemCheck: ";
    GetSetItemCheck();
    std::cout << std::endl;
    std::cout << "  IsEqualCheck: ";    
    IsEqualCheck();
    std::cout << std::endl;
    std::cout << "  IsNonEqualCheck: ";    
    IsNonEqualCheck();
    std::cout << std::endl;
    std::cout << "  MultCheck: ";    
    MultCheck();    
    std::cout << std::endl;    
    std::cout << "Testing is ended" << std::endl;
    return 0;
}