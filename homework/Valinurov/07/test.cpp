#include "calculator.cpp"
#include <assert.h>

template <class T>
void check(const char* test, T answer)
{
    Calculator<T> calc(test);
    T calculated;
    try
    {
        calculated = calc.Expr();
    } catch (std::invalid_argument e){
        std::cout << "On test " << test << " get exception " << e.what() << std::endl;
        assert(0);
    }

    if (fabs(calculated - answer) > 1e-12)
    {
        std::cout << "On test " << test << " expected answer " << answer << " but get " << calculated << std::endl;
        assert(0);
    }
}

template <class T>
void check_exceptions(const char* test)
{
    Calculator<T> calc(test);
    try
    {
        calc.Expr();
    } catch (std::invalid_argument){
        return;
    }

    std::cout << "On test " << test << " expected exception but didn't get it" << std::endl;
    assert(0);
}

void validTests()
{
    check<int>("2", 2);
    check<long>("-2", -2);
    check<long>("1 * 2 * 3 / 6", 1);
    check<long>("14 / 6 * 3", 6);
    check<int>("2+2", 4);
    check<long>("  2  + -  3  ", -1);
    check<int>("e", 2);
    check<long>("2 - -  -   Pi", -1);
    check<long>("2 * (1 + 4 / (1 + 1) * 2) / 5", 2);
    check<long>("(1 + 4 / (1 + 1) * 2) / 5 * 2", 2);
    check<long>("(8 - 6) / 2 * -2", -2);
    check<long>("(5 + 3 * (9 / Pi) * 4) + (1)", 42);
    check<double>(".", 0);
    check<double>("2 * Pi", 6.28);
    check<double>("1. * e", 2.7);
    check<double>(".5 + 1", 1.5);
    check<double>("2 * 2.5 + 3.1 / 3.1", 6);
    check<double>("2 * 2. / 4 + 2.3 * 2.4", 6.52);
    check<double>("(2.5 * (1.7 + 1.3) / 3)", 2.5);
    check<double>("-2 * 26.23423 + 3", -49.46846);

}

void invalidTests()
{
    check_exceptions<int>("4294967296"); // переполнение
    check_exceptions<char>("1"); // недопустимый тип
    check_exceptions<float>("1");
    check_exceptions<double>("1111.1111.111 + 1");
    check_exceptions<int>("1 / 4294967296");
    check_exceptions<double>("1.5 + 1,5");
    check_exceptions<double>("e.5");
    check_exceptions<double>("1 / (Pi - Pi)");
    check_exceptions<long>("2 c (2)");
    check_exceptions<long>("2 ++2 ");
    check_exceptions<long>("2 -+ 2");
    check_exceptions<double>("2 .    5");
    check_exceptions<long>("2 / 0");
}

int main(){
    validTests();
    invalidTests();
    std::cout << "tests are OK" << std::endl;
    return 0;
}
