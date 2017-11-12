#include <iostream>
#include <stdexcept>
#include <vector> // to check move
#include "Vector.h"

bool fail(bool setFail = false) {
    static bool isFailed = false;
    isFailed = (setFail || isFailed);
    return isFailed;
}

template <typename T, typename V>
void checkEquals(T a, V b, double eps = 1e-5) {
    bool equals = ((a < b + eps) && (a > b - eps));
    if (!equals) {
        std::cout << "[FAIL]: " << a << " != " << b << std::endl;
        fail(true);
    } else {
        std::cout << "[OK]: " << a << " == " << b << std::endl;
    }
}

void checkThrows(std::function<void ()> f) {
    try {
        f();
    } catch (const std::exception& e) {
        std::cout << "[OK]: Thrown as expected: " << e.what() << std::endl;
        return;
    }
    std::cout << "[FAIL]: Not thrown but expected" << std::endl;
    fail(true);
}

void checkConstructor() {
    std::cout << "===== checkConstructor =====" << std::endl;
    vector<int> vec = {1, 2, 42, 100500};

    checkEquals(vec.size(), 4);
    checkEquals(vec.capacity(), 4);
    checkEquals(vec[0], 1);
    checkEquals(vec[1], 2);
    checkEquals(vec[2], 42);
    checkEquals(vec[3], 100500);
}

void checkAccess() {
    std::cout << "===== checkAccess =====" << std::endl;

    vector<int> vec(10);

    for (int i = 0; i < 5; ++i) {
        vec[i] = i;
        checkEquals(vec[i], i);
    }
    //checkThrows([] () { Matrix<double>(0, 1); });
}

void checkSize() {
    std::cout << "===== checkSize =====" << std::endl;

    vector<int> vec(5);
    checkEquals(vec.size(), 5);
}

void checkPush() {
    std::cout << "===== checkPush =====" << std::endl;

    vector<int> vec(16);
    vec[0] = 0;
    vec[1] = 1;
    vec[2] = 2;
    vec.push_back(42);
    vec.push_back(84);

    checkEquals(vec.size(), 18);
    checkEquals(vec.capacity(), 32);
    checkEquals(vec[0], 0);
    checkEquals(vec[1], 1);
    checkEquals(vec[2], 2);
    checkEquals(vec[16], 42);
    checkEquals(vec[17], 84);

    // now checking move semantics

    std::cout << "Checking move semantics:" << std::endl;
    vector<std::vector<int>> v;
    std::vector<int> moved(10);
    checkEquals(moved.size(), 10);
    v.push_back(std::move(moved));
    checkEquals(moved.size(), 0);
    checkEquals(v[0].size(), 10);
    checkEquals(v.size(), 1);
}

void checkIteration() {
    std::cout << "===== checkIteration =====" << std::endl;

    vector<int> vec;
    int values[] = {1, 2, 3, 42};
    vec.push_back(values[0]);
    vec.push_back(values[1]);
    vec.push_back(values[2]);
    vec.push_back(values[3]);

    std::cout << "Checking forward:" << std::endl;
    int i = 0;
    for (auto e : vec) {
        checkEquals(e, values[i]);
        ++i;
    }

    std::cout << "Checking reverse:" << std::endl;
    i = 1;
    for (vector<int>::reverse_iterator it = vec.rbegin(); it != vec.rend(); ++it) {
        checkEquals(*it, values[vec.size() - i]);
        ++i;
    }

    std::cout << "Checking access:" << std::endl;
    auto it = vec.begin();
    ++it;
    *it = 128;
    checkEquals(vec[1], 128);

    std::cout << "Checking const:" << std::endl;
    const vector<int> cvec = {10, 2, 42, 100500};
    auto begin_it = cvec.begin();
    ++begin_it;
    ++begin_it;
    ++begin_it;
    checkEquals(*begin_it, 100500);

    auto rbegin_it = cvec.rbegin();
    ++rbegin_it;
    ++rbegin_it;
    ++rbegin_it;
    checkEquals(*rbegin_it, 10);
}

void checkPop() {
    std::cout << "===== checkPop =====" << std::endl;
    vector<int> vec = {1, 2, 42, 100500};
    vec.pop_back();
    checkEquals(*vec.rbegin(), 42);
}

void checkClear() {
    std::cout << "===== checkClear =====" << std::endl;
    vector<int> vec = {1, 2, 42, 100500};
    vec.clear();
    checkEquals(vec.size(), 0);
}

void checkEmpty() {
    std::cout << "===== checkEmpty =====" << std::endl;
    vector<int> vec = {1, 2, 42, 100500};
    checkEquals(vec.empty(), false);
    vec.clear();
    checkEquals(vec.empty(), true);
}

void checkResize() {
    std::cout << "===== checkResize =====" << std::endl;

    vector<int> vec;

    vec.push_back(0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    vec.resize(10, 42);
    checkEquals(vec[4], 42);
    checkEquals(vec[5], 42);
    checkEquals(vec[6], 42);
    checkEquals(vec[9], 42);
    checkEquals(vec.size(), 10);

    vec.resize(2);
    checkEquals(vec.size(), 2);
    checkEquals(vec.capacity(), 16);

    vec.resize(20);
    checkEquals(vec.size(), 20);
    checkEquals(vec.capacity(), 20);
}

void runTests() {
    checkConstructor();
    checkAccess();
    checkSize();
    checkPush();
    checkIteration();
    checkPop();
    checkClear();
    checkEmpty();
    checkResize();

    std::cout << "====================" << std::endl;
    if (fail()) {
        std::cout << "[FAIL] one or more tests has failed" << std::endl;
    } else {
        std::cout << "[OK] all tests are ok" << std::endl;
    }
}

int main(int argc, char const *argv[]) {
    try {
        runTests();
    } catch (...) {
        std::cout << "Unknown error occured" << std::endl;
        return 1;
    }
    return 0;
}