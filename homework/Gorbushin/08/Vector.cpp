#include <stddef.h>
#include <cstring>
#include <iostream>
using namespace std;

// Базовый класс итератора
template <typename T>
class BaseVectorIterator {
public:
    using value_type = T;
    using reference = T&;

    // Конструктор от указателя на тип T
    BaseVectorIterator (value_type* p): _pointer(p) {}
    
    // Равенство итераторов
    bool operator == (const BaseVectorIterator & other) {
        return _pointer == other._pointer;
    }

    bool operator != (const BaseVectorIterator & other) {
        return _pointer != other._pointer;
    }

    // Разыменовывание итератора
    reference operator * () const {
        return *_pointer;
    }
protected:
    T* _pointer;
};

// Класс итератор
template <typename T>
class VectorIterator : public BaseVectorIterator<T> {
public:
    using value_type = T;
    using reference = T&;
    using Base = BaseVectorIterator<T>;

    // Конструктор, вызываем родителя
    VectorIterator(value_type* p): Base(p) {}

    // операции с итератором
    VectorIterator& operator ++ () {
        ++Base::_pointer;
        return *this;
    }

    VectorIterator& operator -- () {
        --Base::_pointer;
        return *this;
    }

    VectorIterator operator ++(int) {
        VectorIterator tmp = *this;
        ++Base::_pointer;
        return tmp;
    }

    VectorIterator operator --(int) {
        VectorIterator tmp = *this;
        --Base::_pointer;
        return tmp;
    }

    VectorIterator operator + (int step) {
        return VectorIterator(Base::_pointer + step);
    }

    friend VectorIterator operator + (int step, const VectorIterator & iterator) {
        return VectorIterator(iterator.Base::_pointer + step);
    }

    VectorIterator operator - (int step) {
        return VectorIterator(Base::_pointer - step);
    }

    friend VectorIterator operator - (int step, const VectorIterator & iterator) {
        return VectorIterator(iterator.Base::_pointer - step);
    }

    // обращение к итератору, по индексу
    value_type& operator[] (int index) {
        return *(Base::_pointer + index);
    }

    const value_type operator[] (int index) const {
        return *(Base::_pointer + index);
    }
};

// Класс reverse итератора
template <typename T>
class ReverseVectorIterator : public BaseVectorIterator<T> {
public:
    using value_type = T;
    using reference = T&;
    using Base = BaseVectorIterator<T>;

    // Конструктор, вызываем родителя
    ReverseVectorIterator(value_type* p): Base(p) {}

    // операции с итератором
    ReverseVectorIterator& operator -- () {
        ++Base::_pointer;
        return *this;
    }

    ReverseVectorIterator& operator ++ () {
        --Base::_pointer;
        return *this;
    }

    ReverseVectorIterator operator --(int) {
        ReverseVectorIterator tmp = *this;
        ++Base::_pointer;
        return tmp;
    }

    ReverseVectorIterator operator ++(int) {
        ReverseVectorIterator tmp = *this;
        --Base::_pointer;
        return tmp;
    }

    ReverseVectorIterator operator - (int step) {
        return ReverseVectorIterator(Base::_pointer + step);
    }

    friend ReverseVectorIterator operator - (int step, const ReverseVectorIterator & iterator) {
        return ReverseVectorIterator(iterator.Base::_pointer + step);
    }

    ReverseVectorIterator operator + (int step) {
        return ReverseVectorIterator(Base::_pointer - step);
    }

    friend ReverseVectorIterator operator + (int step, const ReverseVectorIterator & iterator) {
        return ReverseVectorIterator(iterator.Base::_pointer - step);
    }

    // обращение к итератору, по индексу
    value_type& operator[] (int index) {
        return *(Base::_pointer - index);
    }

    const value_type operator[] (int index) const {
        return *(Base::_pointer - index);
    }
};

// Класс вектор
template <typename T>
class Vector {
public:
    using value_type = T;
    using iterator = VectorIterator<T>;
    using reverse_iterator = ReverseVectorIterator<T>;
    
    // Пустой конструктор
    Vector(): _data(nullptr), _size(0), _capacity(0) {}

    // Конструктор от кол-ва элементов
    explicit Vector(size_t size): _size(0), _capacity(size) {
        _data = std::unique_ptr<value_type[]>(new value_type[size]);
    }

    // Конструтор с дефолтной инициализацией
    Vector(size_t size, const value_type& defaultValue): _size(size), _capacity(size) {
        _data = std::unique_ptr<value_type[]>(new value_type[size]);
        for (size_t i = 0; i < size; i++) {
            _data[i] = defaultValue;
        }
    }

    // Конструктор копирования
    Vector(const Vector<value_type>& from) {
        _size = from._size;
        _capacity = from._capacity;
        _data = std::unique_ptr<value_type[]>(new value_type[_capacity]);
        std::memcpy(_data.get(), from._data.get(), _size * sizeof(value_type));
    }

    // Оператор присваивания
    Vector& operator=(const Vector<value_type>& from) {
        if (this == &from)
            return *this;

        _size = from._size;
        _capacity = from._capacity;
        _data = nullptr;
        _data = std::unique_ptr<value_type[]>(new value_type[_capacity]);
        std::memcpy(_data.get(), from._data.get(), _size * sizeof(value_type));
    }

    // Конструктор перемещения
    Vector (Vector<value_type> && from) {
        _size = from._size;
        _capacity = from._capacity;
        _data = std::move(from);

        from._size = 0;
        from._capacity = 0;
        from._data = nullptr;

        return *this;
    }

    // Присваивание с rvalue
    Vector& operator=(Vector<value_type> && from) {
        if (this == &from)
            return *this;

        _size = from._size;
        _capacity = from._capacity;
        _data = std::move(from._data);
     
        from._size = 0;
        from._capacity = 0;
        from._data = nullptr;

        return *this;   
    }

    // обращение по индексу
    T& operator[] (int index) {
        if (index < 0 || index >= _size)
        	throw std::out_of_range(std::to_string(index)); 
		
		return _data[index];
    }

	const T operator[] (int index) const {
        if (index < 0 || index >= _size)
        	throw std::out_of_range(std::to_string(index)); 
		
		return _data[index];
    }

    // итераторы на начало, конец и reverse итераторы
    iterator begin() {
        return iterator(_data.get());
    }

    iterator end() {
        return iterator(_data.get() + _size);
    }

    reverse_iterator rbegin() {
        if (_size == 0)
            return reverse_iterator(_data.get());

        return reverse_iterator(_data.get() + _size - 1);
    }

    reverse_iterator rend() {
        if (_size == 0)
            return reverse_iterator(_data.get());

        return reverse_iterator(_data.get() - 1);
    }

    // добавляет элемент в конец массива
    void push_back(const T & to_push) {
        if (_size == _capacity) {
            _capacity = _capacity ? 2 * _capacity : 1;
            auto tmp_data = std::unique_ptr<value_type[]>(new value_type[_capacity]);
            std::memcpy(tmp_data.get(), _data.get(), _size * sizeof(value_type));
            _data = std::move(tmp_data);
        }
            
        _data[_size] = to_push;
        _size++;
    }

    // удаляет последний элемент
    void pop_back() {
        if (_size != 0) 
            _size--; 
    }
   
    // проверяет массив на пустоту
    bool empty() const {
        return _size == 0;   
    }

    // возвращает размер массива
    size_t size() const {
        return _size;
    }

    // очищает память
    void clear() {
        _data = nullptr;
        _size = 0;
        _capacity = 0;
    }
    
    /*  изменяет размер массива, если новый размер больше старого,
        то старые элементы копируются, новые заполняются мусором,
        если наоборот старые элемент, которые вмещаются копирются, другие
        очищаются
    */
    void resize(size_t new_size) {
        auto tmp_data = std::unique_ptr<value_type[]>(new value_type[new_size]);
        if (new_size < _size) {
            std::memcpy(tmp_data.get(), _data.get(), new_size * sizeof(value_type));
        } else if (_data) {
            std::memcpy(tmp_data.get(), _data.get(), _size * sizeof(value_type));
        }

        _data = std::move(tmp_data);
        _size = new_size;
        _capacity = new_size;
    }

private:
    std::unique_ptr<value_type[]> _data;
    size_t _size;
    size_t _capacity;
};
