#include <iostream>


template<class T>
class Iterator
        : public std::iterator<std::forward_iterator_tag, T> {
    T *ptr_;
public:
    using reference = T &;

    explicit Iterator(T *ptr)
            : ptr_(ptr) {
    }

    bool operator==(const Iterator<T> &other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Iterator<T> &other) const {
        return !(*this == other);
    }

    reference operator*() const {
        return *ptr_;
    }

    T *operator->() {
        return ptr_;
    }

    Iterator &operator++() {
        ++ptr_;
        return *this;
    }

    Iterator &operator++(T) {
        ++ptr_;
        return *this;
    }
};

template<class T>
class reverse_Iterator
        : public std::iterator<std::forward_iterator_tag, T> {
    T *ptr_;
public:
    using reference = T &;

    explicit reverse_Iterator(T *ptr)
            : ptr_(ptr) {
    }

    bool operator==(const reverse_Iterator<T> &other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const reverse_Iterator<T> &other) const {
        return !(*this == other);
    }

    reference operator*() const {
        return *ptr_;
    }

    T *operator->() {
        return ptr_;
    }

    reverse_Iterator &operator++() {
        --ptr_;
        return *this;
    }

    reverse_Iterator &operator++(T) {
        --ptr_;
        return *this;
    }
};


template<class T,
        class Alloc = std::allocator<T>>
class Vector {
public:
    using size_type = size_t;
    using value_type = T;

    using reference = value_type &;
    using const_reference = const value_type &;

    using iterator = Iterator<T>;
    using const_iterator = Iterator<const T>;
    using reverse_iterator = reverse_Iterator<T>;
    using const_reverse_iterator = reverse_Iterator<const T>;


    explicit Vector() {
        size_ = 0;
        capacity_ = 0;
        data_ = nullptr;
    }

    explicit Vector(size_type n) {
        size_ = n;
        capacity_ = n;
        data_ = allocator_.allocate(n);
    }

    explicit Vector(size_type n, const T &value) {
        size_ = n;
        capacity_ = n;
        data_ = allocator_.allocate(n);
        for (size_type i = 0; i < size_; ++i)
            data_[i] = value;
    }

    //operator[]
    reference operator[](size_type n) {
        return data_[n];
    }

    const_reference operator[](size_type n) const {
        return data_[n];
    }

    //push_back
    void push_back(const T &x) {
        if (size_ == capacity_) {
            capacity_ = (capacity_ == 0) ? 8 : (capacity_ * 2);

            reserve(capacity_);
        }

        data_[size_++] = x;
    }

    void push_back(T &&x) {
        if (size_ == capacity_) {
            capacity_ = (capacity_ == 0) ? 8 : (capacity_ * 2);
            reserve(capacity_);
        }
        data_[size_++] = std::move(x);
    }

    //pop_back
    void pop_back() {
        size_--;
    }

    //empty
    bool empty() const noexcept {
        return size_ == 0;
    }

    //size
    size_t size() const noexcept {
        return size_;
    }

    //clear
    void clear() noexcept {
        allocator_.deallocate(data_, capacity_);
        size_ = capacity_ = 0;
    }

    //begin, end, rbegin, rend
    iterator begin() noexcept {
        return iterator(data_);
    }

    const_iterator begin() const noexcept {
        return const_iterator(data_);
    }

    iterator end() noexcept {
        return iterator(data_ + size_);
    }

    const_iterator end() const noexcept {
        return const_iterator(data_ + size_);
    }

    reverse_iterator rbegin() noexcept {
        return reverse_iterator(data_);
    }

    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(data_);
    }

    reverse_iterator rend() noexcept {
        return reverse_iterator(data_ + size_);
    }

    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(data_ + size_);
    }

    //resize
    void resize(size_t sz) {
        reserve(sz);
        size_ = sz;
    }

    void resize(size_t sz, const T &c) {
        reserve(sz);

        for (size_t i = size_; i < sz; i++) {
            data_[i] = c;
        }
        size_ = sz;
    }

    void reserve(size_t sz) {
        T *tmp = allocator_.allocate(sz);

        for (size_type i = 0; i < std::min(size_, sz); i++) {
            tmp[i] = data_[i];
        }
        capacity_ = sz;
        size_ = std::min(size_, sz);
        allocator_.deallocate(data_, size_);
        data_ = tmp;
    }

private:
    T *data_;
    size_t size_;
    size_t capacity_;
    Alloc allocator_;
};

void check(bool value) {
    if (!value)
        std::cout << "error" << std::endl;
    else
        std::cout << "ok" << std::endl;
}

template<typename T>
void check_vector() {
    Vector<T> v1 = Vector<T>(5, 0);

    v1[1] = 2;
    check(v1[0] == 0);
    check(v1[1] == 2);

    T x = 3;
    v1.push_back(x);
    check(v1.size() == 6);
    check(v1[5] == x);

    v1.pop_back();
    check(v1.size() == 5);

    v1.clear();
    check(v1.empty());

    v1.resize(10, x);
    check(v1.size() == 10);

    auto iter = v1.begin();
    auto r_iter = v1.rend();
    r_iter++;
    while ((iter != v1.end()) && (r_iter != v1.rbegin())) {
        check(*iter == *r_iter);
        iter++;
        r_iter++;
    }

}


int main() {
    check_vector<int>();
    return 0;
}