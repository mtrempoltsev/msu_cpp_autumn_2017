#include <iostream>

template <class T>
struct UniquePtr
{
    T* data_;
public:
    explicit UniquePtr(T* data)
        : data_(data)
    {
    }

    ~UniquePtr()
    {
        std::cout << "   ~UniquePtr\n";
        std::cout << data_ << std::endl;
        delete data_;
    }

    UniquePtr(const UniquePtr&) = delete;
    
    UniquePtr(UniquePtr&& movied)
    {
        data_ = movied.data_;
        movied.data_ = nullptr;
    }

    UniquePtr& operator=(const UniquePtr& copied) = delete;
    
    UniquePtr& operator=(UniquePtr&& movied)
    {
        delete data_;
        data_ = movied.data_;
        movied.data_ = nullptr;
        return *this;
    }
};

struct A
{
    A() { std::cout << "    A\n"; }
    ~A() { std::cout << "    ~A\n"; }
};

int main()
{
    A* a = new A();
    UniquePtr<A> x(a);
    UniquePtr<A> y(new A());
    y = std::move(x);
}
