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


    class iterator : public std::iterator<std::random_access_iterator_tag, T>
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

    class const_iterator : public std::iterator<std::random_access_iterator_tag, T>
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

    class reverse_iterator : public std::iterator<std::random_access_iterator_tag, T>
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

    class const_reverse_iterator : public std::iterator<std::random_access_iterator_tag, T>
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



    MyVector() : _capacity(0),  _size(0)
    {}

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
        return iterator(_data.get());
    }
    const_iterator begin() const noexcept
    {
        return const_iterator(_data.get());
    }

    iterator end() noexcept
    {
        return iterator(_data.get() + _size);
    }

    const_iterator end() const noexcept
    {
        return const_iterator(_data.get() + _size);
    }




    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(_data.get() + _size-1);
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(_data.get() + _size-1);
    }

    reverse_iterator rend() noexcept
    {
        return reverse_iterator(_data.get()-1);
    }
    const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(_data.get()-1);
    }


    void push_back(value_type&& value)
    {
        if(_capacity == 0)
        {
            reserve(1);
        }

        if(_size == _capacity)
        {
            reserve(2*_capacity);
        }

        _data.get()[_size] = value;
        _size++;
    }


    void push_back(const value_type& value)
    {

        if(_capacity == 0)
        {
            reserve(1);
        }

        if(_size == _capacity)
        {
            reserve(2*_capacity);
        }

        _data.get()[_size] = value;
        _size++;
    }

    void pop_back()
    {
        if(_size == 0)
        {
            return;
        }

        _size--;
    }

    bool empty()
    {
        return _size == 0;
    }

    size_type size()
    {
        return _size;
    }

    void clear() noexcept
    {

        _data.release();

        _capacity = 0;
        _size = 0;

    }

    void reserve(size_type count)
    {
        if(_capacity == 0)
        {
            _data = std::unique_ptr<T[]>( new T[count]);
            _capacity = count;
            return;
        }

        if(count > _capacity)
        {
            T* new_ptr_data = (T *) realloc(_data.get(), count * sizeof(T));

            if (!new_ptr_data) {
                throw std::runtime_error("error in reserve:reallocation");
            }

            _data.release();
            _data.reset(new_ptr_data);
        }
    }

    size_type capacity() const noexcept
    {
        return _capacity;
    }

    void resize(size_type newSize)
    {
        if(newSize == 0)
        {
            clear();
            return;
        }

        if(newSize > _capacity) {
            reserve(newSize);
        }
        else
        {
            T* new_ptr_data = (T *) realloc(_data.get(), newSize * sizeof(T));

            if (!new_ptr_data) {
                throw std::runtime_error("error in resize:reallocation");
            }

            _data.release();
            _data.reset(new_ptr_data);
        }

        _size = newSize;
        _capacity = newSize;
    }


    void resize(size_type newSize, const value_type& defaultValue)
    {

        if(newSize == 0)
        {
            clear();
            return;
        }

        if(newSize > _capacity) {
            size_type prev_capacity = _capacity;
            reserve(newSize);


            T* data_ptr = _data.get();
            std::fill(data_ptr + prev_capacity, data_ptr + newSize, defaultValue);
        }
        else
        {

            T* new_ptr_data = (T *) realloc(_data.get(), newSize * sizeof(T));


            if (!new_ptr_data) {
                throw std::runtime_error("error in resize:reallocation");
            }

            _data.release();
            _data.reset(new_ptr_data);
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

    virtual ~MyVector()
    {}


private:

    std::unique_ptr<T[]> _data;
    size_type _size;
    size_type _capacity;


};




#endif //HW8_MYVECTOR_H
