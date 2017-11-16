#pragma once

template <class T>
class Iterator: public std::iterator<std::random_access_iterator_tag, T>
{
public:
    explicit Iterator(T* ptr)
                    :ptr_(ptr) {}

    T& operator*() const {
        return *ptr_;
    }


    bool operator==(const Iterator& other) const {
        return other.ptr_ == ptr_;
    }


    bool operator!=(const Iterator& other) const {
        return !(*this == other);
    }


    bool operator<(const Iterator& other) const {
        return ptr_ < other.ptr_;
    }


    bool operator>(const Iterator& other) const {
        return ptr_ > other.ptr_;
    }


    Iterator& operator++() {
        ptr_++;
        return *this;
    }


    Iterator operator++(int) {
        Iterator tmp(ptr_);
        ptr_++;
        return tmp;
    }


    Iterator& operator--() {
        ptr_--;
        return *this;
    }


    Iterator operator--(int) {
        Iterator tmp(ptr_);
        ptr_--;
        return tmp;
    }


    Iterator& operator+(size_t n) {
        ptr_ += n;
        return *this;
    }


    Iterator& operator-(size_t n) {
        ptr_ -= n;
        return *this;
    }

private:
    T* ptr_;

};


template <class T>
class ReverseIterator: public std::reverse_iterator <std::iterator<std::random_access_iterator_tag, T> >
{
public:
    explicit ReverseIterator(T* ptr)
                    :ptr_(ptr) {}


    T& operator*() const {
        return *ptr_;
    }


    bool operator==(const ReverseIterator& other) const {
        return other.ptr_ == ptr_;
    }


    bool operator!=(const ReverseIterator& other) const {
        return !(*this == other);
    }


    bool operator<(const ReverseIterator& other) const {
        return ptr_ > other.ptr_;
    }


    bool operator>(const ReverseIterator& other) const {
        return ptr_ < other.ptr_;
    }


    ReverseIterator& operator++() {
        ptr_--;
        return *this;
    }


    ReverseIterator operator++(int) {
        ReverseIterator tmp(ptr_);
        ptr_--;
        return tmp;
    }


    ReverseIterator& operator--() {
        ptr_++;
        return *this;
    }


    ReverseIterator operator--(int) {
        ReverseIterator tmp(ptr_);
        ptr_++;
        return tmp;
    }


    ReverseIterator& operator+(size_t n) {
        ptr_ -= n;
        return *this;
    }


    ReverseIterator& operator-(size_t n) {
        ptr_ += n;
        return *this;
    }

private:
    T* ptr_;

};
