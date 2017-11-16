#pragma once
#include <memory>

template <typename T>
class vector {
public:
    template <bool, typename>
    class base_iterator;

    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;

    using iterator = base_iterator<false, reference>;
    using reverse_iterator = base_iterator<true, reference>;
    using const_iterator = base_iterator<false, const_reference>;
    using const_reverse_iterator = base_iterator<true, const_reference>;

    template <bool REVERSE, typename REFERENCE>
    class base_iterator : public std::iterator<std::forward_iterator_tag, T> {
    public:
        explicit base_iterator(value_type* ptr) : ptr_(ptr) {}
    
        bool operator==(const base_iterator& other) const {
            return ptr_ == other.ptr_;
        }
    
        bool operator!=(const base_iterator& other) const {
            return !(*this == other);
        }
        
        REFERENCE operator*() const {
            return *ptr_;
        }

        template <bool R = REVERSE>
        std::enable_if_t<!R, base_iterator<false, REFERENCE>>& operator++() {
            ++ptr_;
            return *this;
        }

        template <bool R = REVERSE>
        std::enable_if_t<R, base_iterator<true, REFERENCE>>& operator++() {
            --ptr_;
            return *this;
        }
    protected:
        T* ptr_;
    };

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void clear() {
        for (auto it = this->rbegin(); it != this->rend(); ++it) {
            (*it).~value_type();
        }
        size_ = 0;
    }

    iterator begin() {
        return iterator(data_.get());
    }

    iterator end() {
        return iterator(data_.get() + size_);
    }

    const_iterator begin() const {
        return const_iterator(data_.get());
    }

    const_iterator end() const {
        return const_iterator(data_.get() + size_);
    }

    reverse_iterator rbegin() {
        return reverse_iterator(data_.get() + size_ - 1);
    }

    reverse_iterator rend() {
        return reverse_iterator(data_.get() - 1);
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(data_.get() + size_ - 1);
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(data_.get() - 1);
    }

    reference operator[](size_t index) {
        return data_[index];
    }

    const_reference operator[](size_t index) const {
        return data_[index];
    }

    void push_back(const_reference value) {
        maybe_expand();
        data_[size_] = value;
        ++size_;
    }

    void push_back(value_type&& value) {
        maybe_expand();
        data_[size_] = std::move(value);
        ++size_;
    }

    void pop_back() {
        --size_;
        data_[size_].~value_type();
    }

    void resize(size_t count) {
        if (count > capacity_) {
            expand(count);
        }
        for (size_t i = count; i < size_; ++i) {
            data_[i].~value_type();
        }
        size_ = count;
    }

    void resize(size_t count, const_reference value) {
        if (count > capacity_) {
            expand(count);
        }
        for (size_t i = count; i < size_; ++i) {
            data_[i].~value_type();
        }
        for (size_t i = size_; i < count; ++i) {
            data_[i] = std::move(value_type(value));
        }
        size_ = count;
    }

    vector() : capacity_(16), size_(0) {
        data_ = std::make_unique<value_type[]>(capacity_);
    }

    vector(const size_t size) : capacity_(size), size_(size) {
        data_ = std::make_unique<value_type[]>(capacity_);
    }

    vector(const std::initializer_list<value_type> list) : vector(list.size()) {
        std::copy(list.begin(), list.end(), data_.get());
    }
private:
    void maybe_expand() {
        if (capacity_ == size_) {
            expand(capacity_ * 2);
        }
    }

    void expand(size_t new_capacity) {
        if (new_capacity == 0) {
            new_capacity = 1;
        }
        auto tmp = std::make_unique<value_type[]>(new_capacity);
        capacity_ = new_capacity;
        for (size_t i = 0; i < size_; ++i) {
            tmp[i] = std::move(data_[i]);
        }
        data_ = std::move(tmp);
    }

    size_t capacity_;
    size_t size_;
    std::unique_ptr<value_type[]> data_;
};