#pragma once

template<typename T>
class Matrix
{
    T* p;
    size_t size;

    class Row
    {
        T* q;

    public:
        Row(T* n)
            : q(n)
        {
        }

        T& operator[](size_t m)
        {
            return *(q + m);
        }

        const T& operator[](size_t m) const
        {
            return *(q + m);
        }
    };

public:
    Matrix(size_t size_)
        : p(new T[size_ * size_])
        , size(size_)
    {
        // no initialization of p
    }

    ~Matrix()
    {
        delete[] p;
    }

    Row operator[](T n)
    {
        return Row(p + n * size);
    }

    Row operator[](T n) const
    {
        return Row(p + n * size);
    }
};
