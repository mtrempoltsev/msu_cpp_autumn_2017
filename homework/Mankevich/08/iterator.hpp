template <class T> 
class Iterator{
public:
    explicit Iterator(T* ptr): ptr_(ptr) {};
    bool operator==(const Iterator<T>& other){
        return ptr_ == other.ptr_;
    }
    bool operator!=(const Iterator<T>& other){
        return ptr_ != other.ptr_;
    }
    T& operator*(){
        return *ptr_;
    }
    Iterator<T>& operator++(){
        ++ptr_;
        return *this;
    }
private:
    T* ptr_;
};

template <class T> 
class ReverseIterator{
public:
    explicit ReverseIterator(T* ptr): ptr_(ptr) {};
    bool operator==(const ReverseIterator<T>& other){
        return ptr_ == other.ptr_;
    }
    bool operator!=(const ReverseIterator<T>& other){
        return ptr_ != other.ptr_;
    }
    T& operator*(){
        return *ptr_;
    }
    ReverseIterator<T>& operator++(){
        --ptr_;
        return *this;
    }
private:
    T* ptr_;
};