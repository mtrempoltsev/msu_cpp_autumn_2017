#include <iostream>
#include <stdio.h>
#include <memory>
#include <vector>


//базовый класс ошибок
class Error {
protected:
    std::string message_;
public:
    const std::string getMessage() const {
        return message_;
    }
};

//класс ошибок, возникающих в базовых операциях/функциях класса Vector
class VectorError : public Error
{
public:
    VectorError(std::string&& message) {
        message_ = message;
    }
};


//класс ошибок, возникающих в базовых операциях/функциях при использовании итераторов
class IteratorError : public Error
{
public:
    IteratorError(std::string&& message) {
        message_ = message;
    }
};

//класс ошибок возникающих при неправильных значениях векторов
class ValueError: public Error {
public:
    ValueError(std::string&& message) {
        message_ = message;
    }
};

template<class T> void test();

template <class T, bool reverse>
class Iterator: public std::iterator<std::forward_iterator_tag, T>
{
    T* ptr_;
    
    void next_() {
        if (reverse) {
            ptr_--;
        } else {
            ptr_++;
        }
    }
    
public:
    using const_reference = const Iterator<T, reverse>&;
    using reference_type = T&;
    
    explicit Iterator(T* ptr) : ptr_(ptr) {}
    
    bool operator==(const_reference other) const
    {
        return ptr_ == other.ptr_;
    }
    
    bool operator!=(const_reference other) const
    {
        return !(*this == other);
    }
    
    reference_type operator*() const
    {
        return *ptr_;
    }
    
    Iterator& operator++()
    {
        next_();
        return *this;
    }
    
    Iterator& operator++(T)
    {
        next_();
        return *this;
    }
    
    
};

//шаблонная реализация класса Vector
template<class T, class Alloc = std::allocator<T>>
class Vector
{
    using size_type = size_t;
    using value_type = T;
    using value_type_ptr = T*;
    using lvalue_type = value_type&&;
    using reference = value_type&;
    using const_reference = const value_type&;
    
    static const int default_size = 128;
    
    using iterator = Iterator<value_type, false>;
    using const_iterator = Iterator<const_reference, false>;
    using reverse_iterator = Iterator<value_type, true>;
    using const_reverse_iterator = Iterator<const_reference, true>;
    
    
public:
    explicit Vector()
    {
        size_ = default_size;
        capacity_ = default_size;
        data_ = allocator_.allocate(default_size);
    }
    explicit Vector(size_type count)
    {
        size_ = count;
        capacity_ = count;
        data_ = allocator_.allocate(count);
        throw std::bad_alloc();
    }
    explicit Vector(size_type count, value_type defaultValue)
    {
        size_ = count;
        capacity_ = count;
        data_ = allocator_.allocate(count);

        for (size_type i = 0; i < size_; i++) {
            data_[i] = defaultValue;
        }
    }
    
    void push_back(const_reference value) {
        if (size_ == capacity_) {
            reserve(capacity_ * 2);
        }
        data_[size_] = value;
        size_++;
    }
    
    void push_back(lvalue_type value) {
        if (size_ == capacity_){
            reserve(capacity_ * 2);
        }
        data_[size_] = std::move(value);
        size_++;
    }
    
    reference pop_back() {
        size_--;
        return data_[size_];
    }
    
    void reserve(size_type count)
    {
        value_type_ptr tmp;
        
        tmp = allocator_.allocate(size_);
        
        for (size_type i = 0; i < size_; i++) {
            tmp[i] = data_[i];
        }
        

        data_ = allocator_.allocate(count);
        
        size_type bound = std::min(size_, count);
        for (size_type i = 0; i < bound; i++) {
            data_[i] = tmp[i];
        }
        capacity_ = count;
        size_ = bound;
        allocator_.deallocate(tmp, size_);
    }
    
    size_type capacity() const noexcept
    {
        return capacity_;
    }
    
    void resize(size_type newSize)
    {
        reserve(newSize);
        size_ = newSize;
    }
    
    void resize(size_type newSize, value_type defaultValue)
    {
        reserve(newSize);

        for (size_type i = size_; i < newSize; i++) {
            data_[i] = defaultValue;
        }
        size_ = newSize;
    }
    
    constexpr size_type size() const noexcept
    {
        return size_;
    }
    
    reference operator[](size_type pos)
    {
        return data_[pos];
    }
    
    constexpr const_reference operator[](size_type pos) const
    {
        return data_[pos];
    }
    
    void clear() noexcept {
        allocator_.deallocate(data_, capacity_);
        size_ = 0;
        capacity_ = 0;
    }

    bool empty() noexcept {
        return size_ == 0;
    }

    iterator begin() noexcept
    {
        return iterator(data_);
    }
    
    const_iterator begin() const noexcept
    {
        return const_iterator(data_);
    }
    
    iterator end() noexcept
    {
        return iterator(data_ + size_);
    }
    
    const_iterator end() const noexcept
    {
        return const_iterator(data_ + size_);
    }
    
    
    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(data_ + size_ - 1);
    }
    
    const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(data_ + size_ - 1);
    }
    
    reverse_iterator rend() noexcept
    {
        return reverse_iterator(data_ - 1);
    }
    
    const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(data_ - 1);
    }
    
private:
    T* data_;
    size_t size_;
    size_t capacity_;
    Alloc allocator_;
};

int main(int argc, char* argv[]) {
    
    try {
        test<int>();
    }
    catch (const ValueError& error) {
        std::cerr << error.getMessage() << std::endl;
    }
    catch (const IteratorError& error) {
        std::cerr << error.getMessage() << std::endl;
    }
    catch (...) {
        std::cerr << "Unexpected Exception" << std::endl;
    }
    std::cout << "Finish testing..." << std::endl;
   
    return 0;
}

void check(bool value) {
    if (!value) {
        throw ValueError("Value error while testing");
    }
}

template<class T>
void test()
{
    try {
        Vector<T> vec = Vector<T>(3, 100);
        
        vec[1] = 20;
        check(vec[0] == 100);
        check(vec[1] == 20);
        check(vec[2] == 100);
        
        T a = 5;
        vec.push_back(a);
        
        check(vec.size() == 4);
        check(vec[3] == 5);
        
        T b = vec.pop_back();
        check(b == 5);
        
        vec.resize(5, -10);
        check(vec[3] == -10);
        check(vec.size() == 5);
        
        vec.reserve(100);
        check(vec.capacity() == 100);
        check(vec.size() == 5);
        
        vec.reserve(3);
        check(vec.size() == 3);
    }
    catch(const ValueError& error) {
        std::cerr << error.getMessage() << std::endl;
    }
    catch(...) {
        throw VectorError("Vector error while testing");
    }
    
    try {
        std::vector<T> stdvec(3, 4);
        Vector<T> myvec(3, 4);
        
        myvec.push_back(4);
        stdvec.push_back(4);
        check(myvec.size() == stdvec.size());
        
        auto iter = myvec.begin();
        auto stditer = stdvec.begin();
        while ((iter != myvec.end()) && (stditer != stdvec.end())) {
            check(*iter == *stditer);
            iter++;
            stditer++;
        }
        
        auto iter2 = myvec.rbegin();
        auto stditer2 = stdvec.rbegin();
        while ((iter2 != myvec.rend()) && (stditer2 != stdvec.rend())) {
            check(*iter2 == *stditer2);
            iter2++;
            stditer2++;
        }
    }
    catch(const ValueError& error) {
        std::cerr << error.getMessage() << std::endl;
    }
    catch(...) {
        throw IteratorError("Iterator error while testing");
    }
    
}




