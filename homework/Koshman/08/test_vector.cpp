#include <iostream>
#include <stdexcept>
#include <memory>
#include <initializer_list>

#include "vector.cpp"


static bool error = false;
static int check_leak = 0;

void check(bool value) {
    if (!value){
        std::cout << "test failed";
        error = true;
    }
}

/*
 * structure to test for leaks
*/
struct B{
    B(){check_leak++;}
    ~B(){check_leak--;}
};

void test(){

    Vector<int> vect = {1, 2, 3, 4};

    Vector<int> vect2(0);

    check(!vect.empty());

    for (auto i = vect.begin(); i < vect.end(); ++i)
        vect2.push_back(*i);
    check(vect2 == vect);

    vect.erase(3);
    vect2.pop_back();
    check(vect == vect2);

    vect.resize(10);
    check(vect == vect2);

    vect.resize(0);
    check(vect != vect2);

    vect2.clear();
    check(vect == vect2);

    check(vect.empty());

    for (size_t i = 1; i < 5; i++)
        vect.push_back(i);

    Vector<int> vect3 = {4, 3, 2, 1};
    for (auto i = vect.rbegin(); i < vect.rend(); ++i)
        vect2.push_back(*i);
    
    check(vect2 == vect3);

    check(vect2.size() == 4);

    Vector<int> vect4 = {4, 3, 2, 1, 0, 1, 2, 3};
    for (size_t i = 0; i < 4; i++)
        vect2.push_back(i);

    check(vect4 == vect2);

    {
        Vector<B> vect5(5);
        vect5.resize(10);
        vect5.resize(2);
        vect5.pop_back();
    }
    check(check_leak == 0);

    {
        Vector<B> vect5(1);
        vect5.pop_back();
    }
    check(check_leak == 0);

    {
        Vector<B> vect5(10);
        vect5.erase(4);
    }
    check(check_leak == 0);

    {
        Vector<B> vect5(2);
        for (size_t i = 0; i < 1000; ++i)
            vect5.push_back(B());
        vect5.resize(10);
    }
    check(check_leak == 0);

    {
        Vector<B> vect5(2);
        for (size_t i = 0; i < 1000; ++i)
            vect5.push_back(B());
        vect5.clear();
    }
    check(check_leak == 0);

    if (!error) {
        std::cout << "Ok\n";
    }
}


int main(int argc, char const *argv[]) {
    test();
    return 0;
}
