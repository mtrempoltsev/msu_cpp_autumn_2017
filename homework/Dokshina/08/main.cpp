#include <iostream>
#include <vector>
#include <string>
#include <exception>

#include "vector.cpp"


int check(bool value) {
    return int (!value);
}


void test_vector() {
    int num_of_errors = 0;


    // Vector<int> tests
    // constructor and operator[]
    Vector<int> vect = {1, 2, 3, 4};
    num_of_errors += check(vect.capacity() == 4 && vect.size() == 4 &&
                vect[0] == 1 && vect[1] == 2 && vect[2] == 3 && vect[3] == 4);

    // push_back
    vect.push_back(6);
    Vector<int> ans = {1, 2, 3, 4, 6};

    num_of_errors += check(vect.capacity() == 8 && vect == ans);

    // resize (size_t)
    vect.resize(2);
    ans = {1, 2};

    num_of_errors += check(vect.capacity() == 8 && vect == ans);

    // resize (size_t)
    vect.resize(5);
    ans = {1, 2, 0, 0, 0};

    num_of_errors += check(vect.capacity() == 8 && vect == ans);

    // resize (size_t, default_value)
    vect.resize(10, 11);
    ans = {1, 2, 0, 0, 0, 11, 11, 11, 11, 11};

    num_of_errors += check(vect.capacity() == 10 && vect == ans);

    // pop_back
    vect.pop_back();
    ans = {1, 2, 0, 0, 0, 11, 11, 11, 11};

    num_of_errors += check(vect.capacity() == 10 && vect == ans);

    // clear
    vect.clear();
    ans = Vector<int>();

    num_of_errors += check(vect.capacity() == 10 && vect == ans);


    // Vector<std::string> tests
    // constructor
    Vector<std::string> vect_str(5, "abc");
    Vector<std::string> ans_str = {"abc", "abc", "abc", "abc", "abc"};

    num_of_errors += check(vect_str.capacity() == 5 && vect_str == ans_str);

    // pop_back
    vect_str.pop_back();
    ans_str = {"abc", "abc", "abc", "abc"};
    num_of_errors += check(vect_str.capacity() == 5 && vect_str == ans_str);

    // push_back
    vect_str.push_back("gcc");
    ans_str = {"abc", "abc", "abc", "abc", "gcc"};
    num_of_errors += check(vect_str.capacity() == 5 && vect_str == ans_str);

    // resize (size_t, default_value)
    vect_str.resize(7, "hi");
    ans_str = {"abc", "abc", "abc", "abc", "gcc", "hi", "hi"};
    num_of_errors += check(vect_str.capacity() == 7 && vect_str == ans_str);

    // resize (size_t, default_value)
    vect_str.resize(6);
    ans_str = {"abc", "abc", "abc", "abc", "gcc", "hi"};
    num_of_errors += check(vect_str.capacity() == 7 && vect_str == ans_str);

    vect_str.resize(6);
    ans_str = {"abc", "abc", "abc", "abc", "gcc", "hi"};
    num_of_errors += check(vect_str.capacity() == 7 && vect_str == ans_str);

    // iterator and operator[]
    size_t i = 0;
    for (auto it = vect_str.begin(); it < vect_str.end(); it++, i++) {
        num_of_errors += check(*it == ans_str[i]);
    }

    // reverse iterator and operator[]
    i = ans_str.size() - 1;
    for (auto it = vect_str.rbegin(); it < vect_str.rend(); it++, i--) {
        num_of_errors += check(*it == ans_str[i]);
    }


    if (num_of_errors == 0) {
        std::cout << "All tests passed." << std::endl;
    } else {
        std::cout << "Tests failed with " << num_of_errors << " errors." << std::endl;
    }
}


int main() {
    try {
        test_vector();
    } catch (std::exception& err) {
        std::cout << "Error: " << err.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Something wrong." << std::endl;
        return 1;
    }
    return 0;
}
