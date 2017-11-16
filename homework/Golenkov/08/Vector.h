#ifndef VECTOR_H
#define VECTOR_H

#include <memory>

template <class T>
class Iterator: public std::iterator<std::forward_iterator_tag, T>
{
public:
    explicit Iterator(T* ptr): ptr_(ptr) {}

    T& operator*() const
    {
        return *ptr_;
    }

    bool operator==(const Iterator& other) const
    {
        return other.ptr_ == ptr_;
    }

    bool operator!=(const Iterator& other) const
    {
        return !(*this == other);
    }

    Iterator& operator+(size_t n)
    {
        ptr_ += n;
        return *this;
    }

    Iterator& operator-(size_t n)
    {
        ptr_ -= n;
        return *this;
    }

    Iterator& operator++()
    {
        ptr_++;
        return *this;
    }

    Iterator operator++(int notUsed)
    {
        Iterator tmp(ptr_);
        ptr_++;
        return tmp;
    }

    Iterator& operator--()
    {
        ptr_--;
        return *this;
    }

    Iterator operator--(int notUsed)
    {
        Iterator tmp(ptr_);
        ptr_--;
        return tmp;
    }

private:
    T* ptr_;
};

template <class T>
class ReverseIterator: public std::reverse_iterator <std::iterator<std::forward_iterator_tag, T> >
{
public:
    explicit ReverseIterator(T* ptr): ptr_(ptr) {}

    T& operator*() const
    {
        return *ptr_;
    }

    bool operator==(const ReverseIterator& other) const
    {
        return other.ptr_ == ptr_;
    }

    bool operator!=(const ReverseIterator& other) const
    {
        return !(*this == other);
    }

    ReverseIterator& operator+(size_t n)
    {
        ptr_ -= n;
        return *this;
    }

    ReverseIterator& operator-(size_t n)
    {
        ptr_ += n;
        return *this;
    }

    ReverseIterator& operator++()
    {
        ptr_--;
        return *this;
    }

    ReverseIterator operator++(int notUsed)
    {
        ReverseIterator tmp(ptr_);
        ptr_--;
        return tmp;
    }

    ReverseIterator& operator--()
    {
        ptr_++;
        return *this;
    }

    ReverseIterator operator--(int notUsed)
    {
        ReverseIterator tmp(ptr_);
        ptr_++;
        return tmp;
    }

private:
    T* ptr_;
};

template < class T, class Alloc = std::allocator<T> >
class Vector
{
public:
    using iterator = Iterator<T>;
    using const_iterator = Iterator<const T>;
    using reverse_iterator = ReverseIterator<T>;
    using const_reverse_iterator = ReverseIterator<const T>;

    explicit Vector(size_t size = 0): size_(size), capacity_(size)
    {
        data_ = std::make_unique<T[]>(size_); // nullptr
    }

    Vector(size_t size, const T& value): size_(size), capacity_(size)
    {
        data_ = std::make_unique<T[]>(size_);
        for (size_t i = 0; i < size_; i++)
        {
            data_[i] = T(value);
        }
    }

    Vector(const Vector& other): size_(other.size_), capacity_(other.capacity_)
    {
        data_ = std::make_unique<T[]>(size_);
        std::copy(other.data_.get(), other.data_.get() + size_, data_.get());
    }

    explicit Vector(Vector&& other): size_(other.size_), capacity_(other.capacity_)
    {
        data_ = std::move(other.data_);
    }

    Vector& operator=(const Vector& other)
    {
        size_ = (other.size_);
        capacity_ = (other.capacity_);
        data_ = std::make_unique<T[]>(size_);
        std::copy(other.data_.get(), other.data_.get() + size_, data_.get());
        return *this;
    }

    Vector& operator=(Vector&& movied)
    {
        size_ = (movied.size_);
        capacity_ = (movied.capacity_);
        data_ = std::move(movied.data_);
        return *this;
    }

    size_t size() const noexcept
    {
        return size_;
    }

    iterator begin() noexcept
    {
        return iterator(data_.get());
    }

    const_iterator begin() const noexcept
    {
        return const_iterator(data_.get());
    }

    iterator end() noexcept
    {
        return iterator(data_.get() + size_);
    }

    const_iterator end() const noexcept
    {
        return const_iterator(data_.get() + size_);
    }

    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(data_.get() + size_ - 1);
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(data_.get() + size_ - 1);
    }

    reverse_iterator rend() noexcept
    {
        return reverse_iterator(data_.get() - 1);
    }

    const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(data_.get() - 1);
    }

    T& operator[](size_t i)
    {
        if (i >= size_)
        {
            throw "Index is out of range";
        }
        return data_[i];
    }

    void resize(size_t new_size)
    {
        if (new_size < size_)
        {
            for (auto it = this->begin() + new_size; it < this->end(); it++)
            {
                (*it).~T();
            }
            size_ = new_size;
        }
        else if (capacity_ < new_size)
        {
            auto tmp = std::make_unique<T[]>(new_size);
            std::copy(data_.get(), data_.get() + size_, tmp.get());
            data_ = std::move(tmp);

            size_ = new_size;
            capacity_ = new_size;
        }
        else if (capacity_ >= new_size)
        {
            for (auto it = this->begin() + size_; it < this->begin() + new_size; it++)
            {
                *it = T();
            }
            size_ = new_size;
        }
    }

    void resize(size_t new_size, const T& default_value)
    {
        size_t old_size = size_;
        this->resize(new_size);

        if (new_size > old_size)
        {
            for (auto it = this->begin() + old_size; it < this->end(); it++)
            {
                *it = T(default_value);
            }
        }
    }

    void push_back(const T& value)
    {
        if (size_ == capacity_)
        {
            capacity_ *= 2;
            if (capacity_ == 0)
            {
                capacity_ = 1;
            }
            auto tmp = std::make_unique<T[]>(capacity_);
            std::copy(data_.get(), data_.get() + size_, tmp.get());
            data_ = std::move(tmp);
        }
        data_[size_++] = value;
    }

    void pop_back()
    {
        if (size_ == 0)
        {
            throw "Pop of empty array";
        }

        (*this->rbegin()).~T();
        size_--;
    }

    bool empty() const
    {
        return size_ == 0;
    }

    void clear() noexcept
    {
        for (auto it = this->begin(); it < this->end(); it++)
        {
            (*it).~T();
        }
        size_ = 0;
    }

    bool operator==(const Vector<T>& vect) const
    {
        if (size_ != vect.size())
        {
            return false;
        }

        for (size_t k = 0; k < size_; k++)
        {
            if (data_[k] != vect[k])
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Vector<T>& vect) const
    {
         return !(*this == vect);
    }

    ~Vector() {}

private:
    size_t size_;
    size_t capacity_;
    std::unique_ptr<T[]> data_;
};

#endif
