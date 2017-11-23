#pragma once

#include <iterator>


template<class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T> {

public:
    explicit Iterator(T* ptr) : ptr_(ptr) {}

    Iterator& operator++() {
        ++ptr_;

        return (*this);
    }

    Iterator& operator--() {
        --ptr_;

        return (*this);
    }

    Iterator operator+(int x) {
        return Iterator(ptr_ + x);
    }

    Iterator operator-(int x) {
        return Iterator(ptr_ - x);
    }

    Iterator& operator+=(int x) {
        ptr_ += x;

        return (*this);
    }

    Iterator& operator-=(int x) {
        ptr_ -= x;

        return (*this);
    }

    bool operator==(const Iterator& it) {
        return (ptr_ == it.ptr_);
    }

    bool operator!=(const Iterator& it) {
        return (ptr_ != it.ptr_);
    }

    T& operator*() {
        return (*ptr_);
    }

    T* operator->() {
        return ptr_;
    }

private:
    T* ptr_;
};
