#include <iostream>

template <class T>
class Iterator
    : public std::iterator<std::random_access_iterator_tag, T> {
    T* ptr_;
public:
    explicit Iterator(T* ptr)
        :ptr_(ptr) {

    }

    bool operator==(const Iterator<T>& other) const {
        return ptr_ = other.ptr_;
    }

    bool operator!=(const Iterator<T>& other) {
        return !(*this == other);
    }

    bool operator>(const Iterator<T>& other) const {
        return ptr_ > other.ptr_;
    }

    bool operator<(const Iterator<T>& other) const {
        return ptr_ < other.ptr_;
    }

    Iterator<T> operator+(size_t n) {
        ptr_ += n;
        return *this;
    }

    Iterator<T> operator-(size_t n) {
        ptr_ -= n;
        return *this;
    }

    T& operator*() const {
        return *ptr_;
    }

    Iterator& operator++() {
        ++ptr_;
        return *this;
    }
    Iterator& operator--() {
        --ptr_;
        return *this;
    }
};

template <class T>
class ReverseIterator
    : public std::iterator<std::random_access_iterator_tag, T> {
    T* ptr_;
public:
    explicit ReverseIterator(T* ptr)
        :ptr_(ptr) {

    }

    bool operator==(const ReverseIterator<T>& other) const {
        return ptr_ = other.ptr_;
    }

    bool operator!=(const ReverseIterator<T>& other) {
        return !(*this == other);
    }

    bool operator>(const ReverseIterator<T>& other) const {
        return ptr_ < other.ptr_;
    }

    bool operator<(const ReverseIterator<T>& other) const {
        return ptr_ > other.ptr_;
    }

    ReverseIterator<T> operator+(size_t n) {
        ptr_ -= n;
        return *this;
    }

    ReverseIterator<T> operator-(size_t n) {
        ptr_ += n;
        return *this;
    }

    T& operator*() const {
        return *ptr_;
    }

    ReverseIterator& operator++() {
        --ptr_;
        return *this;
    }
    ReverseIterator& operator--() {
        ++ptr_;
        return *this;
    }
};

template <class T, 
    class Alloc = std::allocator<T>>
class Vector {
    size_t capacity_;
    size_t size_;
    T* array_;
public:
    Vector() {
        capacity_ = 0;
        size_ = 0;
        array_ = NULL;
    }

    Vector(size_t n) {
        array_ = NULL;
        reserve(n, false);
        size_ = 0;
    }

    Vector(std::initializer_list<T> init) {
        array_ = NULL;
        size_t init_size = init.size();
        
        reserve(init_size, false);

        size_t i = 0;
        auto current = init.begin();
        const auto end = init.end();
        while (current != end)
        {
            array_[i++] = *current++;
        }
        size_ = init_size;
    }

    ~Vector() {
        if (array_) {
            delete [] array_;
        }
    }

    T& operator[](size_t i) {
        return array_[i];
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) {
            reserve(2 * capacity_, true);
        }
        array_[size_] = value;
        size_++;
    }

    void push_back(T&& value) {
        if (size_ >= capacity_) {
            reserve(2 * capacity_, true);
        }
        array_[size_] = std::move(value);
        size_++;
    }

    void pop_back() {
        if (size_ == 0) {
            throw("Can't pop from empty array");
        }
        array_[size_ - 1].~T();
        size_--;
    }

    void reserve(size_t n, bool copy) {
        T* new_array;
        
        new_array = new T[n];

        if (copy) {
            for(size_t i = 0; i < size_; ++i) {
                new_array[i] = std::move(array_[i]);
            }
        }

        if (array_) {
            delete [] array_;
        }

        array_ = new_array;

        capacity_ = n;
    }

    size_t size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void clear() {
        for(size_t i = 0; i < size_; ++i) {
            array_[i].~T();
        }
        size_ = 0;
    }

    void resize(size_t n) {
        if (n < size_) {
            for(size_t i = n; i < size_; ++i) {
                array_[i].~T();
            }
            size_ = n;
            return;
        }

        if (n > size_) {
            if(n > capacity_) {
                reserve(n, true);
            }
            for(size_t i = size_; i < n; ++i) {
                array_[i] = T();
            }
            size_ = n;
        }
    }

    // fill empty elements with val
    void resize(size_t n, const T& val) {
        if (n < size_) {
            for(size_t i = n; i < size_; ++i) {
                array_[i].~T();
            }
            size_ = n;
            return;
        }

        if (n > size_) {
            if(n > capacity_) {
                reserve(n, true);
            }
            for(size_t i = size_; i < n; ++i) {
                array_[i] = val;
            }
            size_ = n;
        }        
    }

    Iterator<T> begin() noexcept {
        return Iterator<T>(array_);
    }

    Iterator<const T> begin() const noexcept {
        return Iterator<const T>(array_);
    }
    
    Iterator<T> end() noexcept {
        return Iterator<T>(array_ + size_);
    }

    Iterator<const T> end() const noexcept {
        return Iterator<const T>(array_ + size_);
    }

    ReverseIterator<T> rbegin() noexcept {
        return ReverseIterator<T>(array_ + size_ - 1);
    }

    ReverseIterator<const T> rbegin() const noexcept {
        return ReverseIterator<const T>(array_ + size_ - 1);
    }

    ReverseIterator<T> rend() noexcept {
        return ReverseIterator<T>(array_ - 1);
    }

    ReverseIterator<const T> rend() const noexcept {
        return ReverseIterator<const T>(array_ - 1);
    }

    friend std::ostream& operator<< (std::ostream& out, const Vector<T>& vector) {
        for(size_t i = 0; i < vector.size_; ++i) {
            out << vector.array_[i] << ' ';
        }
        return out;
    }
};

int test_indexing() {
    Vector<int> v({1, 2, 3});
    
    return (v[0] != 1) + (v[1] != 2) + (v[2] != 3);
}

int test_push_back() {
    Vector<int> v({1, 2, 3});
    v.push_back(5);

    Vector<int> v1;
    v1.push_back(5);

    return (v[3] != 5) + (v1[0] != 5);
}

int test_pop_back() {
    Vector<int> v({1, 2, 3});
    v.pop_back();
    int r = (v[0] != 1) + (v[1] != 2) + (v.size() != 2);

    Vector<int> v1;
    try {
        v1.pop_back();
    } catch (const char *exeption) {
        std::cerr << exeption << ". Ok because it was a test." << std::endl;
        return r;
    }
    return 1; // pop_back worked for empty vector
}

int test_empty() {
    Vector<int> v({1, 2, 3});
    Vector<int> v1;
    Vector<int> v2({5});
    v2.pop_back();
    
    return (v.empty() == true) + (v1.empty() == false) + (v2.empty() == false);
}

int test_size() {
    Vector<int> v({1, 2, 3, 4, 5});
    Vector<int> v1({1, 2, 3});
    v1.push_back(4);
    Vector<int> v2({1, 2, 3});
    v2.pop_back();
    return (v.size() != 5) + (v1.size() != 4) + (v2.size() != 2);
}

int test_clear() {
    Vector<int> v({1, 2, 3, 4, 5});
    v.clear();
    return (v.size() != 0);
}

int test_begin_end() {
    Vector<int> v({1, 2, 3, 4, 5});
    auto it = v.begin();
    int r = 0;
    int i = 0;
    for(; it < v.end(); ++it) {
        if (*it != v[i]) {
            ++r;
        }
        ++i;
    }
    return r + (i != 5);
}

int test_rbegin_rend() {
    Vector<int> v({1, 2, 3, 4, 5});
    auto it = v.rbegin();
    int r = 0;
    size_t i = 4;
    for(; it < v.rend(); ++it) {
        if (*it != v[i]) {
            ++r;
        }
        --i;
    }
    return r + (i != size_t(-1));
}

int test_resize() {
    Vector<int> v({1, 2, 3, 4, 5});
    v.resize(2);

    Vector<int> v1({1, 2, 3, 4, 5});
    v1.resize(6);

    Vector<int> v2({1, 2, 3, 4, 5});
    v2.resize(6, 12);

    int r = 0;
    r += (v.size() != 2) + (v[0] != 1) + (v[1] != 2);

    r += (v1.size() != 6);
    for(size_t i = 0; i < 5; i++) {
        r += (v1[i] != int(i + 1));
    }

    r += (v2.size() != 6);
    for(size_t i = 0; i < 5; i++) {
        r += (v2[i] != int(i + 1));
    }
    r += (v2[5] != 12);

    return r;
}

int test_vector() {
    return test_indexing() + 
           test_push_back() + 
           test_pop_back() +
           test_empty() +
           test_size() +
           test_clear() + 
           test_begin_end() +
           test_rbegin_rend() +
           test_resize();
}

int main() {
    
    try {
        std::cout << "Got " << test_vector() << " errors" << std::endl;
    } catch (const char *exeption) {
        std::cerr << exeption << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Something unexpected\n";
        return 2;
    }

    return 0;
}
