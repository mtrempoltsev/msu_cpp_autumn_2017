#include <iostream>
#include <stdexcept>
#include "Calculator.h"

template <typename T>
void checkOutput(const char* expr) {
    static int testNumber = 0;
    ++testNumber;
    Calculator<T> calc;
    std::cout << "[ Output ] [ " << expr << " ] Test " << testNumber << " ";
    calc.calculate(expr);
}

template <typename T>
int assert(const char* expr, T expect, double eps = 1e-7) {
    static int testNumber = 0;
    ++testNumber;
    Calculator<T> calc;
    T result = calc.calculate(expr);
    if (std::abs(result - expect) < eps) {
        std::cout << "[ OK ] Test " << testNumber << " succeeded! [ " << expr << " = " << expect << " ]" << std::endl;
        return 0;
    } else {
        std::cout << "[ FAIL ] Test " << testNumber << " failed. :(" << std::endl;
        std::cout << "   For [" << expr << "] got [" << result << "]. [" << expect << "] expexted." << std::endl;
        return 1;
    }
}

template <typename T>
int assertFail(const char* expr) {
    static int testNumber = 0;
    ++testNumber;
    Calculator<T> calc;
    try {
        calc.calculate(expr);
    } catch (const std::runtime_error& e) {
        std::cout << "[ OK ] Test " << testNumber << " thrown as expected. [ " << expr << " ] (" << e.what() << ")" << std::endl;
        return 0;
    }
    std::cout << "[ FAIL ] Test " << testNumber << " expected to throw but returned a value. [ " << expr << " ]" << std::endl;
    return 1;
}

int doIntTests() {
    std::cout << "========== Int ==========" << std::endl;
    int fails = 0;
    fails += assert<int>("1", 1);
    fails += assert<int>("01", 1);
    fails += assert<int>("123", 123);
    fails += assert<int>("1 + 1", 2);
    fails += assert<int>("2 * 2", 4);
    fails += assert<int>("1 + 2 * 3", 7);
    fails += assert<int>("2 * 3 + 1", 7);
    fails += assert<int>("2 * 3 * 4 * 5 * 6", 720);
    fails += assert<int>("1 + 2 + 3 + 4", 10);
    fails += assert<int>("1 + 2 * 3 + 4 * 5 + 6 * 7 + 8 * 9 * 10", 789);
    fails += assert<int>("-5", -5);
    fails += assert<int>("1 + -1", 0);
    fails += assert<int>("1 - -1", 2);
    fails += assert<int>("2 + 10 * -1 + 1", -7);
    fails += assert<int>("1+-2", -1);
    fails += assert<int>("-1", -1);
    fails += assert<int>("-1 - 1 -5 -8*0", -7);
    fails += assert<int>("10*2/7", 2);
    fails += assert<int>("10*2/-7", -2);
    fails += assert<int>("20/-7", -2);
    fails += assert<int>("(1)", 1);
    fails += assert<int>("(1) + 1", 2);
    fails += assert<int>("1 + (1)", 2);
    fails += assert<int>("(1) * 3", 3);
    fails += assert<int>("(-1)", -1);
    fails += assert<int>("3 * (-1)", -3);
    fails += assert<int>("(2) * (1 + 5)", 12);
    fails += assert<int>("(2) * (1 + 5) + (3 + 2) / (-2)", 10);
    fails += assert<int>("2 * (1) + -2", 0);
    fails += assert<int>("(5 + 3 * (8 / 3) * 4) + (1)", 30);
    fails += assert<int>("(5 + 3 * (8 / Pi) * 4) + (1)", 30);
    fails += assert<int>("-Pi", -3);
    fails += assert<int>("Pi", 3);
    fails += assert<int>("-(Pi)", -3);

    fails += assertFail<int>("(2 / 0)");
    fails += assertFail<int>("(2 / 0))");
    fails += assertFail<int>("(2 / 1))");
    fails += assertFail<int>("2 -+ 2");
    fails += assertFail<int>("2 ++ 2");
    fails += assertFail<int>("2 c (0)");
    fails += assertFail<int>("1.5 + 1.5");
    fails += assertFail<int>("(2 + 0");
    fails += assertFail<int>("2a");
    fails += assertFail<int>("2 2");
    fails += assertFail<int>("2 (");
    fails += assertFail<int>("2 )");

    std::cout << "Following tests in this section should print Warnings." << std::endl;

    checkOutput<int>("3000000000");

    return fails;
}

int doDoubleTests() {
    std::cout << "========== Double ==========" << std::endl;
    int fails = 0;
    fails += assert<double>("1.5", 1.5);
    fails += assert<double>("01.1", 1.1);
    fails += assert<double>("123.2", 123.2);
    fails += assert<double>("1.5 + 1", 2.5);
    fails += assert<double>("2.5 * 2", 5);
    fails += assert<double>("(5.123 + 3.456 * (8.789 / Pi) * 4.012) + (1.3456789)", 45.279, 0.001);

    fails += assertFail<double>("(2. / 0)");
    fails += assertFail<double>("(2 / 0.))");
    fails += assertFail<double>("(2 / 1))");
    fails += assertFail<double>("2 -+ 2");
    fails += assertFail<double>("2 ++ 2");
    fails += assertFail<double>("2 c (0)");
    fails += assertFail<double>("(2 + 0");
    fails += assertFail<double>("2a");
    fails += assertFail<double>("2 2");
    fails += assertFail<double>("2 (");

    return fails;
}

int doLongTests() {
    std::cout << "========== Long ==========" << std::endl;
    int fails = 0;
    fails += assert<long>("1", 1);
    fails += assert<long>("01", 1);
    fails += assert<long>("123", 123);
    fails += assert<long>("3000000123", 3000000123);
    fails += assert<long>("1 + 1", 2);
    fails += assert<long>("2 * 2", 4);
    fails += assert<long>("1 + 2 * 3", 7);
    fails += assert<long>("2 * 3 + 1", 7);
    fails += assert<long>("2 * 3 * 4 * 5 * 6", 720);
    fails += assert<long>("1 + 2 + 3 + 4", 10);
    fails += assert<long>("1 + 2 * 3 + 4 * 5 + 6 * 7 + 8 * 9 * 10", 789);
    fails += assert<long>("-5", -5);
    fails += assert<long>("1 + -1", 0);
    fails += assert<long>("1 - -1", 2);
    fails += assert<long>("2 + 10 * -1 + 1", -7);
    fails += assert<long>("1+-2", -1);
    fails += assert<long>("-1", -1);
    fails += assert<long>("-1 - 1 -5 -8*0", -7);
    fails += assert<long>("10*2/7", 2);
    fails += assert<long>("10*2/-7", -2);
    fails += assert<long>("20/-7", -2);
    fails += assert<long>("(1)", 1);
    fails += assert<long>("(1) + 1", 2);
    fails += assert<long>("1 + (1)", 2);
    fails += assert<long>("(1) * 3", 3);
    fails += assert<long>("(-1)", -1);
    fails += assert<long>("3 * (-1)", -3);
    fails += assert<long>("(2) * (1 + 5)", 12);
    fails += assert<long>("(2) * (1 + 5) + (3 + 2) / (-2)", 10);
    fails += assert<long>("2 * (1) + -2", 0);
    fails += assert<long>("(5 + 3 * (8 / 3) * 4) + (1)", 30);
    fails += assert<long>("(5 + 3 * (8 / Pi) * 4) + (1)", 30);
    fails += assert<long>("-Pi", -3);
    fails += assert<long>("Pi", 3);
    fails += assert<long>("-(Pi)", -3);

    fails += assertFail<long>("(2 / 0)");
    fails += assertFail<long>("(2 / 0))");
    fails += assertFail<long>("(2 / 1))");
    fails += assertFail<long>("2 -+ 2");
    fails += assertFail<long>("2 ++ 2");
    fails += assertFail<long>("2 c (0)");
    fails += assertFail<long>("1.5 + 1.5");
    fails += assertFail<long>("(2 + 0");
    fails += assertFail<long>("2a");
    fails += assertFail<long>("2 2");
    fails += assertFail<long>("2 (");
    fails += assertFail<long>("2 )");

    return fails;
}

void doTests() {
    int fails = 0;
    fails += doIntTests();
    fails += doLongTests();
    fails += doDoubleTests();

    std::cout << "==============================" << std::endl;
    if (fails == 0) {
        std::cout << "All tests have passed successfully!" << std::endl;
    } else {
        std::cout << "One or more tests failed." << std::endl;
    }
}
