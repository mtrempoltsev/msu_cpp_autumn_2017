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
    num_of_errors += check(vect.capacity() == 4 && vect.size() == 4 && vect[0] == 1 && vect[1] == 2 && vect[2] == 3 && vect[3] == 4);

    // push_back
    vect.push_back(6);
    Vector<int> v1 = {1, 2, 3, 4, 6};

    num_of_errors += check(vect.capacity() == 8 && vect == v1);

    // resize
    //vect.



/*

    vect.resize(10);
    std::cout << vect << std::endl;
    std::cout << vect.capacity() << ' ' << vect.size() << std::endl;

    vect.resize(2);
    std::cout << vect << std::endl;
    std::cout << vect.capacity() << ' ' << vect.size() << std::endl;

    vect.resize(6, 9);
    std::cout << vect << std::endl;
    std::cout << vect.capacity() << ' ' << vect.size() << std::endl;
*/




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



/*
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int> v1 = {1, 2, 3, 4, 4};
    if (v == v1) {
        std::cout << "lol\n";
    }
    v.resize(2, 10);
    std::cout << v.capacity() << ' ' << v.size() << std::endl;
    for (auto& k : v) {
        std::cout << k << ' ';
    }
    std::cout << std::endl;*/


    return 0;
}
