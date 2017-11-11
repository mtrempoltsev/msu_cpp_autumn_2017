#include <iostream>
#include <vector>
#include <exception>

#include "vector.cpp"


int check(bool value) {
    return int (!value);
}


void test_vector() {
    int num_of_errors = 0;

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
    ans = std::move(Vector<int>(0));

    num_of_errors += check(vect.capacity() == 10 && vect == ans);


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
