#include <memory>
#include <iostream>
#include "TIterator.h"

template<class T>
class TVector 
{
private:
    T* data_;
    size_t size_;
    size_t capacity_;
public:    
    using iterator = TIterator<T>;
    using const_iterator = TIterator<const T>;
    using reverse_iterator = TReverseIterator<T>;
    using const_reverse_iterator = TReverseIterator<const T>;

    TVector() : data_(nullptr), size_(0), capacity_(0) { }
    ~TVector() 
    {    
        this->size_ = this->capacity_ = 0;
        if (this->data_ != nullptr)
        {
            delete[] this->data_;
        }            
    }
    explicit TVector(size_t newSize) : size_(newSize), capacity_(newSize * 2) 
    {
        this->data_ = new T[this->capacity_];
    }
    explicit TVector(size_t newSize, const T& defaultValue) : TVector(newSize) 
    {
        for (size_t i = 0; i < this->size_; ++i)
        {
            this->data_[i] = defaultValue;
        }
    }
    TVector(std::initializer_list<T> initList) : TVector(initList.size()) 
    {
        size_t i = 0;
        auto current = initList.begin();
        const auto end = initList.end();
        while (current != end)
        {
            this->data_[i++] = *current++;
        }
    }    
    TVector(const TVector& vector) : TVector()
    {
        *this = vector;
    }
    TVector(TVector&& vector) : TVector()
    {
        *this = vector;
    }
    iterator begin() noexcept
    {
        return iterator(this->data_);
    }
    const_iterator cbegin() const noexcept
    {
        return const_iterator(this->data_);
    }
    iterator end() noexcept
    {
        return iterator(this->data_ + this->size_);
    }
    const_iterator cend() const noexcept
    {
        return const_iterator(this->data_ + this->size_);
    }
    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(this->data_ + this->size_ - 1);
    }
    const_reverse_iterator crbegin() const noexcept
    {
        return const_reverse_iterator(this->data_ + this->size_ - 1);
    }
    reverse_iterator rend() noexcept
    {
        return reverse_iterator(this->data_ - 1);
    }
    const_reverse_iterator crend() const noexcept
    {
        return const_reverse_iterator(this->data_ - 1);
    }
    T& operator[](size_t pos) 
    {
        return this->data_[pos];
    }
    const T& operator[](size_t pos) const 
    {
        return this->data_[pos];
    }
    TVector& operator=(const TVector& vector) 
    {
        if (vector.data_ != this->data_ || vector.size_ > this->size_) 
        {
            if (this->data_ != nullptr) 
            {
                delete[] this->data_;
            }
            this->size_ = vector.size_;
            this->capacity_ = vector.capacity_;
            this->data_ = new T[this->capacity_];
        }
        for (size_t i = 0; i < this->size_; ++i) 
        {
            this->data_[i] = vector.data_[i];
        }
        return *this;
    }
    TVector& operator=(TVector&& vector) 
    {
        if (this->data_ != nullptr) 
        {
            delete[] this->data_;    
        }
        this->data_ = std::move(vector.data_);
        this->size_ = vector.size_;
        this->capacity_ = vector.capacity_;
        vector.data_ = nullptr;
        vector.size_ = vector.capacity_ = 0;
        return *this;
    }
    void push_back(const T& addedValue) 
    {
        if (this->data_ == nullptr) 
        {
            *this = std::move(TVector(16));
            this->size_ = 0;
        }
        if (this->size_ == this->capacity_) 
        {
            auto vec = std::move(*this);
            this->resize(this->size_);            
            for (size_t i = 0; i < this->size_; ++i) 
            {
                this->data_[i] = vec[i];
            }
        }
        this->data_[this->size_++] = addedValue;
    }
    void pop_back() 
    {
        if (this->size_ == 1) 
        {
            this->clear();
        }    
        if (this->size_ > 1) 
        {
            this->size_--;
        }
    }
    size_t size() const noexcept 
    {
        return this->size_;
    }  
    bool empty() const noexcept
    {
        return this->size_ == 0;
    }
    void clear()
    {
        *this = std::move(TVector());
    }
    void resize(size_t newSize)
    {
        *this = std::move(TVector(newSize));
    }
    void resize(size_t newSize, const T& defaultValue)
    {
        *this = std::move(TVector(newSize, defaultValue));
    }
    const T* data() const 
    {
        return this->data_;
    }
    friend std::ostream& operator<<(std::ostream& out, const TVector<T>& vector) 
    {
        for (auto x : vector) 
        {
            out << x << " ";
        }
        out << "\n*************************************";
        return out;
    }
};