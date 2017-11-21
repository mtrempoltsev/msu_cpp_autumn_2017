
#include <string>
#include <iostream>
#include <memory>

using namespace std;

class Error
{
    string message;
public:
    Error(string&& message_)
    {
        message = message_;
    }
    const string getMessage() const
    {
        return message;
    }
};

void check(bool value, string s)
{
    if (!value)
        cout << "Error: " << s << endl;
}

template <class T>
class Iterator : public iterator<forward_iterator_tag, T>
{
    T* ptr_;
public:
    using reference = T&;
    
    explicit Iterator(T* ptr) : ptr_(ptr){}
    
    bool operator==(const Iterator<T>& other) const
    {
        return ptr_ == other.ptr_;
    }
    
    bool operator!=(const Iterator<T>& other) const
    {
        return !(*this == other);
    }
    
    reference operator*() const
    {
        return *ptr_;
    }
    
    Iterator& operator++()
    {
        ptr_++;
        return *this;
    }
    
    Iterator& operator++(int)
    {
        ++ptr_;
        return *this;
    }
};

template <class T>
class const_Iterator : public iterator<forward_iterator_tag, T>
{
    T* ptr_;
public:
    using reference = T&;
    
    explicit const_Iterator(T* ptr) : ptr_(ptr){}
    
    bool operator==(const const_Iterator<T>& other) const
    {
        return ptr_ == other.ptr_;
    }
    
    bool operator!=(const const_Iterator<T>& other) const
    {
        return !(*this == other);
    }
    
    const T& operator*() const
    {
        return *ptr_;
    }
    
    const_Iterator& operator++()
    {
        ++ptr_;
        return *this;
    }
    
    const_Iterator& operator++(int k)
    {
        ptr_++;
        return *this;
    }
};

template <class T>
class RIterator : public iterator<forward_iterator_tag, T>
{
    T* ptr_;
public:
    using reference = T&;
    
    explicit RIterator(T* ptr) : ptr_(ptr){}
    
    bool operator==(const RIterator<T>& other) const
    {
        return ptr_ == other.ptr_;
    }
    
    bool operator!=(const RIterator<T>& other) const
    {
        return !(*this == other);
    }
    
    reference operator*() const
    {
        return *ptr_;
    }
    
    RIterator& operator++()
    {
        --ptr_;
        return *this;
    }
    
    RIterator& operator++(int)
    {
        --ptr_;
        return *this;
    }
};

template <class T>
class const_RIterator : public iterator<forward_iterator_tag, T>
{
    T* ptr_;
public:
    using reference = T&;
    
    explicit const_RIterator(T* ptr) : ptr_(ptr){}
    
    bool operator==(const const_RIterator<T>& other) const
    {
        return ptr_ == other.ptr_;
    }
    
    bool operator!=(const const_RIterator<T>& other) const
    {
        return !(*this == other);
    }
    
    const T& operator*() const
    {
        return *ptr_;
    }
    
    const_RIterator& operator++()
    {
        --ptr_;
        return *this;
    }
    
    const_RIterator& operator++(int)
    {
        --ptr_;
        return *this;
    }
};

/*
 Написать свой контейнер Vector аналогичный std::vector и итератор для него. Из поддерживаемых методов достаточно operator[], push_back, pop_back, empty, size, clear, begin, end, rbegin, rend, resize.
 */
template<class T, class Alloc = std::allocator<T>>
class Vector
{
    unique_ptr<T[]> data;
public:
    using size_type = size_t;
    using value_type = T;
    size_type capacity;
    size_type size_;
    
    Vector(): capacity(0), size_(0), data(nullptr){}
    
    explicit Vector(size_type count)
    {
        capacity = 0;
        size_ = 0;
        resize(count);
    }
    
    Vector(size_type count, const value_type& defaultValue)
    {
        capacity = 0;
        size_ = 0;
        resize(count, defaultValue);
    }
    
    Iterator<T> begin() noexcept
    {
        return Iterator<T>(data.get());
    }
    const_Iterator<T> begin() const noexcept
    {
        return const_Iterator<T>(data);
    }
    
    Iterator<T> end() noexcept
    {
        return Iterator<T>(data.get() + size_);
    }
    const_Iterator<T> end() const noexcept
    {
        return const_Iterator<T>(data + size_);
    }
    
    RIterator<T> rbegin() noexcept
    {
        return RIterator<T>(data.get() + size_ - 1);
    }
    const_RIterator<T> rbegin() const noexcept
    {
        return const_RIterator<T>(data + size_ - 1);
    }
    
    RIterator<T> rend() noexcept
    {
        return RIterator<T>(data.get() - 1);
    }
    const_RIterator<T> rend() const noexcept
    {
        return const_RIterator<T>(data - 1);
    }
    
    void push_back(value_type&& value)
    {
        if(capacity == 0)
        {
            capacity = 1;
            auto tmp_data = unique_ptr<value_type[]>(new value_type[capacity]);
            memcpy(tmp_data.get(), data.get(), size_ * sizeof(value_type));
            data = move(tmp_data);
        }
        
        if(size_ == capacity)
        {
            capacity *= 2;
            auto tmp_data = unique_ptr<value_type[]>(new value_type[capacity]);
            memcpy(tmp_data.get(), data.get(), size_ * sizeof(value_type));
            data = move(tmp_data);
        }
            
        data[size_] = value;
        size_++;
    }
    
    void push_back(const value_type& value)
    {
        
        if(capacity == 0)
        {
            capacity = 1;
            auto tmp_data = unique_ptr<value_type[]>(new value_type[capacity]);
            memcpy(tmp_data.get(), data.get(), size_ * sizeof(value_type));
            data = move(tmp_data);
        }
        
        if(size_ == capacity)
        {
            capacity *= 2;
            auto tmp_data = unique_ptr<value_type[]>(new value_type[capacity]);
            memcpy(tmp_data.get(), data.get(), size_ * sizeof(value_type));
            data = move(tmp_data);
        }
        data[size_] = value;
        size_++;
    }
    
    void pop_back()
    {
        if(size_ == 0)
            return;
        data[size_ - 1].~T();
        size_--;
    }
    
    bool empty()
    {
        return size_ == 0;
    }
    
    void clear() noexcept
    {
        data = nullptr;
        capacity = 0;
        size_ = 0;
    }
    
    void resize(size_type newSize)
    {
        if(newSize == 0)
        {
            clear();
            return;
        }
       
        auto new_data = unique_ptr<value_type[]>(new value_type[newSize]);
        if (newSize < size_)
            memcpy(new_data.get(), data.get(), newSize * sizeof(value_type));
        else
            if (data)
                memcpy(new_data.get(), data.get(), size_ * sizeof(value_type));
        
        size_ = newSize;
        capacity = newSize;
        data = move(new_data);
    }
    
    void resize(size_type newSize, const value_type& defaultValue)
    {
        if(newSize == 0)
        {
            clear();
            return;
        }
        
        auto new_data = unique_ptr<value_type[]>(new value_type[newSize]);
        if (newSize < size_)
            memcpy(new_data.get(), data.get(), newSize * sizeof(value_type));
        else
            if (data)
                memcpy(new_data.get(), data.get(), size_ * sizeof(value_type));
        
        
        data = move(new_data);
        for (size_t i = size_; i < newSize; i++)
            data[i] = defaultValue;
        size_ = newSize;
        capacity = newSize;
    }

    
    T& operator[](size_type i)  const
    {
        if(i < 0 || i >= size_)
            throw Error("out of range");
        
        return data[i];
    }
    
    unsigned long size()
    {
        return size_;
    }
    
    virtual ~Vector()
    {
        clear();
    }
    
};

void test_push_back()
{
    Vector<int> vec(2,2);
    vec.push_back(2);
    check(vec[2] == 2, "invalid element in push_back");
}

void test_pop_back()
{
    Vector<int> vector(5);
    vector.pop_back();
    check(vector.size()==4, "invalid size in pop_back");
}

void test_resize()
{
    Vector<int> vec(2,2);
    
    vec.resize(3,100);
    check(vec[2] == 100, "invalid element in resize");
    check(vec.size() == 3, "invalid size in resize");
    
    vec.resize(2);
    check(vec.size() == 2, "invalid size in resize");
}

void test_operator()
{
    Vector<int> vec(3,2);
    vec[0] = 50;
    vec[1] = vec[0]*2;
    vec[2] = vec[1]*2;
    
    check(vec[0] == 50, "invalid element in []");
    check(vec[1] == 100, "invalid element in []");
    check(vec[2] == 200, "invalid element in []");
}

void test_iterator()
{
    Vector<int> vec(5);
    for (int i = 0; i <5; ++i)
        vec[i] = i;
    
    int i = 0;
    for(Iterator<int> it = vec.begin(); it != vec.end(); it++)
    {
        check(*it == i, "invalid element in iterator");
        i++;
    }
    
    i = 0;
    for(Iterator<int> it = vec.begin(); it != vec.end(); ++it)
    {
        check(*it == i, "invalid element in iterator");
        i++;
    }
    
}

void test_reverse_iterator()
{
    Vector<int> vec(5);
    for (int i = 0; i <5; ++i)
    {
        vec[i] = i;
    }
    
    unsigned long i = vec.size() - 1;
    for(RIterator<int> it = vec.rbegin(); it != vec.rend(); ++it)
    {
        check(*it == i, "invalid element in riterator");
        i--;
    }
    
    i = vec.size() - 1;
    for(RIterator<int> it = vec.rbegin(); it != vec.rend(); it++)
    {
        check(*it == i, "invalid element in riterator");
        i--;
    }
}

void test_clear()
{
    Vector<int> v(5, 1);
    v.clear();
    check(v.size() == 0, "invalid clear");
}

int main(int argc, const char * argv[])
{
    try
    {
        test_push_back();
        test_pop_back();
        test_resize();
        test_operator();
        test_iterator();
        test_reverse_iterator();
        test_clear();
        return 0;
    }
    
    catch (const Error& error)
    {
        cerr << "Error: "<< error.getMessage() << endl;
        return 1;
    }
    catch (...)
    {
        
    }
}
