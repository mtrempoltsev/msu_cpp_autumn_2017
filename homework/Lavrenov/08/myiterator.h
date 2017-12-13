#ifndef MYITERATOR
#define MYITERATOR

#include <iterator>

template <class T>
class MyIterator : public std::iterator<std::random_access_iterator_tag, T>{
public:
    using value_type = typename std::iterator<std::random_access_iterator_tag, T>::value_type;
    using difference_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
    MyIterator();
    MyIterator(value_type*);
    MyIterator(const MyIterator&);
    ~MyIterator();
    bool operator==(const MyIterator& rhs) const;
    bool operator!=(const MyIterator& rhs) const;
    bool operator>(const MyIterator& rhs) const;
    bool operator<(const MyIterator& rhs) const;
    bool operator>=(const MyIterator& rhs) const;
    bool operator<=(const MyIterator& rhs) const;
    MyIterator& operator++();
    MyIterator operator++(int);
    MyIterator& operator--();
    MyIterator operator--(int);
    MyIterator operator[](size_t);
    const MyIterator operator[](size_t) const;
    MyIterator& operator+=(difference_type);
    MyIterator& operator-=(difference_type);
    MyIterator operator+(difference_type) const;
    MyIterator operator-(const MyIterator&) const;
    template <class A>
    friend MyIterator<A> operator+(typename MyIterator<A>::difference_type, const MyIterator<A>&);
    MyIterator& operator=(MyIterator&&);
    MyIterator& operator=(const MyIterator&);
    value_type* getptr();
    T& operator*() const;
private:
    value_type* value;
};

template <class T>
MyIterator<T>::MyIterator()
    :value(nullptr)
{
}

template <class T>
MyIterator<T>::MyIterator(value_type* v)
    :value(v)
{
}

template <class T>
MyIterator<T>::MyIterator(const MyIterator<T>& it){
    this->value = it.value;
}

template <class T>
MyIterator<T>::~MyIterator()
{
}


template <class T>
bool MyIterator<T>::operator==(const MyIterator<T>& rhs) const{
    return rhs.value == this->value;
}

template <class T>
bool MyIterator<T>::operator!=(const MyIterator<T>& rhs) const{
    return !(*this == rhs);
}

template <class T>
bool MyIterator<T>::operator>(const MyIterator<T>& rhs) const{
    return rhs.value > this->value;
}

template <class T>
bool MyIterator<T>::operator<(const MyIterator<T>& rhs) const{
    return rhs.value > this->value;
}

template <class T>
bool MyIterator<T>::operator>=(const MyIterator<T>& rhs) const{
    return rhs.value >= this->value;
}

template <class T>
bool MyIterator<T>::operator<=(const MyIterator<T>& rhs) const{
    return rhs.value <= this->value;
}

template <class T>
MyIterator<T>& MyIterator<T>::operator++(){

    ++value;
    return *this;
}

template <class T>
MyIterator<T> MyIterator<T>::operator++(int i){

    MyIterator<T> tmp(*this);
    ++value;
    return tmp;
}

template <class T>
MyIterator<T>& MyIterator<T>::operator--(){
    --value;
    return *this;
}

template <class T>
MyIterator<T> MyIterator<T>::operator--(int i){
    MyIterator<T> tmp(*this);
    --value;
    return tmp;
}

template <class T>
MyIterator<T> MyIterator<T>::operator[](size_t i){
    MyIterator<T> tmp(*this);
    tmp.value += i;
    return tmp;
}

template <class T>
const MyIterator<T> MyIterator<T>::operator[](size_t i) const{
    MyIterator<T> tmp(*this);
    tmp.value += i;
    return tmp;
}

template <class T>
MyIterator<T>& MyIterator<T>::operator+=(difference_type i){
    value += i;
    return *this;
}

template <class T>
MyIterator<T>& MyIterator<T>::operator-=(difference_type i){
    value -= i;
    return *this;
}

template <class T>
MyIterator<T> MyIterator<T>::operator+(difference_type i) const{
    MyIterator<T> tmp(*this);
    tmp.value += i;
    return tmp;
}

template <class T>
MyIterator<T> MyIterator<T>::operator-(const MyIterator<T>& i) const{
    MyIterator tmp(*this);
    tmp.value -= i.value;
    return tmp;
}

template <class T>
MyIterator<T> operator+(typename MyIterator<T>::difference_type left, const MyIterator<T>& right){
    MyIterator<T> tmp(right);
    tmp.value += left;
    return tmp;
}

template <class T>
MyIterator<T>& MyIterator<T>::operator=(MyIterator<T>&& that) {
    value = that.value;
    that.value = nullptr;
    return *this;
}

template <class T>
MyIterator<T>& MyIterator<T>::operator=(const MyIterator<T>& that) {
    value = that.value;
    return *this;
}

template <class T>
typename MyIterator<T>::value_type* MyIterator<T>::getptr()
{
    return value;
}

template <class T>
T& MyIterator<T>::operator*() const
{
    return *value;
}
#endif // MYITERATOR

