#include <iostream>
#include <memory>
#include <stdexcept>
#include <memory>

template <class T>
class Vector;


//Forward Iterator class for Vector
template <class T>
class FwdIt
{
	Vector<T>* vecPtr;
	size_t idx;

public:

  //constructor
  FwdIt(Vector<T>* ptr_, size_t idx_):
  vecPtr(ptr_), idx(idx_) {}

  //dereferencing operator, returns an element of Vector
  inline T& operator* () const
  {
  	return (*vecPtr)[idx];
  }

  //prefix iterators' next() function,
  //returns self iterator pointing to next element
  FwdIt<T>& operator++ ()
  {
  	++idx;
  	return *this;
  }

  //postfix iterators' next() function,
  //returns new iterator pointing to the current element
  FwdIt<T> operator++ (int)
  {
  	FwdIt<T> it(vecPtr, idx);
  	++idx;
  	return it;
  }

  //prefix prev() function
  FwdIt<T>& operator-- ()
  {
  	--idx;
  	return *this;
  }

  //postfix prev() function
  FwdIt<T> operator-- (int)
  {
  	FwdIt<T> it(vecPtr, idx);
  	--idx;
  	return it;
  }

  //equality comparison
  //used for looping over container
  inline bool operator== (const FwdIt<T>& it) const noexcept
  {
  	return (vecPtr == it.vecPtr) && (idx == it.idx);
  }

  //inequality comparison
  //used for looping over container
  inline bool operator!= (const FwdIt<T>& it) const noexcept
  {
  	return !this->operator == (it);
  }

};

//reverse container iterator; has the same interface as forward iterator
//but increment and decrement change iterators pointing places
//in the opposite direction compared to the forward
template <class T>
class RvsIt
{
	Vector<T>* vecPtr;
	size_t idx;

public:

  RvsIt(Vector<T>* ptr_, size_t idx_):
  vecPtr(ptr_), idx(idx_) {}

  inline T& operator* () const
  {
  	return (*vecPtr)[idx];
  }

  RvsIt<T>& operator++ ()
  {
  	--idx;
  	return *this;
  }

  RvsIt<T> operator++ (int)
  {
  	RvsIt<T> it(vecPtr, idx);
  	--idx;
  	return it;
  }

  RvsIt<T>& operator-- ()
  {
  	++idx;
  	return *this;
  }

  RvsIt<T> operator-- (int)
  {
  	RvsIt<T> it(vecPtr, idx);
  	++idx;
  	return it;
  }

  inline bool operator== (const RvsIt<T>& it) const noexcept
  {
  	return (vecPtr == it.vecPtr) && (idx == it.idx);
  }

  inline bool operator!= (const RvsIt<T>& it) const noexcept
  {
  	return !this->operator == (it);
  }
};

//container of type T
template <class T>
class Vector
{
	std::unique_ptr<T[]> ptr = std::unique_ptr<T[]>(new T[1]);

	size_t numSize = 0;
	size_t arraySize = 1;

public:

  using iterator = FwdIt<T>;
  using reverse_iterator = RvsIt<T>;

  //procedure that zero to container length and returns the length
	bool empty() const
  {
    return numSize == 0;
  }
  //procedure that zero to container length
  void clear()
  {
    numSize = 0;
  }

  //function returns current containers' size
	size_t size() const
  {
    return numSize;
  }

  //get element operator
  T& operator[] (size_t idx)
  {
  	if (idx >= numSize) {
      std::cout<<idx<<std::endl;
  		throw std::runtime_error("Trying to access nonexisting element");
  	}
  	return ptr[idx];
  }

  //pushing procedure
  void push_back(const T& value)
  {
  	if (numSize == arraySize) {
  		std::unique_ptr<T[]> newPtr(new T[2 * arraySize]);
  		for (size_t i = 0; i != arraySize; ++i) {
  			newPtr[i] = ptr[i];
  		}
  		ptr.swap(newPtr);
  		arraySize *= 2;
  	}

  	ptr[numSize] = value;
  	++numSize;
  }

  //popping procedure
  void pop_back()
  {
  	if (numSize == 0) {
  		throw std::runtime_error("Trying to pop_back empty vector");
  	}

  	--numSize;
  }

  //returns begin iterator
  FwdIt<T> begin()
  {
  	return FwdIt<T>(this, 0);
  }

  //returns end iterator
  FwdIt<T> end()
  {
  	return FwdIt<T>(this, numSize);
  }

  //returns reverse begin iterator
  RvsIt<T> rbegin()
  {
  	return RvsIt<T>(this, numSize - 1);
  }

  //returns reverse end iterator
  RvsIt<T> rend()
  {
    //casting int -1 to size_t to get great unsigned int
  	return RvsIt<T>(this, size_t(-1));
  }

};


int main()
{
  //testing Vector

  //create a Vector and output it
  Vector<int> a;
	for (int i = 0; i != 10; ++i) a.push_back(i*2 + 5);

	for (int i = 0; i != 10; ++i) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;

  //iterate over Vector and output it
	for (Vector<int>::iterator it = a.begin(); it != a.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

  //iterate over Vector using reverse iterator
	for (Vector<int>::reverse_iterator it = a.rbegin(); it != a.rend(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;


  //trying to get it = end() element
	auto it1 = a.end();
	try {
		*it1;
	}
	catch (const std::runtime_error& exception) {
		std::cout << exception.what() << std::endl;
	}

  //trying to get it = rend() element
	try {
		*a.rend();
	}
	catch (const std::runtime_error& exception) {
		std::cout << exception.what() << std::endl;
	}

  //trying to pop from empty vector
	a.clear();
	try {
		a.pop_back();
	}
	catch (const std::runtime_error& exception) {
		std::cout << exception.what() << std::endl;
	}
	std::cout << std::endl;
  return 0;
}
