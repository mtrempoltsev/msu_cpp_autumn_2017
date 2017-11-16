#pragma once 
#include <iterator>
using namespace std;

////FORWARD ITERATOR
template<class T>
class fwdIter:
        public std::iterator<forward_iterator_tag, T>
    {
    public:
    using size_type = size_t;
    using value_type = T;
        fwdIter(){
        }
        fwdIter(T* data){
            it = data;
        }
        fwdIter(fwdIter&& copied){
            it = copied.it;
        }
        fwdIter operator=(fwdIter&& copied){
            it = copied.it;
        }
        fwdIter& operator++() {
            ++it;
            return *this;
        }
        fwdIter& operator--() {
            --it;
            return *this;
        }
        fwdIter operator++(int) {
            fwdIter tmp(*this); 
            operator++(); 
            return tmp;
        }
        fwdIter operator--(int) {
            fwdIter tmp(*this); 
            operator--(); 
            return tmp;
        }
        bool operator==(fwdIter rval){
            return it == rval.it;
        }
        bool operator!=(fwdIter rval){
            return it != rval.it;
        }
        bool operator>(fwdIter rval){
            return it > rval.it;
        }

        bool operator<(fwdIter rval){
            return it < rval.it;
        }
        fwdIter operator+(size_type count) {
            fwdIter tmp(*this);
            tmp.it += count;
            return tmp;
        }
        fwdIter operator-(size_type count) {
            fwdIter tmp(*this);
            tmp.it -= count;
            return tmp;
        }
        fwdIter& operator+=(size_type count) {
            it += count;
            return (*this);
        }
        fwdIter& operator-=(size_type count) {
            it -= count;
            return (*this);
        }
        value_type& operator*(){
            return *it;
        }
        ~fwdIter(){};
    private:
        value_type* it;
    };


////REVERSE ITERATOR
template<class T>
class rvsIter:
        public std::iterator<reverse_iterator<T>, T>
    {
    public:
    using size_type = size_t;
    using value_type = T;
        rvsIter(){
        }
        rvsIter(T* data){
            it = data;
        }
        rvsIter(rvsIter&& copied){
            it = copied.it;
        }
        rvsIter operator=(rvsIter&& copied){
            it = copied.it;
        }
        rvsIter& operator++() {
            --it;
            return *this;
        }
        rvsIter& operator--() {
            ++it;
            return *this;
        }
        rvsIter operator++(int) {
            rvsIter tmp(*this); 
            operator++(); 
            return tmp;
        }
        rvsIter operator--(int) {
            rvsIter tmp(*this); 
            operator--(); 
            return tmp;
        }
        bool operator==(rvsIter rval){
            return it == rval.it;
        }
        bool operator!=(rvsIter rval){
            return it != rval.it;
        }
        bool operator>(rvsIter rval){
            return it < rval.it;
        }

        bool operator<(rvsIter rval){
            return it > rval.it;
        }
        rvsIter operator+(size_type count) {
            rvsIter tmp(*this);
            tmp.it -= count;
            return tmp;
        }
        rvsIter operator-(size_type count) {
            rvsIter tmp(*this);
            tmp.it += count;
            return tmp;
        }
        rvsIter& operator+=(size_type count) {
            it -= count;
            return (*this);
        }
        rvsIter& operator-=(size_type count) {
            it += count;
            return (*this);
        }
        value_type& operator*(){
            return *it;
        }
        ~rvsIter(){};
    private:
        value_type* it;
    };


////VECTOR

template<class T,
    class Alloc = std::allocator<T>>
class _vector
{
public:
    using size_type = size_t;
    using value_type = T;

    explicit _vector(const Alloc& a = Alloc()){
        data_ = Alloc(a).allocate(capacity);
        size_ = 0;
    }

    explicit _vector(size_type count, const Alloc& a = Alloc()){
        data_ = Alloc(a).allocate(capacity);
        size_ = count;
    }

    explicit _vector(size_type count, const value_type& defaultValue, const Alloc& a = Alloc()){
        data_ = Alloc(a).allocate(capacity);
        size_ = count;
        for(size_type i = 0; i < count; i++){
            *(data_ + i) = defaultValue;
        }

    }

    _vector(initializer_list<value_type> init, const Alloc& a = Alloc()){
        data_ = Alloc(a).allocate(capacity);
        size_ = init.size();
        size_t i = 0;
        auto current = init.begin();
        const auto end = init.end();
        while (current != end)
        {
            data_[i++] = *current++;
        }
    }

    void enlarge(const Alloc& a = Alloc()){
        T* tmpdata = Alloc(a).allocate(capacity * 2);
        memcpy(tmpdata, data_, sizeof(T) * capacity);
        data_ = Alloc(a).deallocate(capacity);
        data_ = tmpdata;
        capacity *= 2;
    }

    fwdIter<T> begin() noexcept{
        return fwdIter<T>(data_);
    }
    fwdIter<T> end() noexcept{
        return fwdIter<T>(data_ + size_);
    }

    rvsIter<T> rbegin() noexcept{
        return rvsIter<T>(data_ + size_ - 1);
    }

    rvsIter<T> rend() noexcept{
        return rvsIter<T>(data_ - 1);
    }

    value_type& operator[](size_type index){
        if(index >= size_){
            throw std::out_of_range("My error is here");
        }
        return *(data_ + index);
    }
    const value_type& operator[](size_type index) const{
        if(index >= size_){
            throw std::out_of_range("My error is here");
        }
        return *(data_ + index);
    }


    void push_back(value_type value){
        data_[size_++] = value;
    }

    size_type pop_back(){
        return data_[--size_];
    }

    const size_type size() const{
        return size_;
    }

    bool empty() const{
        return size_ == 0;
    }

    void clear(){
        size_ = 0;
    }

    void resize(size_type count){
        if(count > capacity){
            throw std::logic_error("Count > capacity");
        }
        size_ = count;
    }

    void resize(size_type count, const value_type& value){
        if(count > capacity){
            throw std::logic_error("Count > capacity");
        }
        if(count > size_){
            for(size_type i = size_; i < count; i++){
                data_[i] = value;
            }
        }
        size_ = count;
    }

    template<typename M>
    friend std::ostream& operator<<(std::ostream& out, const _vector<M>& value);
private:
    value_type* data_;
    size_type size_;
    const size_type capacity = 1024;
};




template<typename M>
std::ostream& operator<<(std::ostream& out, const _vector<M>& value) {
    const size_t sizeofvec = value.size();
    out << "size:" << sizeofvec  << std::endl;
    for (size_t i = 0; i < sizeofvec; i++) {
            out << value[i] << ' ';
    }
    std::cout << std::endl;
    return out;
}