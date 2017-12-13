#include <iostream>
#include <string>
#include <memory>
#include <initializer_list>

using namespace std;
template <class t>
class Iterator{
private:
	t* ptr;

public:
	Iterator(t* ptr_old) :ptr(ptr_old){}

	t& operator*() const{
		return *ptr;
	}

	bool operator==(const Iterator& right) const{
		return right.ptr == ptr;
	}
	
	bool operator!=(const Iterator& right) const{
		return !(*this == right);
	}
	
	Iterator& operator++(){
		ptr++;
		return *this;
	}
	
	Iterator& operator++(int){
		ptr++;
		return *this;
	}

	Iterator& operator--(){
		ptr--;
		return *this;
	}
	
	Iterator& operator--(int){
		ptr--;
		return *this;
	}
	
	Iterator& operator+ (size_t len){
		ptr += len;
		return *this;
	}
	
	Iterator& operator- (size_t len){
		ptr -= len;
		return *this;
	}
};

template <class t>
class Reverse_iterator{
private:
	t* ptr;

public:
	Reverse_iterator(t* ptr_old) :ptr(ptr_old){}
	
	bool operator==(const Reverse_iterator& right) const{
		return right.ptr == ptr;
	}
	
	bool operator!=(const Reverse_iterator& right) const{
		return !(*this == right);
	}

	t& operator*() const{
		return *ptr;
	}
	
	Reverse_iterator& operator++(){
		ptr--;
		return *this;
	}
	
	Reverse_iterator& operator++(int){
		ptr--;
		return *this;
	}

	Reverse_iterator& operator--(){
		ptr++;
		return *this;
	}	
	
	Reverse_iterator& operator--(int){
		ptr++;
		return *this;
	}
	Reverse_iterator& operator+ (size_t len){
		ptr -= len;
		return *this;
	}
	
	Reverse_iterator& operator- (size_t len){
		ptr += len;
		return *this;
	}
};

template <class t>
class MyVector
{
private:

	unique_ptr<t[]> vect_;
	size_t size_;
	size_t capacity_;
public:

	using iterator = Iterator<t>;
	using const_iterator = Iterator<const t>;

	using reverse_iterator = Reverse_iterator<t>;
	using const_reverse_iterator = Reverse_iterator<const t>;


	MyVector(initializer_list<t> init):size_(init.size()),capacity_(init.size()){
		vect_ = make_unique<t[]>(size_);
		copy(init.begin(), init.end(), vect_.get());
	}

	MyVector(const MyVector& copied):size_(copied.size_),capacity_(copied.capacity_){
		vect_ = make_unique<t[]>(capacity_);
		copy(copied.vect_.get(), copied.vect_.get()+size_, vect_.get());
	}

	MyVector(size_t size = 0):size_(size),capacity_(size){
		vect_ = make_unique<t[]>(size_);
	}

	~MyVector(){
		size_ = 0;
		capacity_ = 0;
	}

	void clear(){
		vect_.reset();
		size_ = 0;
		capacity_ = 0;
	}

	void resize(int new_size){
		if (new_size < 0){
			throw runtime_error("MyVector size can't be less than zero");
		}
		if (new_size > capacity_){
			reshape(new_size);
		}
		size_ = new_size;
	}

	void resize(size_t new_size, t default_val){
		size_t old_size = size_;
		resize(new_size);
		for (size_t i = old_size; i < size_; i++){
			vect_[i] = default_val;
		}
	}

	void reshape(size_t new_capacity)
	{
		if (new_capacity < size_){
			throw runtime_error("You loss data. New capacity is less than old");
		}
		if (new_capacity == capacity_){
			return;
		}

		auto tmp = make_unique<t[]>(new_capacity);
		copy(vect_.get(), vect_.get() + size_, tmp.get());
		vect_ = move(tmp);
		capacity_ = new_capacity;
	}

	constexpr size_t size() const noexcept{
		return size_;
	}

	constexpr size_t capacity() const noexcept{
		return capacity_;
	}

	constexpr bool empty() const noexcept{
		if (size_ == 0)	return true;
		else return false;
	}

	t& get_elem(size_t pos){
		if (pos >= size_){
			throw runtime_error("MyVector out of range");
		}
		return vect_[pos];
	}

	t& operator[](size_t pos) {
		if ((pos >= size_) || (pos < 0)){
			throw runtime_error("MyVector out of range");
		}
		return vect_[pos];
	}

	void push_back(const t& buf){
		if (capacity_ == size_){
			if (capacity_ == 0) reshape(1);
			else reshape(size_ * 2);
		}
		vect_[size_] = buf;
		size_++;
	}

	void pop_back(){
		if (size_ < 1){
			throw runtime_error("MyVector is empty");
		}
		vect_[size_ - 1] = 0;
		size_--;
	}

	iterator begin() const{
		return iterator(vect_.get());
	}
	
	iterator end() const{
		return iterator(vect_.get() + size_);
	}

	reverse_iterator rbegin() const{
		return reverse_iterator(vect_.get() + size_ - 1);
	}
	
	reverse_iterator rend() const{
		return reverse_iterator(vect_.get() - 1);
	}
	
	void print(){
		for (size_t i = 0; i < size_; i++) cout << vect_[i] << " ";
		cout << endl;
	}
};


int main()
{
	//MyVector creation	
	cout<<"Initialization MyVector"<<endl;
	MyVector<int> a = { 1,1,1,1,1 };
	a.print();
	cout<<"Resize MyVector"<<endl;
	a.resize(6,2);
	a.print();
	
	cout<<"Clear MyVector"<<endl;
	a.clear();
	a.resize(5);
	a.print();
	cout<<"Get elements"<<endl;
	a[0] = 1;
	a.get_elem(1) = 2;
	a.print();

	cout<<"Iterators"<<endl;
	MyVector<int> b = {10,20};
	for(auto it = b.begin(); it != b.end(); it++){
		*it *= 2;
	}
	b.print();
	return 0;
}
