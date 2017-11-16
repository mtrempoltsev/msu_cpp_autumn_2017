#include <iterator>

template<class T>
class TIterator : public std::iterator<std::random_access_iterator_tag, T>
{
protected:
    T* ptr_;
public:
    explicit TIterator(T* ptr) : ptr_(ptr) { }
    virtual TIterator operator++(int) { TIterator i = *this; ptr_++; return i; }
    virtual TIterator& operator++() { ptr_++; return *this; }
    virtual TIterator operator--(int) { TIterator i = *this; ptr_--; return i; }
    virtual TIterator& operator--() { ptr_--; return *this; }
    virtual TIterator operator+(int n) { return TIterator(ptr_ + n); }
    virtual TIterator operator-(int n) { return TIterator(ptr_ - n); }
    virtual TIterator& operator+=(int n) { ptr_ += n; return *this; }
    virtual TIterator& operator-=(int n) { ptr_ -= n; return *this; }    
    T& operator*() { return *ptr_; }
    T* operator->() { return ptr_; }
    bool operator==(const TIterator& rhs) { return ptr_ == rhs.ptr_; }
    bool operator!=(const TIterator& rhs) { return ptr_ != rhs.ptr_; }
};

template<class T>
class TReverseIterator : public TIterator<T>
{
public:
    explicit TReverseIterator(T* ptr) : TIterator<T>(ptr) { }
    TIterator<T> operator++(int) override { TReverseIterator i = *this; TIterator<T>::ptr_--; return i; }
    TIterator<T>& operator++() override { TIterator<T>::ptr_--; return *this; }
    TIterator<T> operator--(int) override { TReverseIterator i = *this; TIterator<T>::ptr_++; return i; }
    TIterator<T>& operator--() override { TIterator<T>::ptr_++; return *this; }
    TIterator<T> operator+(int n) override { return TReverseIterator(TIterator<T>::ptr_ - n); }
    TIterator<T> operator-(int n) override { return TReverseIterator(TIterator<T>::ptr_ + n); }
    TIterator<T>& operator+=(int n) override { TIterator<T>::ptr_ -= n; return *this; }
    TIterator<T>& operator-=(int n) override { TIterator<T>::ptr_ += n; return *this; }    
};
