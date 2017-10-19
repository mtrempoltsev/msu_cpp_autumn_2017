#include "Slice.h"
#include "Matrix.h"
#include <iostream>
#include <stdexcept>

bool fail(bool setFail = false) {
    static bool isFailed = false;
    isFailed = (setFail || isFailed);
    return isFailed;
}

template <typename T, typename V>
void checkEquals(T a, V b, double eps = 1e-5) {
    bool equals = ((a < b + eps) && (a > b - eps));
    if (!equals) {
        std::cout << "[FAIL]: " << a << " != " << b << std::endl;
        fail(true);
    } else {
        std::cout << "[OK]: " << a << " == " << b << std::endl;
    }
}

void checkThrows(std::function<void ()> f) {
    try {
        f();
    } catch (const std::exception& e) {
        std::cout << "[OK]: Thrown as expected: " << e.what() << std::endl;
        return;
    }
    std::cout << "[FAIL]: Not thrown but expected" << std::endl;
    fail(true);
}

void checkInvalidConstructor() {
    std::cout << "===== checkInvalidConstructor =====" << std::endl;
    checkThrows([] () { Matrix<double>(0, 1); });
    checkThrows([] () { Matrix<double>(0, 5); });
    checkThrows([] () { Matrix<double>(1, 0); });
    checkThrows([] () { Matrix<double>(5, 0); });
    checkThrows([] () { Matrix<double>(0, 0); });
}

void checkColsNRowsN() {
    std::cout << "===== checkColsNRowsN =====" << std::endl;
    Matrix<double> m(2, 322);
    checkEquals(m.getRowsN(), 2);
    checkEquals(m.getColsN(), 322);
}

void checkGetSet() {
    std::cout << "===== checkGetSet =====" << std::endl;
    Matrix<double> m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;
    
    checkEquals(m[0][0], 1);
    checkEquals(m[0][1], 2);
    checkEquals(m[0][2], 3);
    checkEquals(m[1][0], 4);
    checkEquals(m[1][1], 5);
    checkEquals(m[1][2], 6);
    
    m[1][2] = 100;
    
    checkEquals(m[1][2], 100);
}


void checkInitializerList() {
    std::cout << "===== checkInitializerList =====" << std::endl;
    Matrix<double> m = {
        {1, 2, 3,},
        {4, 5, 6,},
    };

    checkEquals(m[0][0], 1);
    checkEquals(m[0][1], 2);
    checkEquals(m[0][2], 3);
    checkEquals(m[1][0], 4);
    checkEquals(m[1][1], 5);
    checkEquals(m[1][2], 6);

    checkThrows([] () { 
        Matrix<double> m = {
            {},
            {},
        };
    });
    checkThrows([] () { 
        Matrix<double> m = {
            {1,},
            {1,2,}
        };
    });
    checkThrows([] () { 
        Matrix<double> m = {
            {1,2,3},
            {1,2,}
        };
    });
    checkThrows([] () { 
        Matrix<double> m = {
            {1,2,3},
            {4,5,3},
            {4,5,3,7},
        };
    });
}

void checkAt() {
    std::cout << "===== checkAt =====" << std::endl;
    Matrix<double> m = {
        {1, 2, 3,},
        {4, 5, 6,},
    };

    checkEquals(m.at(0, 0), 1);
    checkEquals(m.at(0, 1), 2);
    checkEquals(m.at(0, 2), 3);
    checkEquals(m.at(1, 0), 4);
    checkEquals(m.at(1, 1), 5);
    checkEquals(m.at(1, 2), 6);

    checkThrows([&m] () { m.at(0, 5); });
    checkThrows([&m] () { m.at(6, 1); });
    checkThrows([&m] () { m.at(7, 7); });
}

void checkCopyConstructor() {
    std::cout << "===== checkCopyConstructor =====" << std::endl;
    Matrix<double> first = {
        {1, 2, 3,},
        {4, 5, 6,},
    };

    Matrix<double> second(first);

    checkEquals(second[0][0], 1);
    checkEquals(second[0][1], 2);
    checkEquals(second[0][2], 3);
    checkEquals(second[1][0], 4);
    checkEquals(second[1][1], 5);
    checkEquals(second[1][2], 6);
}

void checkAssignment() {
    std::cout << "===== checkAssignment =====" << std::endl;
    Matrix<double> first = {
        {1, 2, 3,},
        {4, 5, 6,},
    };
    Matrix<double> second(2, 3);
    Matrix<double> badDims1(1, 3);
    Matrix<double> badDims2(3, 3);
    Matrix<double> badDims3(2, 2);
    Matrix<double> badDims4(2, 4);
    Matrix<double> badDims5(1, 1);

    second = first;

    checkEquals(second[0][0], 1);
    checkEquals(second[0][1], 2);
    checkEquals(second[0][2], 3);
    checkEquals(second[1][0], 4);
    checkEquals(second[1][1], 5);
    checkEquals(second[1][2], 6);

    checkThrows([&first, &badDims1] () { badDims1 = first; });
    checkThrows([&first, &badDims2] () { badDims2 = first; });
    checkThrows([&first, &badDims3] () { badDims3 = first; });
    checkThrows([&first, &badDims4] () { badDims4 = first; });
    checkThrows([&first, &badDims5] () { badDims5 = first; });
}

void checkInvalidGet() {
    std::cout << "===== checkInvalidGet =====" << std::endl;
    Matrix<double> m(2, 10);
    checkThrows([&m] () { m[0][10]; });
    checkThrows([&m] () { m[1][11]; });
    checkThrows([&m] () { m[5][0]; });
    checkThrows([&m] () { m[-1][1]; });
}

void checkMultByNumber() {
    std::cout << "===== checkMultByNumber =====" << std::endl;
    Matrix<double> m = {
        {1, 2, 3,},
        {4, 5, 6,},
    };
    
    checkEquals((m * 0.5)[0][0], 0.5);
    checkEquals((m * 0)[0][1], 0);
    checkEquals((m * -1)[0][2], -3);
    checkEquals((m * -2.5)[1][0], -10);
    checkEquals((m * 10)[1][1], 50);
    checkEquals((m * 1)[1][2], 6);
}

void checkMultEquals() {
    std::cout << "===== checkMultEquals =====" << std::endl;
    Matrix<double> m = {
        {1, 2, 3,},
        {4, 5, 6,},
    };

    m *= -0.5;
    
    checkEquals(m[0][0], -0.5);
    checkEquals(m[0][1], -1.0);
    checkEquals(m[0][2], -1.5);
    checkEquals(m[1][0], -2.0);
    checkEquals(m[1][1], -2.5);
    checkEquals(m[1][2], -3.0);
}

void checkMultByVec() {
    std::cout << "===== checkMultByVec =====" << std::endl;
    Matrix<double> m = {
        {1, 2, 3,},
        {4, 5, 6,},
    };

    std::vector<double> vec = {0, 2.0, -0.5};
    std::vector<double> badVec1 = {0, 2.0, -0.5, 1};
    std::vector<double> badVec2 = {0, 2.0};
    std::vector<double> prod = m * vec;
    
    checkEquals(prod[0], 2.5);
    checkEquals(prod[1], 7.0);

    checkThrows([&m, &badVec1] () { m * badVec1; });
    checkThrows([&m, &badVec2] () { m * badVec2; });
}

void checkIsEquals() {
    std::cout << "===== checkIsEquals =====" << std::endl;
    Matrix<double> first = {
        {1, 2, 3,},
        {4, 5, 6,},
    };
    Matrix<double> differentDims1(3, 3);
    Matrix<double> differentDims2(2, 4);

    Matrix<double> second = first;
    Matrix<double> third = first;
    third[1][2] = 10;

    checkEquals(first == second, true);
    checkEquals(first == third, false);
    checkEquals(first == differentDims1, false);
    checkEquals(first == differentDims2, false);
    checkEquals(first != second, false);
    checkEquals(first != third, true);
    checkEquals(first != differentDims1, true);
    checkEquals(first != differentDims2, true);
}

void checkMoveConstructor() {
    std::cout << "===== checkMoveConstructor =====" << std::endl;
    Matrix<double> first = {
        {1, 2, 3,},
        {4, 5, 6,},
    };

    Matrix<double> second = std::move(first);

    checkEquals(second[0][0], 1);
    checkEquals(second[0][1], 2);
    checkEquals(second[0][2], 3);
    checkEquals(second[1][0], 4);
    checkEquals(second[1][1], 5);
    checkEquals(second[1][2], 6);

    checkThrows([&first] () { first[0][0]; } );
    checkThrows([&first] () { first[1][1]; } );
}

void checkMoveOperator() {
    std::cout << "===== checkMoveOperator =====" << std::endl;
    Matrix<double> first = {
        {1, 2, 3,},
        {4, 5, 6,},
    };

    Matrix<double> second(2, 3);
    Matrix<double> badDims1(2, 2);
    Matrix<double> badDims2(2, 4);
    Matrix<double> badDims3(1, 3);
    Matrix<double> badDims4(3, 3);

    second = std::move(first);

    checkEquals(second[0][0], 1);
    checkEquals(second[0][1], 2);
    checkEquals(second[0][2], 3);
    checkEquals(second[1][0], 4);
    checkEquals(second[1][1], 5);
    checkEquals(second[1][2], 6);

    checkThrows([&second, &badDims1] () { badDims1 = std::move(second); } );
    checkThrows([&second, &badDims2] () { badDims2 = std::move(second); } );
    checkThrows([&second, &badDims3] () { badDims3 = std::move(second); } );
    checkThrows([&second, &badDims4] () { badDims4 = std::move(second); } );
    checkThrows([&first, &badDims4] () { badDims4 = std::move(first); } );
    checkThrows([&first] () { first[0][0]; } );
    checkThrows([&first] () { first * 2; } );
    checkThrows([&first] () { Matrix<double> m(first); } );
    checkThrows([&first] () { Matrix<double> m(std::move(first)); } );
}

void checkIntTemplate() {
    std::cout << "===== checkIntTemplate =====" << std::endl;
    Matrix<int> first = {
        {1, 2, 3,},
        {4, 5, 6,},
    };

    checkEquals(first[0][0] / 2, 0);
    checkEquals(first[0][1] / 2, 1);
    checkEquals(first[0][2] / 2, 1);
    checkEquals(first[1][0] / 2, 2);
    checkEquals(first[1][1] / 2, 2);
    checkEquals(first[1][2] / 2, 3);
    
    first *= -2;

    checkEquals(first[0][0], -2);
    checkEquals(first[1][2], -12);
}

void runTests() {
    checkInvalidConstructor();
    checkGetSet();
    checkInitializerList();
    checkAt();
    checkCopyConstructor();
    checkAssignment();
    checkColsNRowsN();
    checkInvalidGet();
    checkMultByNumber();
    checkMultEquals();
    checkMultByVec();
    checkIsEquals();
    checkMoveConstructor();
    checkMoveOperator();
    checkIntTemplate();

    std::cout << "====================" << std::endl;
    if (fail()) {
        std::cout << "[FAIL] one or more tests has failed" << std::endl;
    } else {
        std::cout << "[OK] all tests are ok" << std::endl;
    }
}

int main(int argc, char const *argv[]) {
    runTests();
    return 0;
}