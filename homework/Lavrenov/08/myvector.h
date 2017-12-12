#ifndef MYVECTOR
#define MYVECTOR
#include <memory>
#include <stdexcept>
#include "myiterator.h"
#include <string>
#include "myreverseiterator.h"

template <class T,
          class Alloc = std::allocator<T>,
          class Iterator = MyIterator<T> >
class MyVector{
public:
    //using iterator = Iterator;
    using allocator = Alloc;

    MyVector();
    MyVector(size_t length);
    ~MyVector();
    T& operator[](size_t);
    const T& operator[](size_t) const;
    void push_back(T);
    void pop_back();
    bool empty() const;
    size_t size();
    void clear();
    Iterator& begin();
    Iterator end();
    Iterator& rbegin();
    Iterator& rend();
    void resize(size_t);
private:
    size_t capacity;
    size_t _size;
    MyIterator<T> iter;
};

template <class T,
          class Alloc,
          class Iterator>
MyVector<T, Alloc, Iterator>::MyVector():
    capacity(2), _size(0)
{
    allocator a;
    //T* ptr = a.allocate(length);
    iter = Iterator(a.allocate(2));
    //a.construct(iter.getptr());
}

template <class T,
          class Alloc,
          class Iterator>
MyVector<T, Alloc, Iterator>::MyVector(size_t length):
    capacity(length + 1), _size(length)
{
    allocator a;
    //T* ptr = a.allocate(length);
    iter = Iterator(a.allocate(length));
    for(size_t i = 0; i < _size; ++i){
        a.construct(iter[i].getptr());
    }
}

template <class T,
          class Alloc,
          class Iterator>
MyVector<T, Alloc, Iterator>::~MyVector()
{
    //TODO
    allocator a;
    //T* ptr = a.allocate(length);
    for(size_t i = 0; i < _size; ++i){
        a.destroy(iter[i].getptr());
    }
    a.deallocate(iter.getptr(), capacity);

}

template <class T,
          class Alloc,
          class Iterator>
T& MyVector<T, Alloc, Iterator>::operator[](size_t i)
{
    //TODO
    if(i >= _size){
        std::string s = "index ";
        s += i + " out of range " + _size;
        throw std::out_of_range(s);
    }
    return *(iter[i]);
}

template <class T,
          class Alloc,
          class Iterator>
const T& MyVector<T, Alloc, Iterator>::operator[](size_t i) const
{
    //TODO
    if(i >= _size){
        std::string s = "index ";
        s += i + " out of range " + _size;
        throw std::out_of_range(s);
    }
    return *(iter[i]);
}

template <class T,
          class Alloc,
          class Iterator>
void MyVector<T, Alloc, Iterator>::push_back(T obj)
{
    //TODO
    if(_size >= capacity - 1){
        allocator a;
        Iterator newiter(a.allocate(capacity * 2));
        for(size_t i = 0; i < _size; ++i){
            *(newiter[i]) = std::move(*(iter[i]));
        }
        a.deallocate(iter.getptr(), capacity);
        iter = newiter;
        capacity *= 2;
    }
    *(iter[_size]) = obj;
    ++_size;
}

template <class T,
          class Alloc,
          class Iterator>
void MyVector<T, Alloc, Iterator>::pop_back()
{
    //TODO
    if(_size == 0){
        throw std::out_of_range("removing from empty vector");
    }
    allocator a;
    a.destroy(iter[_size - 1].getptr());
    --_size;
}

template <class T,
          class Alloc,
          class Iterator>
bool MyVector<T, Alloc, Iterator>::empty() const
{
    //TODO
    return _size == 0;
}

template <class T,
          class Alloc,
          class Iterator>
size_t MyVector<T, Alloc, Iterator>::size()
{
    //TODO

    return _size;
}

template <class T,
          class Alloc,
          class Iterator>
void MyVector<T, Alloc, Iterator>::clear()
{
    //TODO
    allocator a;
    //T* ptr = a.allocate(length);
    for(size_t i = 0; i < _size; ++i){
        a.destroy(iter[i].getptr());
    }
    _size = 0;
}

template <class T,
          class Alloc,
          class Iterator>
Iterator& MyVector<T, Alloc, Iterator>::begin()
{
    //TODO
    return iter;
}

template <class T,
          class Alloc,
          class Iterator>
Iterator MyVector<T, Alloc, Iterator>::end()
{
    //TODO
    if(_size == 0)
        return iter;
    return iter[_size];
}

template <class T,
          class Alloc,
          class Iterator>
Iterator& MyVector<T, Alloc, Iterator>::rbegin()
{
    //TODO
    if(_size == 0)
        return MyReverseIterator<T>(iter.getptr());;
    return MyReverseIterator<T>(iter[_size - 1].getptr());
}

template <class T,
          class Alloc,
          class Iterator>
Iterator &MyVector<T, Alloc, Iterator>::rend()
{
    //TODO
   return MyReverseIterator<T>(iter[0].getptr());;
}

template <class T,
          class Alloc,
          class Iterator>
void MyVector<T, Alloc, Iterator>::resize(size_t n)
{
    allocator a;
    if(n > capacity){
        Iterator newiter(a.allocate(n + capacity));
        for(size_t i = 0; i < _size; ++i){
            *(newiter[i]) = std::move(*(iter[i]));
        }
        a.deallocate(iter.getptr(), capacity);
        iter = newiter;
        capacity += n;
    }
    if(_size < n){
        for(size_t i = _size; i < n; ++i){
            a.construct(iter[i].getptr());
        }
    }else{
        for(size_t i = n; i < _size; ++i){
            a.destroy(iter[i].getptr());
        }
    }
    _size = n;
    //TODO

}
#endif // MYVECTOR

