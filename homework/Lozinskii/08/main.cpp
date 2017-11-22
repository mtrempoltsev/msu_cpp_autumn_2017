#include <iostream>
#include <cstring>

template <class T>
class Iterator
{
    T* ptr_;
    bool reversed_;
public:
    using reference = T&;

    Iterator(T* ptr, bool reversed = false)
        : ptr_(ptr), reversed_(reversed)
    {
    }

    bool operator==(const Iterator<T>& other) const
    {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Iterator<T>& other) const
    {
        return !(*this == other);
    }

    reference operator*() const
    {
        return *ptr_;
    }

    Iterator& operator++()
    {
        if (reversed_)
            --ptr_;
        else
            ++ptr_;
        return *this;
    }
    Iterator& operator--()
    {
        if (reversed_)
            ++ptr_;
        else
            --ptr_;
        return *this;
    }
    Iterator operator++(int)
    {
        Iterator<T> a = *this;
        if (reversed_)
            --ptr_;
        else
            ++ptr_;
        return a;
    }
    Iterator operator--(int)
    {
        Iterator<T> a = *this;
        if (reversed_)
            ++ptr_;
        else
            --ptr_;
        return a;
    }

};

template <class T, class Alloc = std::allocator<T>>
class Vector {
    T *arr;
    Alloc alloc;
    size_t len;
    size_t vsize;
public:
    Vector(size_t _size, const Alloc &a = Alloc()) {
        len = _size;
        vsize = _size;
        arr = alloc.allocate(vsize);
    }
    T& operator[](size_t i) {
        if (i < len)
            return arr[i];
        else
            throw std::out_of_range("Range exception");
    }
    void push_back(T a) {
        if (len == vsize) {
            this->resize(vsize * 2);
        }
        arr[len++] = a;
    }
    T pop_back() {
        if (len > 0) {
            len--;
            return arr[len];
        }
        else 
            throw std::out_of_range("Range exception");
    }
    bool empty() {
        return len > 0;
    }
    size_t size() {
        return len;
    }
    void clear() {
        len = 0;
    }
    Iterator<T> begin() {
        return Iterator<T>(arr);
    } 
    const Iterator<T> end() {
        return Iterator<T>(arr + len);
    }
    Iterator<T> rbegin() {
        return Iterator<T>(arr + (len - 1), true);
    }
    const Iterator<T> rend() {
        return Iterator<T>(arr - 1);
    }
    void resize(size_t n_size) { 
        T* arr1 = alloc.allocate(n_size);
        for (size_t i = 0; i < std::min(len, n_size); i++) {
            arr1[i] = std::move(arr[i]);
        }
        len = std::min(len, n_size);
        alloc.deallocate(arr, vsize);
        arr = arr1;
        vsize = n_size;
    }
    ~Vector() {
        alloc.deallocate(arr, vsize);
    }
};

void check(bool s, std::string a = "Error") {
    if (!s)
        std::cout << a  << std::endl;
}

void test_simple() {
    Vector<int> v = Vector<int>(3);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;
    
    check(v[0] == 1, "s1");
    check(v[1] == 2, "s2");
    check(v[2] == 3, "s3");
}

void test_push_pop() {
    Vector<int> v = Vector<int>(3);
    v[0] = 1;
    v[1] = 2;
    v.push_back(4);
    v.push_back(5);
    
    check(v[0] == 1, "pp1");
    check(v[1] == 2, "pp2");
    check(v[3] == 4, "pp3");
    check(v[4] == 5, "pp4");
    
    check(v.pop_back() == 5, "pp5");
    check(v[3] == 4, "pp6");

}

void test_iterator() { 
    Vector<int> v = Vector<int>(3);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;
    v.push_back(4);
    v.push_back(5);

    Iterator<int> ii = v.begin();
    Iterator<int> ie = v.end();
    for (size_t i = 0; i < v.size(); i++, ii++) {
        check(*ii == v[i], "iterator value error");
        check(ii != ie, "iterator end error");
    }

    ii = v.rbegin();
    ie = v.rend();
    for (size_t i = 0; i < v.size(); i++, ii++) {
        check(*ii == v[v.size() - i - 1], "iterator value error");
        check(ii != ie, "iterator end error");
    }
}
int main(void) {
    test_simple();
    test_push_pop();
    test_iterator();
    return 0;
}
