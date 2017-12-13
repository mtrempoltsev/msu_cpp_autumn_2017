//
//  vector.h
//  myvector
//
//  Created by Павел Адаменко on 12/13/17.
//  Copyright © 2017 Павел Адаменко. All rights reserved.
//

#ifndef vector_h
#define vector_h
#include "iterator.h"
#include <iostream>

template <class T, class Alloc = std::allocator<T>>
class  Vector
{
private:
    T* data;
    size_t len;
    size_t capacity;
public:
    using iterator = Iterator<T>;
    using Riterator = Reverse_Iterator<T>;
    
    Vector(){
        len     = 0;
        capacity = 0;
    }
    
    explicit Vector(size_t count){
        len     = count;
        capacity = count * 5;
        data     = new T[capacity];
    }
    
    explicit Vector(size_t count, const T& defaultValue){
        len = count;
        capacity = count * 5;
        data = new T[capacity];
        for (size_t i = 0; i < len; ++i){
            data[i] = defaultValue;
        }
    }
    
    size_t size() const noexcept{
        return len;
    }
    
    size_t __capacity() const noexcept{
        return capacity;
    }
    
    T& operator[](size_t position){
        if (position >= len)
            throw ("Segmentation fault");
        return this -> data[position];
    }
    

    
    Iterator<T> begin() noexcept{
        return Iterator<T> (this->data);
    }
    
    Iterator<T> end() noexcept{
        return Iterator<T>(this->data + this->len);
    }
    
    Reverse_Iterator<T> rbegin() noexcept{
        return Reverse_Iterator<T>(this->data + this->len - 1);
    }
    
    Reverse_Iterator<T> rend() noexcept{
        return Reverse_Iterator<T>(this->data - 1);
    }
    
    void resize(size_t new_len){
        *this = move(Vector(new_len));
    }
    
    void resize(size_t new_len, const T& defaultValue){
        *this = move(Vector(new_len, defaultValue));
    }
    
    bool empty(){
        return this->len == 0;
    }
    
    void clear(){
        *this = move(Vector());
    }
    
    void push_back(const T& value){
        if(this->data == nullptr)
        {
            *this = move(Vector(5));
            this->len = 0;
        }
        if(this->len == this->capacity)
        {
            auto time_vec = move(*this);
            this->resize(this->capacity);
            for (size_t j = 0; j < this->len; j++)
                this->data[j] = time_vec[j];
        }
        this->data[this->len++] = value;
    }
    
    void print(){
        for(T n: *this)
            std :: cout << n << " ";
    }
    
    T pop_back(){
        if (len == 0)
            throw "Segmentation fault";
        else if (len == 1)
            this->clear();
        else
            len--;
            return data[len];
    }
    
};


#endif /* vector_h */
