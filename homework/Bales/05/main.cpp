#include "TMatrix.h"

void PrintVec(const std::vector<double>& vec) {
    for (auto x: vec) {
        std::cout << x << " ";
    }
    std::cout << std::endl << "#####################################" << std::endl << std::endl;
}

void Check(bool predic) {
    if (!predic) {
        std::cout << "Error was occured";
    }
}

void InitCheck() {
    TMatrix<double> y(3, 2);
    Check(y.GetSizeCol() == 3 && y.GetSizeRow() == 2);

    TMatrix<double> x(3, 2, 3.14);
    Check(x[0][0] == 3.14 && x[0][1] == 3.14 
            && x[1][0] == 3.14 && x[1][1] == 3.14
            && x[2][0] == 3.14 && x[2][1] == 3.14);
}

void GetSetItemCheck() {
    TMatrix<double> y(3, 2);
    y[2][1] = 100; 
    Check(y[0][0] == 0 && y[0][1] == 0 
        && y[1][0] == 0 && y[1][1] == 0
        && y[2][0] == 0 && y[2][1] == 100);
}

void MultCheck() {
    TMatrix<double> x(3, 2, 3);
    Check((x *= 10.0) == TMatrix<double>(3, 2, 30));
    Check((x *= std::vector<double>({1, 2, 3})) == std::vector<double>({18, 18}));
}

void IsEqualCheck() {
    TMatrix<double> x(3, 2, 3);
    TMatrix<double> y(3, 2, 3);
    Check(x == y);
}

void IsNonEqualCheck() {
    TMatrix<double> x(3, 2, 3);
    TMatrix<double> y(3, 2, 5);
    TMatrix<double> z(3, 3, 3);
    Check(x != y);
    Check(x != z);
}

void CopyCheck() {
    TMatrix<double> x(3, 2, 3);
    TMatrix<double> y(5, 5, 3);
    Check(x != y);
    y = x;
    Check(x == y);
    Check(x == TMatrix<double>(x));
}

void UnifyLinkCheck() {
    TMatrix<double> x(3, 2, 3);
    TMatrix<double> y = std::move(x);
    Check(x.GetSizeCol() == 0 && x.GetSizeRow() == 0
            && y.GetSizeCol() == 3 && y.GetSizeRow() == 2);
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
    std::cout << "  CopyCheck: ";    
    CopyCheck();
    std::cout << std::endl;
    std::cout << "  UnifyLinkCheck: ";    
    UnifyLinkCheck();
    std::cout << std::endl;    
    std::cout << "Testing is ended" << std::endl;
    return 0;
}