#include <iostream>
#include "MyVector.h"


void check(bool value, std::string checkstr)
{
    if (!value)
        std::cout <<checkstr<<std::endl;
}

void testMyVector()
{
    MyVector<int> vec(2,2);
    vec.push_back(2);


    check( vec.size() == 3, "error 1");

    for(auto it = vec.begin(); it != vec.end(); it++)
    {
        check(*it == 2, "error 2");
    }

    for(auto it = vec.rbegin(); it != vec.rend(); it++)
    {
        check(*it == 2, "error 3");
    }

    for (size_t i = 0; i < vec.size(); ++i) {
        check(vec[i] == 2, "error 5");
    }

    vec[1] = 3;

    check(vec[1] == 3, "error 6");

    vec.resize(1);

    check(vec[0] == 2, "error 7");
    check(vec.size() == 1, "error 8");

    vec.resize(5, 3);

    check(vec.size() == 5, "error 9");
    check(vec[4] == 3, "error 10");

}


int main() {

    testMyVector();


    return 0;
}
