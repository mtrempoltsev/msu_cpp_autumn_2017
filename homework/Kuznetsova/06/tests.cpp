#include "parser.h"
#include <cstring>
#include <iostream>
#include <unordered_map>
const char *message = "Usage: calc \"(5 + 3 * (8 / Pi) * 4.3) + (1)\"";
std::unordered_map<std::string, double> constants = {
    {"Pi", 3.14}, {"e", 2.7},
};
void test_string(char *input);
int main() {
    char input1[] = "8 - 6 / 2 * -2";
    char input2[] = "8 - 6 / (2 * -2)";
    char input3[] = "2/0";
    char input4[] = "abcde";
    char input5[] = "2 ** 2";
    char input6[] = "(5 + 3 * (8 / Pi) * 4) + (1)";
    char input7[] = "(2 / 1))";
    char input8[] = "2 c (2)";
    char input9[] = "Pi";
    char input10[] = "2222222222222222222 + 2";
    char input11[] = "9223372036854775807 + 2";
    char input12[] = "3.14 * 3.22";

    test_string(input1);
    test_string(input2);
    test_string(input3);
    test_string(input4);
    test_string(input5);
    test_string(input6);
    test_string(input7);
    test_string(input8);
    test_string(input9);
    test_string(input10);
    test_string(input11);
    test_string(input12);

    return 0;
}
void test_string(char *input) {
    std::cout << input << std::endl;
    Parser<double> parser_double(input, constants);
    Parser<int> parser_int(input, constants);
    Parser<long int> parser_long_int(input, constants);
    std::cout << "Double: " << std::endl;
    std::cout << parser_double.calculate() << std::endl;
    std::cout << "Int: " << std::endl;
    std::cout << parser_int.calculate() << std::endl;
    std::cout << "Long int: " << std::endl;
    std::cout << parser_long_int.calculate() << std::endl;
    std::cout << "--------" << std::endl;
}
