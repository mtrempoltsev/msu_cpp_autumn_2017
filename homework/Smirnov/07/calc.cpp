/**
 Калькулятор.
 БНФ (скобки)
 expr = term | expr + term | expr - term 
 term = prim | term * prim | term / prim 
 prim = - number | number | name 
 number = [0,9]+
 name = [a-z.A-Z]+
 */
#include "calc.hpp"
#include <cmath>

const double eps = 1e-3;

bool is_equal(double a, double b)
{
    if (abs(a-b) < eps) return true;
    return false;
}

int main(int argc,char** argv)
{
    Calculator<double> calc_d;
    Calculator<int> calc_i;
    Calculator<long> calc_l;
    double test_d;
    long test_l;
    int test_i;

    //Test1
    std::cout << "Test1: ";
    try
    {
        const char* test1 = "2/0+(2.1*4.2)";
        test_d = calc_d.calculate(test1);
        std::cout << "not passed" << std::endl;
    }
    catch(const std::runtime_error& error)
    {
        std::cout << "passed" << std::endl;
    }
    catch(...)
    {
        std::cout << "not passed" << std::endl;
    }

    //Test2
    std::cout << "Test2: ";
    try
    {
        const char* test2 = "30000000000+(16*4)";
        test_i = calc_i.calculate(test2);
        std::cout << "not passed" << std::endl;
    }
    catch(const std::logic_error& error)
    {
        std::cout << "passed" << std::endl;
    }
    catch(...)
    {
        std::cout << "not passed" << std::endl;
    }

    //Test3
    std::cout << "Test3: ";
    try
    {
        const char* test3 = "130*++1500000*5";
        test_l = calc_l.calculate(test3);
        std::cout << "not passed" << std::endl;
    }
    catch(const std::logic_error& error)
    {
        std::cout << "passed" << std::endl;
    }
    catch(...)
    {
        std::cout << "not passed" << std::endl;
    }

    //Test4
    std::cout << "Test4: ";
    try
    {
        const char* test3 = "2e12+(10*5)";
        test_d = calc_d.calculate(test3);
        std::cout << "not passed" << std::endl;
    }
    catch(const std::logic_error& error)
    {
        std::cout << "passed" << std::endl;
    }
    catch(...)
    {
        std::cout << "not passed" << std::endl;
    }
    
    //Test5
    std::cout << "Test5: ";
    try
    {
        const char* test3 = "21+(12*(1)-2+10*5))";
        test_i = calc_i.calculate(test3);
        std::cout << "not passed" << std::endl;
    }
    catch(const std::logic_error& error)
    {
        std::cout << "passed" << std::endl;
    }
    catch(...)
    {
        std::cout << "not passed" << std::endl;
    }
    
    return 0; 
}