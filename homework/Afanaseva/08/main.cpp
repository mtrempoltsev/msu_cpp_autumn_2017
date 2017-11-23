#include <iostream>
#include <stdexcept>

#include "vector.h"

using namespace std;

/*
 *  Написать свой контейнер Vector аналогичный std::vector и итератор для него.
 * Из поддерживаемых методов достаточно
 * operator[], push_back, pop_back,
 * empty, size, clear, begin, end,
 * rbegin, rend, resize.
 * */

int check(bool value) {
    if (!value)
        cout << "Failed" << endl;
    else
        cout << "Passed" << endl;
    return int (!value);
}


template<typename T>
void check_vector() {
    Vector<T> vect = {1, 2, 3, 4};
    Vector<T> ans = {1, 2, 3, 4};

    // operator[]
    cout << "operator[]: ";
    check(vect.capacity() == 4 && vect.size() == 4 &&
          vect[0] == 1 && vect[1] == 2 && vect[2] == 3 && vect[3] == 4);

    // operator==
    cout << "operator==: ";
    check(vect == ans);

    // push_back
    cout << "push_back: ";
    vect.push_back(6);
    ans = {1, 2, 3, 4, 6};
    check(vect.capacity() == 8 && vect == ans);

    // resize (size_t)
    cout << "resize to less size: ";
    vect.resize(2);
    ans = {1, 2};
    check(vect.capacity() == 8 && vect == ans);

    // resize (size_t)
    cout << "resize to bigger size: ";
    vect.resize(5);
    ans = {1, 2, 0, 0, 0};
    check(vect.capacity() == 8 && vect == ans);

    // resize (size_t, default_value)
    cout << "resize with default value: ";
    vect.resize(10, 11);
    ans = {1, 2, 0, 0, 0, 11, 11, 11, 11, 11};
    check(vect.capacity() == 10 && vect == ans);

    // pop_back
    cout << "pop_back: ";
    vect.pop_back();
    ans = {1, 2, 0, 0, 0, 11, 11, 11, 11};
    check(vect.capacity() == 10 && vect == ans);

    // clear
    cout << "clear: ";
    vect.clear();
    ans = std::move(Vector<T>(0));
    check(vect.capacity() == 10 && vect == ans);
}



int main()
{
    try
    {
        check_vector<int>();
    }
    catch (VectorError& e)
    {
        std::cout << "Error occured: " << e.what() << std::endl;
        return -1;
    }
    catch (...)
    {
        std::cout << "Unknown error occured." << std::endl;
        return -2;
    }
    return 0;
}
