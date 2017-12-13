#include <iostream>
#include "calc.cpp"
#include "testing.cpp"
#include <cmath>

template <class T>
void test(string &&s, T true_answer, bool want_error = false) {
    startTest(s);
    T res;
    bool was_error = false;
    try {
        calc<T> str(s);
        str.calculation();
        res = str.get_num();
        cerr << "answer from calc: " << res << endl;
    } catch (std::string & err) {
        cerr << err << endl;
        was_error = true;
    }
    if ((!was_error && std::abs(res - true_answer) < 1e12) || (was_error && want_error)) {
        ok();
    } else {
        error();
    }
    endTest();
}

int main(void) {
    
    testParagraph("Test int");
    test<int>(string("1 + 1"), 2);
    test<int>(string("1 - 1"), 0);
    test<int>(string("1 + 1 * 2 - 2 / 1 * (1 - 4)"), 9);
    test<int>(string("1 - (123) * (-123) - (-1) * 1000"), 16130);
    test<int>(string("1 - 1 - 1- -1 + -1 -1 * 10 / 10"), -2);

    testParagraph("Test int error");
    test<int>(string("1 / 0"), 0, true);
    test<int>(string("1 / (1 - 1)"), 0, true);
    test<int>(string("1 / -e"), 0, true);
    test<int>(string("1.12"), 0, true);
    test<int>(string("1 / 100000000000"), 0, true);
    test<int>(string("1 / -100000000000"), 0, true);
    test<int>(string("1  ++ -100000000000"), 0, true);

    testParagraph("Test long");
    test<long>(string("1 - 1"), 0);
    test<long>(string("10000000000 - 1 / 1"), 9999999999);
    test<long>(string("1 * 1000000 * 10000 * 9999 / 1 - 0"), 99990000000000);
    test<long>(string("1 - 1 - 23948213741231 -123412341 -(-1) * 112313  / 123123 + 123123"), -23948337030449);

    testParagraph("Test long error");
    test<long>(string("1 / 0"), 0, true);
    test<long>(string("1  ++ -100000000000"), 0, true);
    test<long>(string("1  / 1 - 0asdf"), 0, true);
    test<long>(string("1 - e"), 0, true);
    test<long>(string("12381746129387469287136498172634981234"), 0, true);
    test<long>(string("-12381746129387469287136498172634981234"), 0, true);

    testParagraph("Test double");
    test<double>(string("1.0 - 1.0"), 0);
    test<double>(string("1.0 / 1231 - 21312 * 21321.12321 * 10000"), -4.54396e+12);
    test<double>(string("1.0 - 1.0 / 1000"), 0.999);
    test<double>(string("1.0 - 1.0 * e / -Pi"), 1.86525598);
    test<double>(string("1.0 * (1312.12312 - 12312) * 10000"), -109998768.8);

    testParagraph("Test error double");
    test<double>(string("1 - e/0"), 0, true);
    test<double>(string("1 ++ 1 - 12312"), 0, true);
    test<double>(string("1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"), 0, true);

    testResult();
    return 0;
}