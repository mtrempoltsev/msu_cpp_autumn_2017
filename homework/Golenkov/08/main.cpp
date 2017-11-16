#include <iostream>
#include <string>
#include <cassert>

#include "Vector.h"

int check(bool value) {
    if (!value)
    {
        assert("Test is not passed!");
    }
}

void doTests() {

    Vector<int> vect(4);
    check(vect.size() == 4);

    vect(4, 3);
    Vector<int> answer = {3, 3, 3, 3};
    check(vect == answer);

    Vector<int> vect_origin = vect;
    check(vect_origin == vect);

    Vector<int> vect1(4, 3);
    vect1 = vect;
    check(vect1 == vect);

    Vector<int> vect2(std::move(vect));
    check(vect2 == vect_origin);

    Vector<int> vect3(4, 3);
    vect3 = std::move(vect2);
    check(vect3 == vect2);

    vect = {1, 2, 3, 4};

    check(vect.size() == 4);
    check(vect[0] == 1);
    check(vect[1] == 2);
    check(vect[2] == 3);
    check(vect[3] == 4);

    vect.push_back(5);
    answer = {1, 2, 3, 4, 5};
    check(vect == answer);

    vect.resize(2);
    answer = {1, 2};
    check(vect == answer);

    vect.resize(5);
    answer = {1, 2, 0, 0, 0};
    check(vect == answer);

    vect.resize(10, 6);
    answer = {1, 2, 0, 0, 0, 6, 6, 6, 6, 6};
    check(vect == answer);

    vect.pop_back();
    answer = {1, 2, 0, 0, 0, 6, 6, 6, 6};
    check(vect == answer);

    vect = {2, 2, 2, 2};
    for(auto it = vect.begin(); it != vect.end(); it++)
    {
        check(*it == 2);
    }

    for(auto it = vect.rbegin(); it != vect.rend(); it++)
    {
        check(*it == 2);
    }

    vect.clear();
    //answer = std::move(Vector<int>(0));
    check(vect == Vector<int>(0));

    check(vect.empty());
    std::cout << "All tests passed successfully!" << std::endl;
}

int main() {
    try {
        doTests();
    } catch (const char* error) {
        std::cout << error << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Unknown error occured" << std::endl;
        return 1;
    }
    return 0;
}
