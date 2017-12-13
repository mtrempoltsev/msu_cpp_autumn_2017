//
//  iterator.h
//  myvector
//
//  Created by Павел Адаменко on 12/13/17.
//  Copyright © 2017 Павел Адаменко. All rights reserved.
//

#ifndef iteration_h
#define iteration_h
#include <iostream>
using namespace std;

template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
private:
    T* p;
    
public:
    explicit Iterator<T>(T* ptr){
        p = ptr;
    }
    
    Iterator<T> operator ++(){
        p++;
        return *this;
    }
    
    Iterator<T> operator --(){
        p--;
        return *this;
    }
    
    bool operator == (const Iterator& tmp){
        return p == tmp.p;
    }
    
    bool operator != (const Iterator& tmp){
        return p != tmp.p;
    }
    
    T& operator*(){
        return *p;
    }
    
    T* operator->(){
        return p;
    }
};

template <class T>
class Reverse_Iterator : public std::iterator<std::random_access_iterator_tag, T>
{
private:
    T* p;
public:
    explicit Reverse_Iterator<T>(T* ptr){
        p = ptr;
    }
    
    Reverse_Iterator<T> operator ++(){
        p--;
        return *this;
    }
    
    Iterator<T> operator --(){
        p++;
        return *this;
    }
    
    bool operator == (const Reverse_Iterator& tmp){
        return p == tmp.p;
    }
    
    bool operator != (const Reverse_Iterator& tmp){
        return p != tmp.p;
    }
    
    T& operator*(){
        return *p;
    }
    
    T* operator->(){
        return p;
    }
    
};


#endif /* iteration_h */
