#include <iostream>
#include <string>
#include "iterator.h"
#include "vector.h"
void check_empty();
void check_size();
void check_get_set();
void check_pop_back();
void check_push_back();
void check_resize();
void check_clear();
void check_iterators();
void tests();

int main() {
    try {
        tests();
    } catch (...) {
        std::cerr << "Unexpected error!" << std::endl;
        return -1;
    }
    return 0;
}
void tests() {
    std::cout << "Test" << std::endl;
    std::cout << "Empty" << std::endl;
    check_empty();
    std::cout << "Size" << std::endl;
    check_size();
    std::cout << "Get set (operator [])" << std::endl;
    check_get_set();
    std::cout << "Pop back" << std::endl;
    check_pop_back();
    std::cout << "Push back" << std::endl;
    check_push_back();
    std::cout << "Resize (5, 12, 8; \"aaa\" or value-intialization as default)"
              << std::endl;
    check_resize();
    std::cout << "Clear" << std::endl;
    check_clear();
    std::cout << "Iterators" << std::endl;
    check_iterators();
}
void check(bool value) {
    if (!value) std::cout << "test failed" << std::endl;
}

void check_get_set() {
    Vector<int> v1;
    Vector<int> v2(1, 1);
    Vector<int> v3(4, 3);
    Vector<int> v4(4);

    // add out of range test
    try {
        v1[0] = 0;
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
        std::cout << "Can't use [] for empty vector as expected" << std::endl;
    }
    check(v2[0] == 1);
    v2[0] = 3;
    check(v2[0] == 3);

    std::cout << "=================" << std::endl;
}

void check_empty() {
    Vector<int> v1;
    Vector<int> v2(1, 1);
    Vector<int> v3(4, 3);
    Vector<int> v4(4);

    check(v1.empty() == true);
    check(v2.empty() == false);
    check(v3.empty() == false);
    check(v4.empty() == false);

    std::cout << "=================" << std::endl;
}

void check_size() {
    Vector<int> v1;
    Vector<int> v2(1, 1);
    Vector<int> v3(4, 3);
    Vector<int> v4(4);

    check(v1.size() == 0);
    check(v2.size() == 1);
    check(v3.size() == 4);
    check(v4.size() == 4);

    std::cout << "=================" << std::endl;
}

void check_pop_back() {
    Vector<int> v1;
    Vector<int> v2(1, 1);
    Vector<int> v3(4, 3);
    Vector<int> v4(4);
    std::cout << v1 << std::endl;
    try {
        v1.pop_back();
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
        std::cout << "Can't use pop_back() for empty vector as expected"
                  << std::endl;
    }
    check(v1.size() == 0);
    std::cout << v1 << std::endl;

    std::cout << v2 << std::endl;
    v2.pop_back();
    check(v2.size() == 0);
    std::cout << v2 << std::endl;

    std::cout << v3 << std::endl;
    v3.pop_back();
    check(v3.size() == 3);
    std::cout << v3 << std::endl;

    std::cout << v4 << std::endl;
    v4.pop_back();
    check(v4.size() == 3);
    std::cout << v4 << std::endl;

    std::cout << "=================" << std::endl;
}

void check_push_back() {
    Vector<int> v1;
    Vector<int> v2(1, 1);
    Vector<int> v3(4, 3);
    Vector<int> v4(4);

    std::cout << v1 << std::endl;
    v1.push_back(1);
    check(v1.size() == 1);
    std::cout << v1 << std::endl;

    std::cout << v2 << std::endl;
    v2.push_back(1);
    check(v2.size() == 2);
    check(v2[1] == 1);
    std::cout << v2 << std::endl;

    std::cout << v3 << std::endl;
    v3.push_back(1);
    check(v3.size() == 5);
    check(v3[4] == 1);
    std::cout << v3 << std::endl;

    std::cout << v4 << std::endl;
    v4.push_back(1);
    check(v4.size() == 5);
    check(v4[4] == 1);
    std::cout << v4 << std::endl;

    std::cout << "=================" << std::endl;
}

void check_clear() {
    Vector<int> v1;
    Vector<int> v2(1, 1);
    Vector<int> v3(4, 3);
    Vector<int> v4(4);

    std::cout << v1 << std::endl;
    v1.clear();
    check(v1.empty());
    std::cout << v1 << std::endl;

    std::cout << v2 << std::endl;
    v2.clear();
    check(v2.empty());
    std::cout << v2 << std::endl;

    std::cout << v3 << std::endl;
    v3.clear();
    check(v3.empty());
    std::cout << v3 << std::endl;

    std::cout << v4 << std::endl;
    v4.clear();
    check(v4.empty());
    std::cout << v4 << std::endl;

    std::cout << "=================" << std::endl;
}

void check_resize() {
    Vector<std::string> v1;

    std::cout << v1 << std::endl;
    v1.resize(5);
    std::cout << v1 << std::endl;
    v1.resize(12, "aaa");
    std::cout << v1 << std::endl;
    v1.resize(8);
    std::cout << v1 << std::endl;
    std::cout << "=================" << std::endl;
}
void check_iterators() {
    Vector<int> v1(5);
    int i = 0;
    for (i = 0; i < 5; i++) {
        v1[i] = i;
    }
    i = 0;
    std::cout << "Forward ";
    for (auto it = v1.begin(); it < v1.end(); ++it, i++) {
        check(*it == i);
        std::cout << *it << " ";
    }
    i = 4;
    std::cout << std::endl << "Reverse ";
    for (auto it = v1.rbegin(); it < v1.rend(); ++it, i--) {
        check(*it == i);
        std::cout << *it << " ";
    }
    std::cout << std::endl << "=================" << std::endl;
}
