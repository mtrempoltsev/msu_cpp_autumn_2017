#ifndef ITERATOR_H
#define ITERATOR_H

#include <memory>

template <class T>
class Iterator
        : public std::iterator<std::forward_iterator_tag, T>
{
private:
    T* ptr_;
public:
    using reference = T&;

    explicit Iterator(T* ptr)
      : ptr_(ptr)
    {}

    bool operator==(const Iterator<T>& other) const
    {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Iterator<T>& other) const
    {
        return !(*this == other);
    }

    reference operator*() const
    {
        return *ptr_;
    }

    reference operator*()
    {
        return *ptr_;
    }

    Iterator& operator++()
    {
        ptr_++;
        return *this;
    }

    Iterator& operator+(size_t n) {
        ptr_ += n;
        return *this;
    }

    bool operator<(const Iterator& other) const
    {
        return ptr_ < other.ptr_;
    }


    bool operator>(const Iterator& other) const
    {
        return ptr_ > other.ptr_;
    }



    T* operator->()
    {
        return ptr_;
    }
};

template <class T>
class RIterator
        : public std::iterator<std::forward_iterator_tag, T>
{
private:
    T* ptr_;
public:
    using reference = T&;

    explicit RIterator(T* ptr)
      : ptr_(ptr)
    {}

    bool operator==(const RIterator<T>& other) const
    {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const RIterator<T>& other) const
    {
        return !(*this == other);
    }

    reference operator*() const
    {
        return *ptr_;
    }

    reference operator*()
    {
        return *ptr_;
    }

    RIterator& operator++()
    {
        ptr_--;
        return *this;
    }

    bool operator<(const RIterator& other) const
    {
        return ptr_ < other.ptr_;
    }


    bool operator>(const RIterator& other) const
    {
        return ptr_ > other.ptr_;
    }

    RIterator& operator+(size_t n) {
        ptr_ -= n;
        return *this;
    }

    T* operator->()
    {
        return ptr_;
    }
};



#endif // ITERATOR_H
