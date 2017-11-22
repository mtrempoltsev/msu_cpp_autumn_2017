#include <iostream>
#include <memory>
#include <cmath>
#include <assert.h>


//Iterator class
template<class T>
class iterator{
public:
	iterator(T* p){
		ptr = p;
	}

	bool operator==(const iterator<T>& other){
		return ptr == other.ptr;
	}

	bool operator!=(const iterator<T>& other){
		return ptr != other.ptr;
	}

	T& operator*(){
		return *ptr;
	}

	iterator<T>& operator++(){
		++ptr;
		return *this;
	}

private:
	T* ptr;   //Pointer to current element
};

//Reverse iterator class
template<class T>
class r_iterator{
public:
	r_iterator(T* p){
		ptr = p;
	}

	bool operator==(const r_iterator<T>& other){
		return ptr == other.ptr;
	}

	bool operator!=(const r_iterator<T>& other){
		return ptr != other.ptr;
	}

	T& operator*(){
		return *ptr;
	}

	r_iterator<T>& operator++(){
		--ptr;
		return *this;
	}

private:
	T* ptr;   //Pointer to current element
};


//Vector class
template<class T, class Alloc = std::allocator<T>>
class vector{
public:

	//Creates empty vector
	vector(){
		capacity = 8;
		size_ = 0;

		array = allocator.allocate(capacity);
	}

	//Creates vector with n elements with undefined values
	explicit vector(size_t n){
		//Initial capacity is power of 2 big enough to cover n elements
		capacity = pow(2, trunc(log(n)) + 1);
		size_ = n;

		array = allocator.allocate(capacity);
		for(uint i = 0; i < size_; i++)
			allocator.construct(array + i);
	}

	//Creates vector with n elements with copies of defVal 
	vector(size_t n, const T& defVal){
		//Initial capacity is power of 2 big enough to cover n elements
		capacity = pow(2, trunc(log(n)) + 1);
		size_ = n;

		array = allocator.allocate(capacity);
		for(uint i = 0; i < size_; i++)
			array[i] = defVal;
	}

	//Access to i element by reference
	T& operator[](int i){
		return array[i];
	}

	//Adds elem to the end of vector, allocates new memory
	void push_back(const T&& elem){
		array[size_] = elem;
		size_++;

		//Allocates new memory if amount of elements is more than 90% of capacity
		if((double)size_/capacity >= 0.9){
			T* new_array = allocator.allocate(2*capacity);
			for(uint i = 0; i < size_; i++){
				new_array[i] = array[i];
				allocator.destroy(array + i);
			}
			allocator.deallocate(array, capacity);
			array = new_array;
			capacity *= 2;
		}
	}

	//Destroys last element of vector, if vector is empty, does nothing
	void pop_back(){
		if(size_ == 0) return;
		size_--;
		allocator.destroy(array + size_);
	}

	//Change size to new_size
	//If new_size < size, destroys elements to resize
	//If new_size > size, adds elements initialized with default constructors
	void resize(size_t new_size){
		if(new_size < size_){
			for(uint i = 0; i < size_ - new_size; i++)
				this->pop_back();
			return;
		}

		for(uint i = 0; i < new_size - size_; i++)
			this->push_back(T());
	}

	//Change size to new_size
	//If new_size < size, destroys elements to resize
	//If new_size > size, adds elements initialized with defVal
	void resize(size_t new_size, const T& defVal){
		if(new_size < size_){
			for(uint i = 0; i < size_ - new_size; i++)
				this->pop_back();
			return;
		}

		for(uint i = 0; i < new_size - size_; i++)
			this->push_back(defVal);
	}

	//Returns true, if vector is empty
	bool empty() const{
		return !size_;
	}

	//Returns size of vector
	size_t size() const{
		return size_;
	}

	//Destroys all elements of vector
	void clear(){
		size_t old_size = size_;

		for(uint i = 0; i < old_size; i++)
			this->pop_back();

		size_ = 0;
	}

	//Returns iterator to the begining
	iterator<T> begin(){
		return iterator<T>(array);
	}

	//Returns iterator to the end
	iterator<T> end(){
		return iterator<T>(array + size_ - 1);
	}

	//Returns reverse iterator to the reverse begining
	r_iterator<T> rbegin(){
		return r_iterator<T>(array + size_ - 1);
	}

	//Returns iterator to the reverse end
	r_iterator<T> rend(){
		return r_iterator<T>(array);
	}

	~vector(){
		for(uint i = 0; i < size_; i++)
			allocator.destroy(array + i);
		allocator.deallocate(array, capacity);
	}

private:
	Alloc allocator;   //allocator
	T* array;		   //Pointer to the elements
	size_t size_;      //Amount of elements
	size_t capacity;   //Amount of allocated memory
};

//Struct for testing memory
struct A{
	
	A(){
		std::cout << "A constr\n";
	}

	void operator=(const A& copied){
		std::cout << "A copy\n";
	}

	~A(){
		std::cout << "A des\n";
	}
};

//Tests
void check(bool expr){
	if(!expr)
		assert(!"error");
}

//Checks constructors
void checkConstructors(){
	vector<A> vec1;

	check(vec1.size() == 0);

	vector<A> vec2(5);

	check(vec2.size() == 5);

	vector<A> vec3(5, A());

	check(vec3.size() == 5);
}

//Checks push_back(), pop_back(), size()
void checkPushPop(){
	vector<A> vec;

	vec.push_back(A());

	check(vec.size() == 1);

	vec.pop_back();
}

//Checks [] operator
void checkElAccess(){
	vector<int> vec(5, 1);

	check(vec[0] == 1);

	vec[1] = 5;

	check(vec[1] == 5);
}

//Checks empty()
void checkEmpty(){
	vector<int> vec;

	check(vec.empty());
}

//Checks clear()
void checkClear(){
	vector<int> vec(6);

	vec.clear();

	check(vec.empty());
}

//Checks begin(), end()
void checkIter(){
	vector<int> vec(3, 0);

	vec[1] = 1;
	vec[2] = 2;

	iterator<int> it = vec.begin();

	int i = 0;

	for(; it != vec.end(); ++it, ++i)
		check(*it == i);
}

//Checks rbegin(), rend()
void checkRIter(){
	vector<int> vec(3, 0);

	vec[1] = 1;
	vec[2] = 2;

	r_iterator<int> it = vec.rbegin();

	int i = 2;

	for(; it != vec.rend(); ++it, --i)
		check(*it == i);	
}

//Checks memory allocation
void checkMemory(){
	vector<int> vec;

	for(uint i = 0; i < 1000; i++)
		vec.push_back(0);
}

int main(){

	checkConstructors();
	checkPushPop();
	checkElAccess();
	checkEmpty();
	checkClear();
	checkIter();
	checkRIter();
	checkMemory();

	return 0;
}
