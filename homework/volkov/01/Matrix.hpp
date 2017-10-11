#pragma once

template<typename T>
class Matrix
{
    T* data_;
    size_t size_;

    class Row
    {
        T* rowStart_;

    public:
        Row(T* start)
            : rowStart_(start)
        {
        }

        T& operator[](size_t n)
        {
            return *(rowStart_ + n);
        }

        const T& operator[](size_t n) const
        {
            return *(rowStart_ + n);
        }
    };

public:
    Matrix(size_t size)
        : data_(new T[size * size]())
        , size_(size)
    {
    }

    ~Matrix()
    {
        delete[] data_;
    }

    Row operator[](size_t n)
    {
        return Row(data_ + n * size_);
    }

    const Row operator[](size_t n) const
    {
        return Row(data_ + n * size_);
    }
};
