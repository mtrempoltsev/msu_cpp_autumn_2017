#include <iostream>
#include <vector>
#include <typeinfo>
#include "myvector.h"

using namespace std;

void checkIterator(){
    MyVector<int> v(10);
    for(int i = 0; i < 10; ++i){
        v[i] = i;
    }
    int i = 0;
    for(auto val : v){
        if(val != i){
            cerr<<"iterator does not work\n";
        }
        ++i;
    }
}

void checkPushAndPop(){
    MyVector<int> v;

    v.push_back(10);
    auto ii = v.end();

    if(*(--v.end()) != 10){
        cerr<<"push does not work\n";
    }

    if(v[0] != 10){
        cerr<<"push does not work\n";
    }
    v.push_back(11);
    v.pop_back();

    for(auto val : v){
        if(val != 10){
            cerr<<"pop does not work\n";
        }
    }

    for(int i = 0; i < v.size(); ++i){
        if(v[i] != 10){
            cerr<<"pop does not work\n";
        }
    }
}


void checkOperator(){
    MyVector<int> v(10);
    for(int i = 0; i < 10; ++i){
        v[i] = i;
    }

    for(int i = 0; i < 10; ++i){
        if(v[i] != i){
            cerr<<"operator[] does not work\n";
        }
    }
}

int main()
{
    checkOperator();
    checkIterator();
    checkPushAndPop();
    cout<<"end checks\n";
    return 0;
}

