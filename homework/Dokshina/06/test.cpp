#include <iostream>
#include <ctype.h>
#include <unordered_map>
#include <cmath>
#include <limits>

#include "numeric_traits.cpp"
#include "parse.cpp"
#include "calc.cpp"


template<typename T>
bool is_equal(T x, T y) {
    return x == y;
}

template<>
bool is_equal(double x, double y) {
    return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}


template<typename T>
int test(std::string expr, T ans = 0) {
    try {
        Calcuator<T> calc(expr);
        T result = calc.calculate();

        if (is_equal(result, ans)) {
            std::cout << "  OK:  ";
            std::cout << expr << " = " << result << std::endl;
            return 0;
        } else {
            std::cout << "  ERROR:  ";
            std::cout << expr << " = " << result << std::endl;
            return 1;
        }
    } catch (const char* err) {
        std::cout << "  " << err;
        std::cout << ": " << expr << std::endl;
        return 1;
    }
}


int main(int argc, char const *argv[])
{
    int num_of_errors = 0;
    std::cout << "Tests with good input:" << std::endl;

    // Calcuator int
    int ans1 = 42;
    num_of_errors += test<int>(std::string("(5 + 3 * (9 / Pi) * 4) + (1)"), ans1);

    // Calcuator long
    long ans2 = 1234567903356;
    num_of_errors += test(std::string("1234567891011 + 12345"), ans2);

    // Calcuator double
    double ans3 = 81.5;
    num_of_errors += test(std::string("0.5 + 0.5 / 0.25 + 79.0"), ans3);


    // Error input
    std::cout << std::endl;
    std::cout << "Tests with bad input:" << std::endl;
    num_of_errors += 1 - test<int>(std::string("19 - 2 + ( 4"));
    num_of_errors += 1 - test<double>(std::string("12.6 + +3"));
    num_of_errors += 1 - test<double>(std::string("12.6 + 6 7"));
    num_of_errors += 1 - test<double>(std::string("111.11 c 10"));
    num_of_errors += 1 - test<int>(std::string("(5.1 + 3 * (9 / Pi) * 4) + (1)"));

    num_of_errors += 1 - test<long>(std::string("92233720368547758070 * 13"));
    num_of_errors += 1 - test<int>(std::string("12345678910 / 14"));


    if (num_of_errors == 0) {
        std::cout << std::endl;
        std::cout << "All tests passed" << std::endl;
    } else {
        std::cout << std::endl;
        std::cout << "Tests failed with " << num_of_errors << " errors" << std::endl;
    }

    return 0;
}
