#include <iostream>
#include <stdexcept>
#include "iterator.hpp"

template <class T>
class Vector{
public:
    using size_type = size_t;
    using value_type = T;
    using iterator = Iterator<T>;
    using reverse_iterator = ReverseIterator<T>;
    
    Vector(): size_(0), capacity_(0), data_(nullptr) {};
    Vector(size_t size): size_(size), capacity_(size), data_(new Vector<T>::value_type[size]) {};
    Vector(const Vector& other);
    ~Vector(){ delete [] data_;}
    
    void push_back(const value_type& value);
    void resize(size_type size);
    void resize(size_type size, const value_type& value);
    
    value_type& operator[](size_type index){
        if (index >= size_)
            throw std::invalid_argument("Out range of index");
        return data_[index];
    }
    iterator begin(){ 
        return iterator(data_);
    }
    iterator end(){ 
        return iterator(data_ + size_);
    }
    reverse_iterator rbegin(){
        return reverse_iterator(data_ + size_ - 1);
    }
    reverse_iterator rend(){
        return reverse_iterator(data_ - 1);
    }
    void pop_back(){
        --size_;
    }
    bool empty(){
        return size_ == 0;
    }
    size_type size(){
        return size_;
    }
    size_type capacity(){
        return capacity_;
    }
    void clear(){
        size_ = 0;
    }
private:
    size_type size_;
    size_type capacity_;
    value_type* data_;
};

template <class T>
Vector<T>::Vector(const Vector& other){
    data_ = new value_type[other.size_];
    size_ = other.size_;
    capacity_ = other.capacity_;
    for (int i = 0; i < size_; ++i)
        data_[i] = other.data_[i];
}

template <class T>
void Vector<T>::push_back(const value_type& value){
    if (capacity_ == 0){
        value_type* data = new value_type[1];
        data[0] = value;
        size_ = capacity_ = 1;
        data_ = data;
        return;
    }
    if (capacity_ > size_){
        data_[size_] = value;
        ++size_;
        return;
    }
    value_type* data = new value_type[2 * size_];
    for (int i = 0; i < size_; ++i)
        data[i] = data_[i];
    data[size_] = value;
    delete [] data_;
    data_ = data;
    capacity_ = 2 * size_;
    ++size_;
}

template <class T>
void Vector<T>::resize(size_type new_size){
    if (new_size == size_)
        return;
    
    value_type* data = new value_type[new_size]; 
    for (int i = 0; i < new_size; ++i)
        if (new_size > size_ && i >=size_)
            data[i] = value_type();
        else
            data[i] = data_[i];

    delete [] data_;
    data_ = data;
    size_ = new_size;
    capacity_ = new_size;
}

template <class T>
void Vector<T>::resize(size_type new_size, const value_type& value){
    if (new_size == size_)
        return;
    
    value_type* data = new value_type[new_size]; 
    for (int i = 0; i < new_size; ++i)
        if (new_size > size_ && i >=size_)
            data[i] = value;
        else
            data[i] = data_[i];

    delete [] data_;
    data_ = data;
    size_ = new_size;
    capacity_ = new_size;
}
