#pragma once
#include <iterator>

template <typename T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
   public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type =
        typename std::iterator<std::random_access_iterator_tag,
                               T>::difference_type;

    explicit Iterator(value_type* ptr) : ptr_(ptr) {}

    value_type& operator*() const { return *ptr_; }
    pointer* operator->() const { return ptr_; }
    reference operator[](difference_type number) const { return ptr_[number]; }

    //+ AND -

    Iterator& operator++() {
        ++ptr_;
        return *this;
    }  // prefix
    Iterator& operator--() {
        --ptr_;
        return *this;
    }  // prefix

    Iterator operator+(difference_type number) {
        return Iterator(ptr_ + number);
    }
    Iterator operator-(difference_type number) {
        return Iterator(ptr_ - number);
    }
    Iterator& operator+=(difference_type number) {
        ptr_ += number;
        return *this;
    }
    Iterator& operator-=(difference_type number) {
        ptr_ -= number;
        return *this;
    }

    friend Iterator operator+(difference_type number,
                              const Iterator& iterator) {
        return Iterator(number + iterator.ptr_);
    }
    friend Iterator operator-(difference_type number,
                              const Iterator& iterator) {
        return Iterator(number - iterator.ptr_);
    }

    // COMPARING

    bool operator==(const Iterator& other) const { return ptr_ == other.ptr_; }
    bool operator!=(const Iterator& other) const { return !(*this == other); }
    bool operator>(const Iterator& other) const { return ptr_ > other.ptr_; }
    bool operator<(const Iterator& other) const { return ptr_ < other.ptr_; }
    bool operator>=(const Iterator& other) const { return !(*this < other); }
    bool operator<=(const Iterator& other) const { return !(*this > other); }

   private:
    T* ptr_;
};

template <typename T>
class ReverseIterator
    : public std::iterator<std::random_access_iterator_tag, T> {
   public:
    using value_type = T;
    typedef T* pointer;
    using reference = T&;
    using difference_type =
        typename std::iterator<std::random_access_iterator_tag,
                               T>::difference_type;

    explicit ReverseIterator(pointer ptr) : ptr_(ptr) {}

    reference operator*() const { return *ptr_; }
    pointer operator->() const { return ptr_; }
    reference operator[](difference_type number) const { return ptr_[number]; }

    //+ AND -

    ReverseIterator& operator++() {
        --ptr_;
        return *this;
    }  // prefix
    ReverseIterator& operator--() {
        ++ptr_;
        return *this;
    }  // prefix

    ReverseIterator operator+(difference_type number) {
        return ReverseIterator(ptr_ - number);
    }
    ReverseIterator operator-(difference_type number) {
        return ReverseIterator(ptr_ + number);
    }
    ReverseIterator& operator+=(difference_type number) {
        ptr_ -= number;
        return *this;
    }
    ReverseIterator& operator-=(difference_type number) {
        ptr_ += number;
        return *this;
    }

    friend ReverseIterator operator+(difference_type number,
                                     const ReverseIterator& iterator) {
        return ReverseIterator(number - iterator.ptr_);
    }
    friend ReverseIterator operator-(difference_type number,
                                     const ReverseIterator& iterator) {
        return ReverseIterator(number + iterator.ptr_);
    }

    // COMPARING

    bool operator==(const ReverseIterator& other) const {
        return ptr_ == other.ptr_;
    }
    bool operator!=(const ReverseIterator& other) const {
        return !(*this == other);
    }
    bool operator>(const ReverseIterator& other) const {
        return ptr_ < other.ptr_;
    }
    bool operator<(const ReverseIterator& other) const {
        return ptr_ > other.ptr_;
    }
    bool operator>=(const ReverseIterator& other) const {
        return !(*this < other);
    }
    bool operator<=(const ReverseIterator& other) const {
        return !(*this > other);
    }

   private:
    T* ptr_;
};
