// Vasilii Bodnariuk

#include <iostream>
#include <string>

#include "vector.hpp"

using namespace std;

bool testing(bool value) {
    if(!value) {
        std::cout << "fail" << '\n';
    }
    return value;
}

int main(int argc, char* argv[])
{
    auto tests_passed = true;
    std::cout << "starting tests" << '\n';\

    auto v1 = Vector<int>();
    tests_passed &= testing(v1.empty());

    auto v2 = Vector<int>(5);
    tests_passed &= testing(!v2.empty());
    tests_passed &= testing(v2.size() == 5);

    auto v3 = Vector<int>(10, 4);
    tests_passed &= testing(v3.size() == 10);
    tests_passed &= testing(v3[8] == 4);

    v3.clear();
    tests_passed &= testing(v3.empty());

    v3.resize(7, 6);
    tests_passed &= testing(v3.size() == 7);
    tests_passed &= testing(v3[5] == 6);

    v3.resize(8, 8);
    tests_passed &= testing(v3[6] == 6);
    tests_passed &= testing(v3[7] == 8);

    v3[3] = 9;
    tests_passed &= testing(v3[3] == 9);

    v3.push_back(11);
    tests_passed &= testing(v3[8] == 11);

    try {
        v1.pop_back();
        tests_passed = false;
    }
    catch (exception &e) {
        tests_passed &= testing(e.what() == string("trying to pop_back an empty vector"));
    }

    try {
        v1[0] = 0;
        tests_passed = false;
    }
    catch (exception &e) {
        tests_passed &= testing(e.what() == string("index out of range"));
    }


    v3[0] = 9;


    int i = 0;
    for(auto it = v3.begin(); it != v3.end(); ++it) {
        tests_passed &= (*it == v3[i]);
        ++i;
    }

    for(auto it = v3.rbegin(); it != v3.rend(); ++it) {
        --i;
        tests_passed &= (*it == v3[i]);
    }

    if(tests_passed) {
        std::cout << "+ tests passed" << '\n';
    } else {
        std::cout << "- not passed" << '\n';
    }

    return 0;
}
