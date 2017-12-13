// Vasilii Bodnariuk

#include <memory>
#include <cstddef>
#include <algorithm>
#include <exception>
#include <iterator>

using namespace std;

template <typename T>
class Vector {
private:
    unique_ptr<T[]> elements;
    size_t located_size;
    size_t used_size;
    size_t extending_size = 10;

    void construct(size_t size);
    void locate(size_t size);

public:
    void test();
    Vector(size_t size = 0);
    Vector(size_t size, T default_elem);

    size_t size();
    bool empty();
    void clear();
    void resize(size_t new_size);
    void resize(size_t new_size, T val);
    T& operator[](size_t i);
    void push_back(T val);
    void pop_back();

    template <typename T_ref>
    class iterator : public std::iterator<std::forward_iterator_tag, T> {
    public:
        iterator(T* pointer) {
            p = pointer;
        }

        bool operator!=(const iterator& other) const {
            return !(p == other.p);
        }

        T_ref operator*() const {
            return *p;
        }


        iterator<T_ref>& operator++() {
            ++p;
            return *this;
        }

    protected:
        T* p;
    };

    template <typename T_ref>
    class reverse_iterator : public std::iterator<std::forward_iterator_tag, T> {
    public:
        reverse_iterator(T* pointer) {
            p = pointer;
        }

        bool operator!=(const reverse_iterator& other) const {
            return !(p == other.p);
        }

        T_ref operator*() const {
            return *p;
        }


        reverse_iterator<T_ref>& operator++() {
            --p;
            return *this;
        }

    protected:
        T* p;
    };

    iterator<T&> begin();
    iterator<T&> end();

    reverse_iterator<T&> rbegin();
    reverse_iterator<T&> rend();

};

template<typename T>
Vector<T>::Vector(size_t size) {
    construct(size);
}

template<typename T>
Vector<T>::Vector(size_t size, T default_elem) {
    construct(size);
    for(size_t i = 0; i < used_size; ++i) {
        elements[i] = default_elem;
    }
}

template<typename T>
void Vector<T>::construct(size_t size) {
    located_size = max(extending_size, size);
    elements = make_unique<T[]>(located_size);
    used_size = size;
}

template<typename T>
size_t Vector<T>::size() {
    return used_size;
}

template<typename T>
bool Vector<T>::empty() {
    return size() == 0;
}

template<typename T>
void Vector<T>::clear() {
    construct(0);
}

template<typename T>
void Vector<T>::locate(size_t new_size) {
    auto old_elements(std::move(elements));
    elements = make_unique<T[]>(new_size);
    for(size_t i = 0; i < used_size; ++i) {
        elements[i] = old_elements[i];
    }
    located_size = new_size;
}

template<typename T>
void Vector<T>::resize(size_t new_size) {
    if(new_size > located_size) {
        locate(new_size);
    }
    used_size = new_size;
}

template<typename T>
void Vector<T>::resize(size_t new_size, T val) {
    auto old_size = used_size;
    resize(new_size);
    for(size_t i = old_size; i < new_size; ++i) {
        elements[i] = val;
    }
}

template<typename T>
T& Vector<T>::operator[](size_t i) {
    if(i < used_size) {
        return elements[i];
    } else {
        throw range_error("index out of range");
    }
}

template<typename T>
void Vector<T>::push_back(T val) {
    if(located_size == used_size) {
        locate(located_size + extending_size);
    }

    elements[used_size] = val;
    ++used_size;
}

template<typename T>
void Vector<T>::pop_back() {
    if(used_size > 0) {
        --used_size;
    } else {
        throw range_error("trying to pop_back an empty vector");
    }
}

template<typename T>
Vector<T>::iterator<T&> Vector<T>::begin() {
    return iterator<T&>(elements.get());
}

template<typename T>
Vector<T>::iterator<T&> Vector<T>::end() {
    return iterator<T&>(elements.get() + used_size);
}

template<typename T>
Vector<T>::reverse_iterator<T&> Vector<T>::rbegin() {
    return reverse_iterator<T&>(elements.get() + used_size - 1);
}

template<typename T>
Vector<T>::reverse_iterator<T&> Vector<T>::rend() {
    return reverse_iterator<T&>(elements.get() - 1);
}
