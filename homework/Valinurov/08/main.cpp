#include <cstdio>
#include <iostream>
#include <set>
#include "vector.hpp"

void check_constructor()
{
    vector<int> a(3, 4);
    for (size_t i = 0; i < 3; i++)
        if (a[i] != 4)
        {
            std::cout << "error in constructor";
            break;
        }

    vector<int> b(4);
    if (b.size() != 4)
        std::cout << "error in constructor";

    vector<int> c = {1, 2, 3, 4};
    for (size_t i = 0; i < 4; i++)
        if (c[i] != i + 1)\
        {
            std::cout << "error in constructor";
            break;
        }
}

void check_push_back()
{
    std::set<int> a = {1, 2, 3};
    std::set<int> b = {1, 2, 3};
    std::set<int> d = {1, 2, 3};
    vector<std::set<int> > c(1);
    c[0] = a;
    c.push_back(b);
    c.push_back(std::move(d));
    if (c.size() != 3 || c.capacity() != 4)
        std::cout << "error in push_back";

    for (vector<std::set<int> >::iterator i = c.begin(); i != c.end(); ++i)
        if ((*i).size() != 3)
            std::cout << "error in push_back";
}

void check_indexing()
{
    vector<int> a(3);
    a[0] = a[1] = a[2] = 2;
    if (a[1] != 2)
        std::cout << "error in indexing";

    a.resize(6);
    a[3] = a[4] = a[5] = 3;
    if (a[5] != 3)
        std::cout << "error in indexing";

    a.push_back(4);
    a[6] = 5;
    if (a[6] != 5)
        std::cout << "error in indexing";
}

void check_size()
{
    vector<int> a = {1, 2, 3, 4};
    a.resize(5, 5);
    if (a.size() != 5)
        std::cout << "error in resize";
    for (size_t i = 0; i < 5; i++)
        if (a[i] != i + 1)
        {
            std::cout << a[i];
            std::cout << "error in resize";
            break;
        }

    a.resize(0);
    if (a.size() != 0 || !a.empty())
        std::cout << "error in resize";

    a.push_back(1);
    if (a.size() != 1)
        std::cout << "error in resize";
    a.push_back(2);
    a.pop_back();
    if (a.size() != 1)
        std::cout << "error in resize";

    for (int i = 0; i < 8; i++)
        a.push_back(i);

    a.clear();
    if (a.size() != 0 || a.capacity() != 10)
        std::cout << "error in resize";

}

void check_iterator()
{
    const char* ms = "error in iteration";
    vector<int> a = {1, 2, 3, 4, 5, 6, 7};
    int n = 1;
    for (vector<int>::iterator i = a.begin(); i != a.end(); ++i)
        if (*i != n++)
        {
            std::cout << ms;
            break;
        }

    for (vector<int>::reverse_iterator i = a.rbegin(); i != a.rend(); ++i)
        if (*i != --n)
        {
            std::cout << ms;
            break;
        }

    for (vector<int>::const_iterator i = a.cbegin(); i != a.cend(); ++i)
        if (*i != n++)
        {
            std::cout << ms;
            break;
        }

    for (vector<int>::const_reverse_iterator i = a.crbegin(); i != a.crend(); ++i)
        if (*i != --n)
        {
            std::cout << ms;
            break;
        }
}

int main(){
    check_constructor();
    check_iterator();
    check_push_back();
    check_size();
    check_indexing();
    return 0;
}
