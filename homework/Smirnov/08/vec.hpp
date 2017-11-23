#include <iostream>
#include <memory>
////////////////////////////////
//      Reverse_Iterator
//////////////////////////////
template<typename T>
class Reverse_Iterator 
    : public std::iterator<std::forward_iterator_tag, T>
{
public:
    Reverse_Iterator(T* pointer);
    bool operator!=(const Reverse_Iterator & other) const;
    bool operator==(const Reverse_Iterator & other) const;
    T& operator*() const;
    Reverse_Iterator operator++();

private:
    T* p;
};

template<typename T>
Reverse_Iterator<T>::Reverse_Iterator(T* pointer)
{
    p = pointer;
}

template<typename T>
bool Reverse_Iterator<T>::operator==(const Reverse_Iterator& other) const
{
    return p == other.p;
}

template<typename T>
bool Reverse_Iterator<T>::operator!=(const Reverse_Iterator& other) const
{
    return p != other.p;
}

template<typename T>
T& Reverse_Iterator<T>::operator*() const
{
    return *p;
}

template<typename T>
Reverse_Iterator<T> Reverse_Iterator<T>::operator++() 
{
    --p;
    return *this;
}

////////////////////////////////
//          Iterator
//////////////////////////////
template<typename T>
class Iterator 
    : public std::iterator<std::forward_iterator_tag, T>
{
public:
    Iterator(T* pointer);
    bool operator!=(const Iterator& other) const;
    bool operator==(const Iterator& other) const;

    T& operator*() const;
    Iterator operator++();

private:
    T* p;
};

template<typename T>
Iterator<T>::Iterator(T* pointer) 
{
    p = pointer;
}

template<typename T>
bool Iterator<T>::operator==(const Iterator& other) const
{
    return p == other.p;
}

template<typename T>
bool Iterator<T>::operator!=(const Iterator& other) const
{
    return p != other.p;
}

template<typename T>
T& Iterator<T>::operator*() const
{
    return *p;
}

template<typename T>
Iterator<T> Iterator<T>::operator++()
{
    ++p;
    return *this;
}
////////////////////////////////
//          Vector
//////////////////////////////
template<typename T>
class Vector
{   
public:
    using iterator = Iterator<T>;
    using const_iterator = const Iterator<T>;
    using reverse_iterator = Reverse_Iterator<T>;

    Vector(size_t size = 0):
        size_(size),
        capacity_(size_),
        data_(new T[capacity_])
    {       
    }

    Vector(std::initializer_list<T> values) :
        size_(values.size()),
        capacity_(size_),
        data_(new T[capacity_])
    {
        std::copy(values.begin(), values.end(), data_.get());
    }

    void push_back(T&& value);
    void pop_back();
    bool empty();
    size_t size();
    void clear();

    iterator begin();
    iterator end();
    reverse_iterator rbegin();
    reverse_iterator rend();
    void resize (size_t n, T val = T());
    T& operator[](size_t idx);

private:
    size_t size_;
    size_t capacity_;
    std::unique_ptr<T[]> data_;
};

template< typename T>
T& Vector<T>::operator[](size_t idx)
{
    return data_[idx];
}

template<typename T>
void Vector<T>::resize (size_t n, T val)
{
    if (n < size_)
    {
        size_ = n;
    }
    else if (n > size_)
    {   

        capacity_ = n;
        std::unique_ptr<T[]> data(new T[capacity_]);
        for (int i = 0; i < size_ - 1; ++i)
        {
            data[i] = data_[i];
        }
        for (int i = size_; i < n; ++i)
        {
            data[i] = val;
        }
        data_ = std::move(data);
        size_ = n;
    }
}

template<typename T>
typename Vector<T>::iterator Vector<T>::begin()
{
    return iterator(data_.get());
}

template<typename T>
typename Vector<T>::iterator Vector<T>::end()
{
    return iterator(data_.get() + size_);
}

template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::rbegin()
{
    return reverse_iterator(data_.get() + size_ - 1);
}

template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::rend()
{
    return reverse_iterator(data_.get() - 1);
}

template<typename T>
bool Vector<T>::empty()
{
    return size_ == 0;
}

template<typename T>
size_t Vector<T>::size()
{
    return size_;
}

template<typename T>
void Vector<T>::clear()
{
    size_ = 0;
    capacity_ = 0;
    data_.reset(nullptr);
}

template<typename T>
void Vector<T>::push_back(T&& value)
{   
    size_ += 1;
    if (size_ < capacity_)
    {
        data_[size_ - 1] = value;
    }
    else{
        capacity_ = capacity_ + 40;
        std::unique_ptr<T[]> data(new T[capacity_]);
        for (int i = 0; i < size_ - 1; i++)
        {
            data[i] = data_[i];
        }
        data_ = std::move(data);
        data_[size_ - 1] = value;
    }
}

template<typename T>
void Vector<T>::pop_back()
{
    size_ -= 1;
}



