#ifndef MYREVERSEITERATOR
#define MYREVERSEITERATOR

#include <iterator>

template <class T>
class MyReverseIterator : public std::iterator<std::forward_iterator_tag, T>{
public:
    using value_type = typename std::iterator<std::random_access_iterator_tag, T>::value_type;
    using difference_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
    MyReverseIterator();
    MyReverseIterator(value_type*);
    MyReverseIterator(const MyReverseIterator&);
    ~MyReverseIterator();
    bool operator==(const MyReverseIterator& rhs) const;
    bool operator!=(const MyReverseIterator& rhs) const;
    MyReverseIterator& operator++();
    MyReverseIterator operator++(int);
    MyReverseIterator& operator=(MyReverseIterator&&);
    T& operator*() const;
private:
    value_type* value;
};

template <class T>
MyReverseIterator<T>::MyReverseIterator()
    :value(nullptr)
{
}

template <class T>
MyReverseIterator<T>::MyReverseIterator(value_type* v)
    :value(v)
{
}

template <class T>
MyReverseIterator<T>::MyReverseIterator(const MyReverseIterator<T>& it){
    this->value = it.value;
}

template <class T>
MyReverseIterator<T>::~MyReverseIterator()
{
}


template <class T>
bool MyReverseIterator<T>::operator==(const MyReverseIterator<T>& rhs) const{
    return rhs.value == this->value;
}

template <class T>
bool MyReverseIterator<T>::operator!=(const MyReverseIterator<T>& rhs) const{
    return !(*this == rhs);
}

template <class T>
MyReverseIterator<T>& MyReverseIterator<T>::operator++(){

    --value;
    return *this;
}

template <class T>
MyReverseIterator<T> MyReverseIterator<T>::operator++(int i){

    MyReverseIterator<T> tmp(*this);
    --value;
    return tmp;
}

template <class T>
MyReverseIterator<T>& MyReverseIterator<T>::operator=(MyReverseIterator<T>&& that) {
    std::swap(value, that.value);
    return *this;
}

template <class T>
T& MyReverseIterator<T>::operator*() const
{
    return *value;
}
#endif // MYREVERSEITERATOR

