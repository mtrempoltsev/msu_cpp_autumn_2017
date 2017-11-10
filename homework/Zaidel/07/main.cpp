#include <iostream>
#include <sstream>
#include <cstring>
#include "Calculator.h"
#include "Parser.h"

void check(bool cond)
{
    if(!cond)
    {
        std::cout<<"ERROR!"<<std::endl;
    }
}

void testInt()
{
   Calculator<int, Parser<int>> calc;

    // valid tests
    check(calc.calculate_s("1+1") == 2);
    check(calc.calculate_s("Pi") == 3);
    check(calc.calculate_s("e") == 2);
    check(calc.calculate_s("1/2") == 0);
    check(calc.calculate_s("(9*8 )/(2+3*2-4/ 2)") == 12);
    check(calc.calculate_s("8 - 6 / 2 * -2") == 14);

    // invalid tests
    try {
        calc.calculate_s("1 1");
        std::cout<<"ERROR";
    } catch(std::exception& ex) {}

    try {
        calc.calculate_s("((2+2)");
        std::cout<<"ERROR";
    } catch(std::exception& ex) {}

    try {
        calc.calculate_s("Pii + e");
        std::cout<<"ERROR";
    } catch(std::exception& ex) {}

    try {
        calc.calculate_s("92233720368547758");
        std::cout<<"ERROR";
    } catch(std::exception& ex) { }

    try {
        calc.calculate_s("922337299 * 1000000000");
        std::cout<<"ERROR";
    } catch(std::exception& ex) {}

    std::cout<<"Int Tested!"<<std::endl;
}


void testLong()
{
    Calculator<long, Parser<long>> calc;

    // valid tests
    check(calc.calculate_s("1+1") == 2);
    check(calc.calculate_s("Pi") == 3);
    check(calc.calculate_s("e") == 2);
    check(calc.calculate_s("1/2") == 0);
    check(calc.calculate_s("(9*8 )/(2+3*2-4/ 2)") == 12);
    check(calc.calculate_s("8 - 6 / 2 * -2") == 14);
    check(calc.calculate_s("92233720368547758") == 92233720368547758);

    // invalid tests
    try {
        calc.calculate_s("1 1");
        std::cout<<"ERROR";
    } catch(std::exception& ex) {}

    try {
        calc.calculate_s("((2+2)");
        std::cout<<"ERROR";
    } catch(std::exception& ex) {}

    try {
        calc.calculate_s("Pii + e");
        std::cout<<"ERROR";
    } catch(std::exception& ex) {}

    try {
        calc.calculate_s("92233720368547758 * 1000000000");
        std::cout<<"ERROR";
    } catch(std::exception& ex) {}


    std::cout<<"Long Tested!"<<std::endl;
}

void testDouble()
{
    Calculator<double, Parser<double>> calc;

    // valid tests
    check(calc.calculate_s("1+1") == 2);
    check(calc.calculate_s("Pi") == 3.14);
    check(calc.calculate_s("e") == 2.7);
    check(calc.calculate_s("1/2") == 0.5);
    check(calc.calculate_s("(9*8 )/(2+3*2-4/ 2)") == 12);
    check(calc.calculate_s("8 - 6 / 2 * -2") == 14);
    check(calc.calculate_s("92233720368547758") == 92233720368547758);

    // invalid tests
    try {
        calc.calculate_s("1 1");
        std::cout<<"ERROR";
    } catch(std::exception& ex) {}

    try {
        calc.calculate_s("((2+2)");
        std::cout<<"ERROR";
    } catch(std::exception& ex) {}

    try {
        calc.calculate_s("Pii + e");
        std::cout<<"ERROR";
    } catch(std::exception& ex) {}

    try {
        calc.calculate_s("92233720368547758 * 1000000000");
        std::cout<<"ERROR";
    } catch(std::exception& ex) {}

    try {
        calc.calculate_s("1 / 1e-320");
        std::cout<<"ERROR";
    } catch(std::exception& ex) {}

    std::cout<<"Double Tested!"<<std::endl;
}




int main(int argc, char* argv[]) {

    testInt();
    testLong();
    testDouble();

    return 0;
}
