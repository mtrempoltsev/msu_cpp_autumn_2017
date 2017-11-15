#include <iostream>
#include "MyVector.h"


void check(bool value, std::string checkstr)
{
    if (!value)
        std::cout <<checkstr<<std::endl;
}

void testResize()
{
    MyVector<int> vec(2,2);
    vec.resize(3,100);
    check(vec[2] == 100, "error in resize");

    vec.resize(2);
    check(vec.size() == 2, "error in resize");
    check(vec[1] == 2, "error in resize");

}

void testPushBack()
{
    MyVector<int> vec(2,2);
    vec.push_back(2);

    check(vec[2] == 2, "error in push_back");
}

void testIterators()
{
    MyVector<int> vec(3);
    for (int i = 0; i < 3; ++i) {
        vec[i] = i;
    }


    check( vec.size() == 3, "error in size");


    int i = 0;
    for(auto v : vec)
    {
        check(v == i, "error in 1 iterator");
        i++;
    }
    check(i == 3, "error in 1 iterator size");



    i = 0;
    for(auto it = vec.begin(); it != vec.end(); it++)
    {
        check(*it == i, "error in forward iterator");
        i++;
    }
    check(i == 3, "error in forward iterator size");


    i=2;
    for(auto it = vec.rbegin(); it != vec.rend(); it++)
    {
        check(*it == i, "error in reverse iterator");
        i--;
    }
    check(i == -1, "error in reverse iterator");
}


void testRandomAcessOperator()
{
    MyVector<int> vec(3,2);
    vec[0] = 50;
    vec[1] = 100;
    vec[2] = 200;

    check(vec[0] == 50, "error in [] operator");
    check(vec[1] == 100, "error in [] operator");
    check(vec[2] == 200, "error in [] operator");

}


void testPopBack()
{
    MyVector<int> vec(4,2);
    vec.pop_back();

    check(vec.size()==3, "error in pop_back 1 ");

}


int main() {

    testIterators();
    testPushBack();
    testRandomAcessOperator();
    testResize();
    testPopBack();

    return 0;
}