#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <memory>
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <math.h>

#include "iterator.h"

//using namespace std;
//template<typename T, typename... Args>
//std::unique_ptr<T> std::make_unique(Args&&... args) {
//    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
//}


bool almost_equal(double a, double b, double epsilon = 1e-7)
{
    double maximum = std::max(1., std::max(std::abs(a), std::abs(b)));
    if (std::abs(a - b) < epsilon * maximum)
        return true;
    return false;
}

/*
 *  Написать свой контейнер Vector аналогичный std::vector и итератор для него.
 * Из поддерживаемых методов достаточно
 * operator[], push_back, pop_back,
 * empty, size, clear, begin, end,
 * rbegin, rend, resize.
 * */

class VectorError : public std::runtime_error
{
public:
    VectorError() : std::runtime_error("")
    {}

    virtual ~VectorError() throw()
    {}

    virtual const char* what() const throw()
    {
        return mMsg.c_str();
    }

protected:
    std::string mMsg;
};

class IndexOutOfRange : public VectorError
{
public:
    IndexOutOfRange() : VectorError()
    {
        mMsg = "(operator[] error) index is out of range";
    }
    virtual ~IndexOutOfRange() throw()
    {}
};

class PopFromEmptyVector : public VectorError
{
public:
    PopFromEmptyVector() : VectorError()
    {
        mMsg = "(pop_back error) vector is empty";
    }
    virtual ~PopFromEmptyVector() throw()
    {}
};

// ======================================================================================
// ======================================================================================
// ======================================================================================


template <class T, class Alloc = std::allocator<T>>
class Vector
{
private:
    size_t size_;
    size_t capacity_;
    std::unique_ptr<T[]> data_;

public:
    using size_type = size_t;
    using value_type = T;

    using iterator = Iterator<T>;
    using riterator = RIterator<T>;

    using const_iterator = Iterator<const T>;
    using const_riterator = RIterator<const T>;


    // instantiation
    explicit Vector(size_type count = 0) : size_(count)
                                         , capacity_(count)
                                         , data_(nullptr)
    {
        if (size_ != 0)
        {
            data_ = std::make_unique<value_type[]>(size_);
        }

    }

    Vector(size_type count, const value_type& defaultValue) : Vector(count)
    {
        if (size_ != 0)
        {
            for (size_type i = 0; i < size_; i++)
            {
               data_[i] = defaultValue;
            }
        }
    }

    Vector(std::initializer_list<value_type> init) : Vector(init.size())
    {
        if (size_ != 0)
        {
            size_type i = 0;
            auto current = init.begin();
            const auto end = init.end();
            while (current != end)
            {
                data_[i++] = *current++;
            }
        }
    }

    // operator[]
    value_type& operator[](size_type i)
    {
        if (i >= size_)
        {
            throw IndexOutOfRange();
        }
        return data_[i];
    }

    const value_type& operator[](size_type i) const
    {
        if (i >= size_)
        {
            throw IndexOutOfRange();
        }
        return data_[i];
    }

    // push_back
    // void push_back(value_type&& value);
    void push_back(const value_type& value)
    {
        if (size_ == capacity_) // if limit reached
        {
            capacity_ = (capacity_ == 0) ? 1 : (capacity_ * 2);

            auto tmp = std::make_unique<T[]>(capacity_);
            std::copy(data_.get(), data_.get() + size_, tmp.get());
            data_ = std::move(tmp);
        }

        data_[size_++] = value;
    }

    // pop_back
    void pop_back()
    {
        if (size_ == 0)
        {
            throw PopFromEmptyVector();
        }

        (*this->rbegin()).~T();
        *this->rbegin() = T();
        size_--;
    }

    // empty
    bool empty() const
    {
        return (size_ == 0);
    }
    // size
    size_type size() const noexcept
    {
        return size_;
    }

    size_type capacity() const noexcept
    {
        return capacity_;
    }

    // clear
    void clear() noexcept
    {
        for (auto it = this->begin(); it < this->end(); ++it)
        {
            (*it).~T();
            *it = T();
        }
        size_ = 0;
    }

    // begin
    iterator begin() noexcept
    {
        return iterator(data_.get());
    }
    const_iterator begin() const noexcept
    {
        return const_iterator(data_.get());
    }

    // end
    iterator end() noexcept
    {
        return iterator(data_.get() + size_);
    }
    const_iterator end() const noexcept
    {
        return const_iterator(data_.get() + size_);
    }

    // rbegin
    riterator rbegin() noexcept
    {
        return riterator(data_.get() - 1);
    }
    const_riterator rbegin() const noexcept
    {
        return const_riterator(data_.get() - 1);
    }

    // rend
    riterator rend() noexcept
    {
        return riterator(data_.get() + size_ - 1);
    }
    const_riterator rend() const noexcept
    {
        return const_riterator(data_.get() + size_ - 1);
    }

    // resize
    void resize(size_type newsize)
    {
        if(newsize == 0)
        {
            clear();
            return;
        }

        if(newsize == size_)
        {
            return;
        }

        if(newsize < size_) // delete superfluous elements
        {
            for (auto it = this->begin() + newsize; it < this->end(); ++it)
            {
                (*it).~T();
            }
           size_ = newsize;
        }
        else if (capacity_ < newsize) // realloc data, replace elements
        {
            auto newData = std::make_unique<T[]>(newsize);

            std::copy(data_.get(), data_.get() + size_, newData.get());
            data_ = std::move(newData);

            size_ = newsize;
            capacity_ = newsize;
        }
        else // add new elements
        {
            for (auto it = this->begin() + size_; it < this->begin() + newsize; ++it)
            {
                (*it) = T();
            }
           size_ = newsize;
        }
    }

    void resize(size_type newsize, const value_type& defaultValue)
    {
        size_type oldsize = size_;
        this->resize(newsize);

        if (newsize > oldsize)
        {
            for (auto it = this->begin() + oldsize; it < this->end(); ++it)
            {
                *it = T(defaultValue);
            }
        }
    }

    bool operator==(const Vector<T>& other) const
    {
        if (this->size_ != other.size())
            return false;
        for (size_type i = 0; i < this->size_; ++i)
            if (!almost_equal((*this)[i], other[i]))
                return false;

        return true;
    }
};
template <typename T>
std::ostream& operator <<(std::ostream &os, const Vector<T> &vect){
    for (size_t i = 0; i < (size_t)vect.size(); ++i)
        os << vect[i] << ' ';
    os << endl;
    return os;
}


#endif // VECTOR_H
