#include <memory>
#include <string>

template<class T>
class vector
{
    void expand(size_t new_capacity_)
    {
        T* new_array_ = new T[new_capacity_];

        for (size_t i = 0; i < size_; i++)
            new_array_[i] = std::move(array_[i]);
        delete []array_;
        array_ = new_array_;
        capacity_ = new_capacity_;
    }

    T* array_;
    size_t size_;
    size_t capacity_;

    template<bool is_reversed, typename reference>
    class Iterator : public std::iterator<std::bidirectional_iterator_tag, T>
    {
        T* ptr_;
        public:
            Iterator(T* ptr)
                : ptr_(ptr)
            {
            }

            bool operator==(const Iterator& other) const
            {
                return ptr_ == other.ptr_;
            }

            bool operator!=(const Iterator& other) const
            {
                return !(*this == other);
            }

            reference operator*() const
            {
                return *ptr_;
            }

            Iterator& operator++()
            {
                (is_reversed) ? --ptr_: ++ ptr_;
                return *this;
            }
    };

public:

    using iterator = Iterator<false, T&>;
    using reverse_iterator = Iterator<true, T&>;
    using const_iterator = Iterator<false, const T&>;
    using const_reverse_iterator = Iterator<true, const T&>;

    vector(): capacity_(8), size_(0)
    {
        array_ = new T[capacity_];
    }

    vector(size_t size): capacity_(size), size_(size)
    {
        array_ = new T[capacity_];
    }

    vector(size_t size, const T& default_value): vector(size)
    {
        for (size_t i = 0; i < size_; i++)
            array_[i] = default_value;
    }

    vector(const std::initializer_list<T>& init) : vector(init.size())
    {
        std::copy(init.begin(), init.end(), array_);
    }

    void push_back(const T& elem)
    {
        if (size_ == capacity_)
            expand(capacity_ * 2);

        array_[size_++] = elem;
    }

    void push_back(T&& elem)
    {
        if (size_ == capacity_)
            expand(capacity_ * 2);

        array_[size_++] = std::move(elem);
    }

    T& operator [](size_t index)
    {
        if (index >= size_)
            throw std::invalid_argument("index is out of range");

        return array_[index];
    }

    void resize(size_t new_size_)
    {
        if (new_size_ > capacity_)
            expand(new_size_);

        for (size_t i = new_size_; i < capacity_; i++)
            (array_ + i)->~T();

        size_ = new_size_;
    }

    void resize(size_t new_size_, const T& value)
    {
        if (new_size_ > capacity_)
            expand(new_size_);

        for (size_t i = size_; i < new_size_; i++)
            array_[i] = value;

        for (size_t i = new_size_; i < capacity_; i++)
            (array_ + i)->~T();

        size_ = new_size_;
    }

    bool empty() const
    {
        return size_ == 0;
    }

    iterator begin() noexcept
    {
        return iterator(array_);
    }

    iterator end() noexcept
    {
        return iterator(array_ + size_);
    }

    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(array_ + size_ - 1);
    }

    reverse_iterator rend() noexcept
    {
        return reverse_iterator(array_ - 1);
    }

    const_iterator cbegin() const noexcept
    {
        return const_iterator(array_);
    }

    const_iterator cend() const noexcept
    {
        return const_iterator(array_ + size_);
    }

    const_reverse_iterator crbegin() const noexcept
    {
        return const_reverse_iterator(array_ + size_ - 1);
    }

    const_reverse_iterator crend() const noexcept
    {
        return const_reverse_iterator(array_ - 1);
    }

    void clear()
    {
        for (size_t i = 0; i < size_; i++)
            (array_ + i)->~T();

        size_= 0 ;
    }

    size_t size() const
    {
        return size_;
    }

    size_t capacity() const
    {
        return capacity_;
    }

    void pop_back()
    {
        if (size_ == 0)
            throw std::invalid_argument("cannot pop element from empty vector");

        size_--;
        (array_ + size_)->~T();
    }

    ~vector()
    {
        delete []array_;
    }
};
