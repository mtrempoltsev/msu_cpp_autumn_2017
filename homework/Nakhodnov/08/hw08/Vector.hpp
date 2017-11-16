#ifndef __VECTORHPP__
#define __VECTORHPP__

#include <memory>

/*
    Набор классов итераторов вектор
*/
/*
    Итератор произвольного доступа
*/
template <typename _T>
class RandomAccessIterator {
public:

    RandomAccessIterator() {};

    RandomAccessIterator(_T *begin, _T *end, off_t off) : _MyBeg(begin), _MyEnd(end), _MyIter(begin) {
        this->operator+=(off);
    }

    RandomAccessIterator& operator+=(off_t off) {
        if (this->_MyBeg == this->_MyEnd ||
            this->_MyEnd - this->_MyIter < off ||
            this->_MyBeg - this->_MyIter > off) {
            throw("iterator offset is out of range");
        }
        this->_MyIter += off;
        return *(this);
    }

    RandomAccessIterator& operator-=(off_t off) {
        return this->operator+=(-off);
    }

    RandomAccessIterator operator+(off_t off) const {
        if (this->_MyBeg == this->_MyEnd ||
            this->_MyEnd - this->_MyIter < off ||
            this->_MyBeg - this->_MyIter > off) {
            throw("iterator offset is out of range");
        }
        return RandomAccessIterator(this->_MyIter + off, this->_MyBeg, this->_MyEnd);
    }

    RandomAccessIterator operator-(off_t off) const {
        return this->operator+(off);
    }

    RandomAccessIterator& operator++() {
        return this->operator+=(1);
    }

    RandomAccessIterator operator++(int) {
        RandomAccessIterator tmp = *this;
        this->operator+=(1);
        return tmp;
    }

    RandomAccessIterator& operator--() {
        return this->operator-=(1);
    }

    RandomAccessIterator& operator--(int) {
        RandomAccessIterator tmp = *this;
        this->operator-=(1);
        return tmp;
    }

    ptrdiff_t operator-(const RandomAccessIterator& Iter) {
        return (this->_MyIter - Iter->_MyIter);
    }


    _T& operator[](size_t off) {
        return *(this->operator+(off)->_MyIter);
    }

    const _T& operator[](size_t off) const {
        return *(this->operator+(off)->_MyIter);
    }

    _T& operator*() {
        if (this->_MyIter == this->_MyEnd) {
            throw("iterator get out of range");
        }
        return *(this->_MyIter);
    }

    _T * operator->() {
        if (this->_MyIter == this->_MyEnd) {
            throw("iterator get out of range");
        }
        return (std::pointer_traits<_T *>::pointer_to(*this->_MyIter));
    }

    const _T& operator*() const {
        if (this->_MyIter == this->_MyEnd) {
            throw("iterator get out of range");
        }
        return *(this->_MyIter);
    }

    const _T * operator->() const {
        if (this->_MyIter == this->_MyEnd) {
            throw("iterator get out of range");
        }
        return (std::pointer_traits<const _T *>::pointer_to(*this->_MyIter));
    }


    bool operator==(const RandomAccessIterator& Iter) const {
        return (this->_MyIter == Iter._MyIter);
    }

    bool operator!=(const RandomAccessIterator& Iter) const {
        return !(this->_MyIter == Iter._MyIter);
    }

    bool operator<(const RandomAccessIterator& Iter) const {
        return ((Iter - *this) < 0);
    }

    bool operator>(const RandomAccessIterator& Iter) const {
        return !(Iter < *this);
    }

    bool operator<=(const RandomAccessIterator& Iter) const {
        return ((Iter - *this) <= 0);
    }

    bool operator>=(const RandomAccessIterator& Iter) const {
        return !(Iter <= *this);
    }

protected:
    _T *_MyBeg, *_MyEnd, *_MyIter;
};

/*
    Инкремантальный двунаправленный итератор
*/
template <typename _T>
class BiDirectionalIterator :
    public RandomAccessIterator<_T> {
public:

    BiDirectionalIterator() {};

    BiDirectionalIterator(_T *begin, _T *end, off_t off) : RandomAccessIterator<_T>(begin, end, off) {};

    RandomAccessIterator<_T>& operator+=(size_t off) = delete;

    RandomAccessIterator<_T>& operator-=(size_t off) = delete;

    RandomAccessIterator<_T> operator+(size_t off) = delete;

    RandomAccessIterator<_T> operator+(size_t off) const = delete;

    RandomAccessIterator<_T> operator-(size_t off) = delete;

    RandomAccessIterator<_T> operator-(size_t off) const = delete;

    _T& operator[](size_t off) = delete;

    const _T& operator[](size_t off) const = delete;
};

/*
    Однонаправленный итератор   
*/
template <typename _T>
class ForwardIterator :
    public BiDirectionalIterator<_T> {
public:

    ForwardIterator(_T *begin, _T *end, off_t off) : BiDirectionalIterator<_T>(begin, end, off) {};

    BiDirectionalIterator<_T>& operator--() = delete;

    BiDirectionalIterator<_T> operator--(int) = delete;

};

/*
    Однонаправленный обратный итератор
*/
template <typename _T>
class ReverseIterator :
    public BiDirectionalIterator<_T> {
public:

    ReverseIterator() {};

    ReverseIterator(_T *begin, _T *end, off_t off) {
        if (end - begin < off) {
            throw("iterator get out of range");
        }
        this->_MyBeg = end;
        this->_MyEnd = begin;
        this->_MyIter = end - off;
    };

    ReverseIterator& operator++() {
        if (this->_MyIter == this->_MyEnd) {
            throw("iterator get out of range");
        }
        this->_MyIter -= 1;
        return *this;
    }

    ReverseIterator operator++(int) {
        if (this->_MyIter == this->_MyEnd) {
            throw("iterator get out of range");
        }
        this->_MyIter -= 1;
        return ReverseIterator(this->_MyBeg, this->_MyEnd, this->_MyIter + 1);
    }

    RandomAccessIterator<_T>& operator--() = delete;

    RandomAccessIterator<_T> operator--(int) = delete;

    _T& operator*() {
        if (this->_MyIter == this->_MyEnd) {
            throw("iterator get out of range");
        }
        return *(this->_MyIter - 1);
    }

    _T * operator->() {
        if (this->_MyIter == this->_MyEnd) {
            throw("iterator get out of range");
        }
        return (std::pointer_traits<_T *>::pointer_to(*(this->_MyIter - 1)));
    }

    const _T& operator*() const {
        if (this->_MyIter == this->_MyEnd) {
            throw("iterator get out of range");
        }
        return *(this->_MyIter - 1);
    }

    const _T * operator->() const {
        if (this->_MyIter == this->_MyEnd) {
            throw("iterator get out of range");
        }
        return (std::pointer_traits<const _T *>::pointer_to(*(this->_MyIter - 1)));
    }

};


/*
    Класс-вектор
*/
template <typename _T, typename _Alloc = std::allocator<_T>>
class Vector {
public:

    Vector() {
        this->_data = nullptr;
        this->_size = this->_capacity = 0;
    }

    Vector(size_t N) {
        this->_size = N;
        this->_capacity = this->_Impove_Size(N);
        this->_data = this->_alloc.allocate(this->_capacity);
    }

    Vector(size_t N, _T val) {
        this->_size = N;
        this->_capacity = this->_Impove_Size(N);
        this->_data = this->_alloc.allocate(this->_capacity);
        for (size_t i = 0; i < N; ++i) {
            _data[i] = val;
        }
    }

    void resize(size_t size, const _T& val = _T()) {
        if (size < this->_capacity) {
            this->_size = size;
            return;
        }
        this->_capacity = this->_Impove_Size(size);
        _T *new_data = this->_alloc.allocate(this->_capacity);
        for (size_t i = 0; i < size; ++i) {
            if (i < this->_size) {
                new_data[i] = this->_data[i];
            }
            else {
                new_data[i] = val;
            }
        }
        this->_alloc.deallocate(this->_data, this->_capacity);
        this->_size = size;
        this->_data = new_data;
    }
    
    void push_back(const _T& val) {
        size_t old_size = this->_size;
        if (this->_size + 1 > this->_capacity) {
            this->resize(this->_Impove_Size(this->_capacity));
        }
        this->_data[old_size] = val;
        this->_size = old_size + 1;
    }

    void push_back(_T&& val) {
        size_t old_size = this->_size;
        if (this->_size + 1 > this->_capacity) {
            this->resize(this->_Impove_Size(this->_capacity));
        }
        this->_data[old_size] = std::move(val);
        this->_size = old_size + 1;
    }

    void pop_back() {
        if (this->_size == 0) {
            throw("vector is out of range");
        }
        --this->_size;
    }

    const _T& operator[](size_t off) const {
        if (off < 0 || off > this->_size) {
            throw("vector is out of range");
        }
        return this->_data[off];
    }

    _T& operator[](size_t off) {
        if (off < 0 || off > this->_size) {
            throw("vector is out of range");
        }
        return this->_data[off];
    }

    void clear() {
        this->_size = 0;
    }

    ForwardIterator<_T> begin(){
        return ForwardIterator<_T>(this->_data, this->_data + this->_size, 0);
    }

    ForwardIterator<_T> end() {
        return ForwardIterator<_T>(this->_data, this->_data + this->_size, this->_size);
    }

    ReverseIterator<_T> rbegin() {
        return ReverseIterator<_T>(this->_data, this->_data + this->_size, 0);
    }

    ReverseIterator<_T> rend() {
        return ReverseIterator<_T>(this->_data, this->_data + this->_size, this->_size);
    }

    bool empty() {
        return (this->_size == 0);
    }

    size_t capacity() const {
        return this->_capacity;
    }

    size_t size() const {
        return this->_size;
    }


private:
    size_t _size, _capacity;
    _T *_data;
    _Alloc _alloc;

    size_t _Impove_Size(size_t size) {
        return 2 * size + 1;
    }


};


#include "Vector.cpp"

#endif
