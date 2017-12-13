#pragma once
#include <memory>
#include "iterator.h"
template <typename T>
class Vector {
   public:
    using size_type = size_t;
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;
    typedef Iterator<T> iterator;
    typedef Iterator<const T> const_iterator;
    using reverse_iterator = ReverseIterator<T>;
    using const_reverse_iterator = ReverseIterator<const T>;

    Vector() : size_(0), capacity_(0), buffer_(nullptr){};
    explicit Vector(size_type size) : size_(size), capacity_(size) {
        buffer_ = new value_type[capacity_];
    }

    explicit Vector(size_type size, const_reference default_value)
        : size_(size), capacity_(size) {
        buffer_ = new value_type[capacity_];
        for (size_type i = 0; i < size_; i++) {
            buffer_[i] = default_value;
        }
    }
   

    ~Vector() { delete[] buffer_; }

    bool empty() const { return (size_ == 0); }
    size_type size() const { return size_; }

    reference operator[](size_type position) {
        if (position >= size_) {
            throw(std::out_of_range("Out of range in []"));
        }
        return buffer_[position];
    }

    void push_back(const value_type &value) {
        if (size_ == capacity_) {
            size_type new_capacity = (capacity_ > 0) ? 2 * capacity_ : 1;
            add_space(new_capacity);
        }
        buffer_[size_] = value;
        size_++;
    }
    void push_back(const value_type &&value) {
        if (size_ == capacity_) {
            size_type new_capacity = (capacity_ > 0) ? 2 * capacity_ : 1;
            add_space(new_capacity);
        }
        buffer_[size_] = std::move(value);
        size_++;
    }

    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("Out of range in pop_back()");
        }
        (buffer_[size_ - 1]).~value_type();
        size_--;  // something else?
        // size 1?
    }

    iterator begin() {
        Iterator<T> iter(this->buffer_);
        return iter;
    }

    const_iterator begin() const { return const_iterator(buffer_); }

    iterator end() { return iterator(buffer_ + size_); }
    const_iterator end() const { return const_iterator(buffer_ + size_); }

    reverse_iterator rbegin() { return reverse_iterator(buffer_ + size_ - 1); }
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(buffer_ + size_ - 1);
    }

    reverse_iterator rend() { return reverse_iterator(buffer_ - 1); }
    const_reverse_iterator rend() const {
        return const_reverse_iterator(buffer_ - 1);
    }

    void resize(size_type new_size) {
        if (new_size > capacity_) {
            add_space(new_size);
        }
        // add elements until new_size is reached (value-initialized when no
        // default value is provided)
        for (size_t i = size_; i < new_size; i++) buffer_[i] = value_type();
        // delete excess values
        for (size_t i = new_size; i < capacity_; i++)
            (buffer_[i]).~value_type();

        size_ = new_size;
    }

    void resize(size_type new_size, const value_type &default_value) {
        if (new_size > capacity_) {
            add_space(new_size);
        }
        // add elements until new_size is reached
        for (size_t i = size_; i < new_size; i++) buffer_[i] = default_value;
        // delete excess values
        for (size_t i = new_size; i < capacity_; i++)
            (buffer_[i]).~value_type();

        size_ = new_size;
    }

    void add_space(size_type new_capacity) {
        pointer resized_buffer = new T[new_capacity];

        for (size_t i = 0; i < size_; i++)
            resized_buffer[i] = std::move(buffer_[i]);
        delete[] buffer_;
        buffer_ = resized_buffer;
        capacity_ = new_capacity;
    }

    void clear() {
        for (size_t i = 0; i < size_; i++) (buffer_[i]).~value_type();
        size_ = 0;
    }

    friend std::ostream &operator<<(std::ostream &out,
                                    const Vector<T> &vector) {
        out << "Size: " << vector.size() << ' ';
        if (!vector.empty()) {
            out << "Content: ";
            for (auto it = vector.begin(); it != vector.end(); ++it) {
                out << *it << ' ';
            }
        }
        return out;
    }

   private:
    size_type size_;
    size_type capacity_;
    pointer buffer_;
};
