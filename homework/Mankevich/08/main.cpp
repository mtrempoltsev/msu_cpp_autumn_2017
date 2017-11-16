#include "vector.hpp"

void check(bool value){
    if (!value)
        std::cout << "Error" << std::endl;
}

void check_vec(){
    Vector<int> vec(10);
    check(vec.size() == 10);
    vec.push_back(2);
    check(vec[10] == 2);
    Vector<int> v(vec);
    check(v[10] == 2);
    check(v.size() == 11);
    v.resize(5);
    check(v.capacity() == 5);
}

void check_iter(){
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(3);
    Vector<int>::iterator iter = vec.begin();
    check(*iter == 1);
    ++iter;
    check(*iter == 3);
    ++iter;
    check(iter == vec.end());
    
    Vector<int> vect;
    vect.push_back(1);
    vect.push_back(3);
    Vector<int>::reverse_iterator itert = vect.rbegin();
    check(*itert == 3);
    ++itert;
    check(*itert == 1);
    ++itert;
    check(itert == vect.rend());
}

void check_clear(){
    Vector<int> vec;
    vec.resize(5, 7);
    vec.clear();
    vec.push_back(3);
    check(vec.size() == 1);
}

int main(){
    try{
        check_vec();
        check_iter();
        check_clear();
    }
    catch(std::invalid_argument& e){
        std ::cout << e.what() << std::endl;
    }
    return 0;
}