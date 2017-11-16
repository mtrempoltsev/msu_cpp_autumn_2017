#include "Vector.hpp"
#include <iostream>
#include <vector>
#include <cassert>

template<typename _T>
void test_assert(_T val1, _T val2) {
    if (val1 != val2) assert(!"Fail");
}

template<typename _T>
void prepare_simple_test() {
    Vector<_T> myvec;
    test_assert<size_t>(myvec.capacity(), 0);
    test_assert<size_t>(myvec.empty(), true);
    test_assert<size_t>(myvec.size(), 0);
    for (int i = 0; i < 15; ++i) {
        myvec.push_back(10 * i);
    }
    test_assert<size_t>(myvec.capacity(), 15);
    test_assert<size_t>(myvec.empty(), false);
    test_assert<size_t>(myvec.size(), 15);
    int i = 0;
    for (auto it = myvec.begin(); it != myvec.end(); ++it, ++i) {
        test_assert<_T>(*it, 10 * i);
    }
    myvec.resize(17);
    test_assert<size_t>(myvec.capacity(), 35);
    test_assert<size_t>(myvec.empty(), false);
    test_assert<size_t>(myvec.size(), 17);

    myvec[15] = 81;
    test_assert<_T>(myvec[15], 81);

    myvec[16] = 142;
    test_assert<_T>(myvec[16], 142);
    test_assert<size_t>(myvec.capacity(), 35);
    test_assert<size_t>(myvec.empty(), false);
    test_assert<size_t>(myvec.size(), 17);

    int j = 0;
    for (auto it = myvec.rbegin(); it != myvec.rend(); ++it, ++j) {
        if (j == 0) {
            test_assert<_T>(*it, 142);
        } else if (j == 1) {
            test_assert<_T>(*it, 81);
        } else {
            test_assert<_T>(*it, 150 - 10 * (j - 1));
        }
    }
    test_assert<_T>(myvec[0], 0);
    test_assert<size_t>(myvec.capacity(), 35);
    test_assert<size_t>(myvec.empty(), false);
    test_assert<size_t>(myvec.size(), 17);

    myvec.clear();
    test_assert<size_t>(myvec.capacity(), 35);
    test_assert<size_t>(myvec.empty(), true);
    test_assert<size_t>(myvec.size(), 0);

    myvec.push_back(14);
    test_assert<_T>(myvec[0], 14);
    test_assert<_T>(*myvec.begin(), 14);
    test_assert<_T>(*myvec.rbegin(), 14);

    myvec.push_back(12);
    test_assert<_T>(myvec[1], 12);
    test_assert<_T>(*++myvec.begin(), 12);
    test_assert<_T>(*myvec.rbegin(), 12);

    test_assert<size_t>(myvec.capacity(), 35);
    test_assert<size_t>(myvec.empty(), false);
    test_assert<size_t>(myvec.size(), 2);

    int k = 0;
    for (auto it = myvec.rbegin(); it != myvec.rend(); ++it, ++k) {
        if (k == 0) {
            test_assert<_T>(*it, 12);
        }
        if (k == 1) {
            test_assert<_T>(*it, 14);
        }
    }
    myvec.pop_back();
    test_assert<size_t>(myvec.capacity(), 35);
    test_assert<size_t>(myvec.empty(), false);
    test_assert<size_t>(myvec.size(), 1);
    int t = 0;
    for (auto it = myvec.begin(); it != myvec.end(); ++it, ++t) {
        if (t == 0) {
            test_assert<_T>(*it, 14);
        }
    }
}

int main()
{
    prepare_simple_test<int>();
    std::cout << "Passed Success" << std::endl;
    return 0;
}
