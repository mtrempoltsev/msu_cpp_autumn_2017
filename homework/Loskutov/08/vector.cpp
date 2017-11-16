#include <iostream>
#include <vector>
#include <stdexcept>

template<class T, class Alloc = std::allocator<T>>
class vector {
private:
    T* data_;
    size_t size_;
    Alloc allocator_;
    
    class iterator {
    private:
        T* ptr_;
        bool reverse_type_;
        
        T* next_element() {
            if (reverse_type_) {
                return ptr_--;
            }
            return ptr_++;
        }
    public:
        explicit iterator(T* ptr): ptr_(ptr), reverse_type_(false) {}
        iterator(T* ptr, bool reverse_type): ptr_(ptr), reverse_type_(reverse_type) {}
        
        iterator operator++() {
            next_element();
            return *this;
        }
        
        iterator operator++(int i) {
            next_element();
            return *this;
        }
        
        T& operator*() {
            return *ptr_;
        }
        
        T* operator->() {
            return ptr_;
        }
        
        bool operator==(const iterator& rhs) {
            return ptr_ == rhs.ptr_;
        }
        
        bool operator!=(const iterator& rhs) {
            return ptr_ != rhs.ptr_;
        }
    };
    
    class const_iterator {
    private:
        T* ptr_;
        bool reverse_type_;
        
        const_iterator next_element() {
            if (reverse_type_) {
                return ptr_--;
            }
            return ptr_++;
        }
        
    public:
        explicit const_iterator(T* ptr): ptr_(ptr), reverse_type_(false) {}
        const_iterator(T* ptr, bool reverse_type): ptr_(ptr), reverse_type_(reverse_type) {}
        
        const_iterator operator++() {
            next_element();
            return *this;
        }
        
        const_iterator operator++(int i) {
            next_element();
            return *this;
        }
        
        const T& operator*() {
            return *ptr_;
        }
        
        const T* operator->() {
            return ptr_;
        }
        
        bool operator==(const const_iterator& rhs) {
            return ptr_ == rhs.ptr_;
        }
        
        bool operator!=(const const_iterator& rhs) {
            return ptr_ != rhs.ptr_;
        }
    };
    
public:
    using size_type = size_t;
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    
    explicit vector(size_type count): size_(count) {
        try {
            data_ = allocator_.allocate(count);
        } catch(...) {
            throw std::bad_alloc();
        }
    }
    
    vector(size_type count, const value_type& defaultValue): size_(count) {
        try {
            data_ = allocator_.allocate(count);
        } catch(...) {
            throw std::bad_alloc();
        }
        for (size_type i = 0; i < size_; i++) {
            data_[i] = defaultValue;
        }
    }
    
    ~vector() {
        clear();
    }
    
    reference operator[](size_type pos) {
        if (pos >= size_) {
            throw std::invalid_argument("Index out of range");
        }
        return data_[pos];
    }
    
    constexpr const_reference operator[](size_type pos) const {
        return data_[pos];
    }
    
    void resize(size_type newSize) {
        value_type* tmpData;
        try {
            tmpData = allocator_.allocate(size_);
        } catch(...) {
            throw std::bad_alloc();
        }
        for (size_type i = 0; i < size_; ++i) {
            tmpData[i] = data_[i];
        }
        try {
            data_ = allocator_.allocate(newSize);
        } catch(...) {
            throw std::bad_alloc();
        }
        for (size_type i = 0; i < ((newSize > size_) ? size_ : newSize); ++i) {
            data_[i] = tmpData[i];
        }
        size_ = newSize;
    }
    
    void resize(size_type newSize, const value_type& defaultValue) {
        size_type oldSize = size_;
        try {
            resize(newSize);
        } catch(...) {
            throw std::bad_alloc();
        }
        if (newSize > oldSize) {
            for (size_type i = oldSize; i < size_; i++) {
                data_[i] = defaultValue;
            }
        }
    }
    
    void push_back(value_type&& value) {
        try {
            resize(size_+1);
        } catch(...) {
            throw std::bad_alloc();
        }
        data_[size_-1] = value;
    }
    
    void push_back(const value_type& value) {
        try {
            resize(size_+1);
        } catch(...) {
            throw std::bad_alloc();
        }
        data_[size_-1] = value;
    }
    
    void clear() noexcept {
        allocator_.deallocate(data_, size_);
        size_ = 0;
    }
    size_type size() noexcept {
        return size_;
    }
    
    bool empty() noexcept {
        return (size_ == 0);
    }
    
    iterator begin() noexcept {
        return iterator(data_);
    }
    
    const_iterator begin() const noexcept {
        return const_iterator(data_);
    }
    
    iterator rbegin() noexcept {
        return iterator(data_ + size_-1, true);
    }
    
    const_iterator rbegin() const noexcept {
        return const_iterator(data_ + size_-1, true);
    }
    
    iterator end() noexcept {
        return iterator(data_ + size_-1);
    }
    
    const_iterator end() const noexcept {
        return const_iterator(data_ + size_-1);
    }
    
    iterator rend() noexcept {
        return iterator(data_ - 1, true);
    }
    
    const_iterator rend() const noexcept {
        return const_iterator(data_ - 1, true);
    }
};

void check(bool value) {
    if (!value)
        std::cout << "error!" <<std::endl;
}

template<class T>
void test() {
    try {
        typename std::vector<T> stdVec(3, 4);
        vector<T> vec(3, 4);
    
        vec.push_back(4);
        stdVec.push_back(4);
        check(vec.size() == stdVec.size());
    
        auto it = vec.begin();
        auto stdIt = stdVec.begin();
        while ((it != vec.end()) && (stdIt != stdVec.end())) {
            check(*it == *stdIt);
            it++;
            stdIt++;
        }
    
        auto it2 = vec.rbegin();
        auto stdIt2 = stdVec.rbegin();
        while ((it2 != vec.rend()) && (stdIt2 != stdVec.rend())) {
            check(*it2 == *stdIt2);
            it2++;
            stdIt2++;
        }
    
        for (size_t i = 0; i < vec.size(); ++i) {
            check(vec[i] == 4);
        }
    
        vec[1] = -1;
        stdVec[1] = -1;
        check(vec[1] == stdVec[1]);
    
        vec.resize(1);
        stdVec.resize(1);
        check(vec[0] == stdVec[0]);
        check(vec.size() == stdVec.size());
    
        vec.clear();
        stdVec.clear();
        check(vec.empty() == stdVec.empty());
    
        vec.resize(5, 3);
        stdVec.resize(5, 3);
        check(vec.size() == stdVec.size());
        check(vec[4] == stdVec[4]);
    } catch(...) {
        std::cout << "error!" << std::endl;
    }
}


int main() {
    test<int>();
    test<double>();
    
    return 0;
}
