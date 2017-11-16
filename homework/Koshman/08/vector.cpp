
template <class T>
struct Iterator: public std::iterator<std::random_access_iterator_tag, T>
{

    explicit Iterator(T* ptr) :ptr_(ptr) {}

    T& operator*() const {
        return *ptr_;
    }


    bool operator==(const Iterator& other) const {
        return other.ptr_ == ptr_;
    }


    bool operator!=(const Iterator& other) const {
        return !(*this == other);
    }


    bool operator<(const Iterator& other) const {
        return ptr_ < other.ptr_;
    }


    bool operator>(const Iterator& other) const {
        return ptr_ > other.ptr_;
    }


    Iterator& operator++() {
        ptr_++;
        return *this;
    }


    Iterator& operator--() {
        ptr_--;
        return *this;
    }


    Iterator& operator+(size_t n) {
        ptr_ += n;
        return *this;
    }


    Iterator& operator-(size_t n) {
        ptr_ -= n;
        return *this;
    }

private:
    T* ptr_;

};


template <class T>
struct ReverseIterator: public std::reverse_iterator <std::iterator<std::random_access_iterator_tag, T>>
{

    explicit ReverseIterator(T* ptr) :ptr_(ptr) {}


    T& operator*() const {
        return *ptr_;
    }


    bool operator==(const ReverseIterator& other) const {
        return other.ptr_ == ptr_;
    }


    bool operator!=(const ReverseIterator& other) const {
        return !(*this == other);
    }


    bool operator<(const ReverseIterator& other) const {
        return ptr_ > other.ptr_;
    }


    bool operator>(const ReverseIterator& other) const {
        return ptr_ < other.ptr_;
    }


    ReverseIterator& operator++() {
        ptr_--;
        return *this;
    }


    ReverseIterator& operator--() {
        ptr_++;
        return *this;
    }


    ReverseIterator& operator+(size_t n) {
        ptr_ -= n;
        return *this;
    }


    ReverseIterator& operator-(size_t n) {
        ptr_ += n;
        return *this;
    }

private:
    T* ptr_;

};


template<class T,
    class Alloc = std::allocator<T>>
struct Vector
{

    using size_type = size_t;
    using iterator = Iterator<T>;
    using const_iterator = Iterator<const T>;
    using reverse_iterator = ReverseIterator<T>;
    using const_reverse_iterator = ReverseIterator<const T>;

    explicit Vector(size_type size)
                    : size_(size)
                    , capacity_(size) {
        if (size != 0) {
            data_ = std::unique_ptr<T[]>(new T[size_]);
        } else {
            data_ = nullptr;
        }
    }

    Vector(size_type size, const T& defaultValue) 
                    : size_(size)
                    , capacity_(size) {
        data_ = std::unique_ptr<T[]>(new T[size_]);
        for (size_type i = 0; i < size_; i++) {
            data_[i] = T(defaultValue);
        }
    }

    Vector(std::initializer_list<T> store)
                    : size_(store.size())
                    , capacity_(store.size()) {
        if (store.size() != 0) {
            data_ = std::unique_ptr<T[]>(new T[size_]);
            std::copy(store.begin(), store.end(), data_.get());
        } else {
            data_ = nullptr;
        }
    }

    iterator begin() noexcept {
        return iterator(data_.get());
    }
    
    const_iterator begin() const noexcept {
        return const_iterator(data_.get());
    }

    iterator end() noexcept {
        return iterator(data_.get() + size_);
    }
    
    const_iterator end() const noexcept {
        return const_iterator(data_.get() + size_);
    }

    reverse_iterator rbegin() noexcept {
        return reverse_iterator(data_.get() + size_ - 1);
    }

    reverse_iterator rend() noexcept {
        return reverse_iterator(data_.get() - 1);
    }

    void push_back(T&& value) {
        if (size_ == capacity_) {
            if (capacity_ == 0) {
                capacity_ = 1;
            } else {
                capacity_ *= 2;
            }

            auto tmp = std::unique_ptr<T[]>(new T[capacity_]);
            if (size_)
                std::copy(data_.get(), data_.get() + size_, tmp.get());
            data_ = std::move(tmp);
        }

        
        data_[size_] = value;
        size_++;
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            if (capacity_ == 0) {
                capacity_ = 1;
            } else {
                capacity_ *= 2;
            }
            
            auto tmp = std::unique_ptr<T[]>(new T[capacity_]);
            std::copy(data_.get(), data_.get() + size_, tmp.get());
            data_ = std::move(tmp);
        }
        
        data_[size_] = value;
        size_++;
    }

    bool empty() const {
        return size_ == 0;
    }

    size_type size() const {
        return size_;
    }

    size_type capacity() const {
        return capacity_;
    }

    void clear() {
        for (auto i = this->begin(); i < this->end(); ++i){
            *i = T();
        }
        size_ = 0;
    }

    void erase(size_type index) {
        auto tmp = std::unique_ptr<T[]>(new T[capacity_]);
        std::copy(data_.get(), data_.get() + index, tmp.get());
        std::copy(data_.get() + index + 1, data_.get() + size_, tmp.get() + index);
        
        data_ = std::move(tmp);
        size_--;
    }

    void pop_back() {
        this->erase(size_ - 1);
    }

    T operator[](size_type index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    T& operator[](size_type index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    void resize(size_type new_size) {
        if (new_size < capacity_)
            size_ = new_size;
        capacity_ = new_size;
        auto tmp = std::unique_ptr<T[]>(new T[capacity_]);
        std::copy(data_.get(), data_.get() + size_, tmp.get());
        data_ = std::move(tmp);
        if (new_size < capacity_)
            size_ = new_size;
    }

    bool operator==(Vector<T> const &other) const {
        if (this->size() != other.size())
            return false;
        auto i = this->begin();
        auto j = other.begin();
        while (i < this->end()){
            if (*i != *j)
                return false;
            ++i;
            ++j;
        }
        return true;
    }

    bool operator!=(Vector<T> const &other) const {
        return !(*this == other);
    }

private:
    size_t size_;
    size_t capacity_;
    std::unique_ptr<T[]> data_;
};
