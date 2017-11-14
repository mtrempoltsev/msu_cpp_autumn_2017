//
// Created by peter on 14.11.17.
//

#ifndef HW8_MYVECTOR_H
#define HW8_MYVECTOR_H


#include <memory>

template<class T, class Alloc = std::allocator<T>>
class MyVector {

public:

    using size_type = size_t;
    using value_type = T;


    class iterator
    {
    public:
        using self_type = iterator;

        explicit iterator(T* ptr) : _ptr(ptr)
        { }

        self_type operator++()
        {
            _ptr++;
            return *this;
        }
        self_type operator++(int junk)
        {
            _ptr++;
            return *this;
        }

        T& operator*()
        {
            return *_ptr;
        }
        T* operator->() { return _ptr; }
        bool operator==(const self_type& rhs) { return _ptr == rhs._ptr; }
        bool operator!=(const self_type& rhs) { return _ptr != rhs._ptr; }

    private:
        T* _ptr;
    };

    class const_iterator
    {
    public:
        using self_type = const_iterator;
        explicit const_iterator(T* ptr) : _ptr(ptr)
                { }

        self_type operator++()
        {
            _ptr++;
            return *this;
        }
        self_type operator++(int junk)
        {
            _ptr++;
            return *this;
        }

        const T& operator*()
        {
            return *_ptr;
        }
        const T* operator->() { return _ptr; }
        bool operator==(const self_type& rhs) { return _ptr == rhs._ptr; }
        bool operator!=(const self_type& rhs) { return _ptr != rhs._ptr; }

    private:
        T* _ptr;
    };

    class reverse_iterator
    {
    public:
        using self_type = reverse_iterator;
        explicit reverse_iterator(T* ptr) : _ptr(ptr)
        { }


        self_type operator++()
        {
            _ptr--;
            return *this;
        }
        self_type operator++(int junk)
        {
            _ptr--;
            return *this;
        }

        T& operator*()
        {
            return *_ptr;
        }
        T* operator->() { return _ptr; }
        bool operator==(const self_type& rhs) { return _ptr == rhs._ptr; }
        bool operator!=(const self_type& rhs) { return _ptr != rhs._ptr; }

    private:
        T* _ptr;
    };

    class const_reverse_iterator
    {
    public:
        using self_type = const_reverse_iterator;
        explicit const_reverse_iterator(T* ptr) : _ptr(ptr)
        { }


        self_type operator++()
        {
            _ptr--;
            return *this;
        }
        self_type operator++(int junk)
        {
            _ptr--;
            return *this;
        }

        const T& operator*()
        {
            return *_ptr;
        }
        const T* operator->() { return _ptr; }
        bool operator==(const self_type& rhs) { return _ptr == rhs._ptr; }
        bool operator!=(const self_type& rhs) { return _ptr != rhs._ptr; }

    private:
        T* _ptr;
    };



    MyVector()
    {
        _capacity = 0;
        _size = 0;
    }

    explicit MyVector(size_type count)
    {
        _capacity = 0;
        _size = 0;
        resize(count);
    }

    MyVector(size_type count, const value_type& defaultValue)
    {
        _capacity = 0;
        _size = 0;
        resize(count, defaultValue);
    }

    iterator begin() noexcept
    {
        return iterator(_data);
    }
    const_iterator begin() const noexcept
    {
        return const_iterator(_data);
    }

    iterator end() noexcept
    {
        return iterator(_data + _size);
    }

    const_iterator end() const noexcept
    {
        return const_iterator(_data + _size);
    }




    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(_data + _size-1);
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(_data + _size-1);
    }

    reverse_iterator rend() noexcept
    {
        return reverse_iterator(_data-1);
    }
    const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(_data-1);
    }


    void push_back(value_type&& value)
    {
        if(_capacity == 0)
        {
            _data = new T[1];
            _capacity = 1;
        }

        if(_size == _capacity)
        {
            reserve(2*_capacity);
        }

        _data[_size] = value;
        _size++;
    }


    void push_back(const value_type& value)
    {

        if(_capacity == 0)
        {
            _data = new T[1];
            _capacity = 1;
        }

        if(_size == _capacity)
        {
            reserve(2*_capacity);
        }

        _data[_size] = value;
        _size++;
    }

    void pop_back()
    {
        _size--;
    }

    bool empty()
    {
        return _size == 0;
    }

    size_type size()
    {
        return (size_t)_size;
    }

    void clear() noexcept
    {
        _capacity = 0;
        _size = 0;

        delete _data;
    }

    void reserve(size_type count)
    {
        if(_capacity == 0)
        {
            _data = new T[count];
            _capacity = count;
            return;
        }

        if(count > _capacity)
        {
            _data = (T *) realloc(_data, count * sizeof(T));
            _capacity = count;
        }
    }

    size_type capacity() const noexcept
    {
        return _capacity;
    }

    void resize(size_type newSize)
    {
        if(newSize > _capacity) {
            reserve(newSize);
        }
        else
        {
            _data = (T *) realloc(_data, newSize * sizeof(T));
            _capacity = newSize;
        }

        _size = newSize;
        _capacity = newSize;
    }


    void resize(size_type newSize, const value_type& defaultValue)
    {
        if(newSize > _capacity) {
            size_type prev_capacity = _capacity;
            reserve(newSize);
            std::fill(_data + prev_capacity, _data + newSize, defaultValue);
        }
        else
        {
            _data = (T *) realloc(_data, newSize * sizeof(T));
            _capacity = newSize;
        }

        _size = newSize;
        _capacity = newSize;
    }


    T& operator[](size_type i)  const
    {
        if(i >= _size)
            throw std::invalid_argument("index out of bounds");

        return _data[i];
    }

    ~MyVector()
    {
        delete[] _data;
    }


private:

    T* _data;
    size_type _size;
    size_type _capacity;


};




#endif //HW8_MYVECTOR_H
