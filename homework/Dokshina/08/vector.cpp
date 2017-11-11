#pragma once

#include <memory>
#include <initializer_list>
#include <exception>

#include "iterator.cpp"

template <class T, class Alloc = std::allocator<T>>
class Vector
{
public:
    typedef Iterator<T> iterator;
    typedef Iterator<const T> const_iterator;
    typedef ReverseIterator<T> reverse_iterator;
    typedef ReverseIterator<const T> const_reverse_iterator;


    explicit Vector(size_t size = 0)
                    : size_(size)
                    , capacity_(size) {
        if (size != 0) {
            data_ = std::make_unique<T[]>(size_);
        } else {
            data_ = nullptr;
        }
    }


    Vector(size_t size, const T& default_value)
                    : size_(size)
                    , capacity_(size) {
        data_ = std::make_unique<T[]>(size_);
        for (size_t i = 0; i < size_; i++) {
            data_[i] = default_value;
        }
    }


    Vector(std::initializer_list<T> store)
                    : size_(store.size())
                    , capacity_(store.size()) {
        if (store.size() != 0) {
            data_ = std::make_unique<T[]>(size_);
            std::copy(store.begin(), store.end(), data_.get());
        } else {
            data_ = nullptr;
        }

    }


    Vector(const Vector& other)
                    : size_(other.size_)
                    , capacity_(other.capacity_) {
        data_ = std::make_unique<T[]>(size_);
        std::copy(other.data_.get(), other.data_.get() + size_, data_.get());
    }


    explicit Vector(Vector&& other)
                    : size_(other.size_)
                    , capacity_(other.capacity_) {
        data_ = std::move(other.data_);
    }


    Vector& operator=(const Vector& other) {
        size_ = (other.size_);
        capacity_ = (other.capacity_);
        data_ = std::make_unique<T[]>(size_);
        std::copy(other.data_.get(), other.data_.get() + size_, data_.get());
        return *this;
    }


    Vector& operator=(Vector&& movied) {
        size_ = (movied.size_);
        capacity_ = (movied.capacity_);
        data_ = std::move(movied.data_);
        return *this;
    }


    size_t size() const noexcept {
        return size_;
    }


    size_t capacity() const noexcept {
        return capacity_;
    }


    iterator begin() noexcept {
        return iterator(data_.get());
    }


    const_iterator begin() const noexcept {
        return const_iterator(data_.get());
    }


    iterator end() noexcept {
        return iterator(data_.get() + size_);
    }


    const_iterator end() const noexcept {
        return const_iterator(data_.get() + size_);
    }


    reverse_iterator rbegin() noexcept {
        return reverse_iterator(data_.get() + size_ - 1);
    }


    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(data_.get() + size_ - 1);
    }


    reverse_iterator rend() noexcept {
        return reverse_iterator(data_.get() - 1);
    }


    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(data_.get() - 1);
    }


    T& operator[](size_t i) {
        if (i >= size_) {
            throw std::out_of_range("Index is out of range");
        }
        return data_[i];
    }


    void resize(size_t new_size) {
        if (new_size == size_) {
            return;
        }

        if (new_size < size_) {
            // capacity doesn't changes
            for (auto it = this->begin() + new_size; it != this->end(); it++) {
                (*it).~T();
            }
            size_ = new_size;
        } else if (capacity_ < new_size) {
            // capacity changes to new_size
            auto tmp = std::make_unique<T[]>(new_size);
            std::copy(data_.get(), data_.get() + size_, tmp.get());
            data_ = std::move(tmp);

            size_ = new_size;
            capacity_ = new_size;
        } else {
            // capacity doesn't changes
            for (auto it = this->begin() + size_; it != this->begin() + new_size; it++) {
                *it = T();
            }
            size_ = new_size;
        }
    }


    void resize(size_t new_size, const T& default_value) {
        size_t old_size = size_;
        this->resize(new_size);

        // fill by default value
        if (new_size > old_size) {
            for (auto it = this->begin() + old_size; it != this->end(); it++) {
                *it = default_value;
            }
        }

    }


    void push_back(const T& value) {
        if (size_ == capacity_) {
            // increase the size
            capacity_ *= 2;
            if (capacity_ == 0) {
                capacity_ = 1;
            }

            auto tmp = std::make_unique<T[]>(capacity_);
            std::copy(data_.get(), data_.get() + size_, tmp.get());
            data_ = std::move(tmp);
        }

        data_[size_++] = value;
    }


    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("Pop of empty array");
        }

        (*this->rbegin()).~T();
        size_--;
    }


    bool empty() const {
        return size_ == 0;
    }


    void clear() noexcept {
        for (auto it = this->begin(); it != this->end(); it++) {
            (*it).~T();
        }
        size_ = 0;
    }


    ~Vector() {}

private:
    size_t size_;
    size_t capacity_;
    std::unique_ptr<T[]> data_;
};

// some useful functions
template <typename T>
bool operator==(Vector<T> vect1, Vector<T> vect2) {
    if (vect1.size() != vect2.size()) {
        return false;
    }

    for (size_t k = 0; k < vect1.size(); k++) {
        if (vect1[k] != vect2[k]) {
            return false;
        }
    }

    return true;
}


template <typename T>
bool operator!=(Vector<T> vect1, Vector<T> vect2) {
    return !(vect1 == vect2);
}


template <typename T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& vect) {
    for (auto &it : vect) {
        out << it << ' ';
    }
    return out;
}
