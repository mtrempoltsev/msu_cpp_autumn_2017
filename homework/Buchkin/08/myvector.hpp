#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>

template <class T>
class myForwardIterator;
template <class T>
class myReverseIterator;

template <class T>
class Vector
{
	std::unique_ptr<T[]> ptr = std::unique_ptr<T[]>(new T[1]);
	
	size_t numSize = 0;
	size_t arraySize = 1;
	
public:
	using valueType = T;
	using iterator = myForwardIterator<T>;
	using reverse_iterator = myReverseIterator<T>;
	
	T& operator[] (size_t);
	bool empty() const {return numSize == 0;}
	size_t size() const {return numSize;}
	
	void push_back(const T&);
	void pop_back();
	void clear() {numSize = 0;};
	
	myForwardIterator<T> begin();
	myForwardIterator<T> end();
	myReverseIterator<T> rbegin();
	myReverseIterator<T> rend();
};

template <class T> T&
Vector<T>::operator[] (size_t idx)
{
	if (idx >= numSize) {
		throw std::runtime_error("Trying to access inexisting element");
	}
	return ptr[idx];
}

template <class T> void
Vector<T>::push_back(const T& value)
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

template <class T> void
Vector<T>::pop_back()
{
	if (numSize == 0) {
		throw std::runtime_error("Trying to pop_back empty vector");
	}
	
	--numSize;
}

template <class T> myForwardIterator<T>
Vector<T>::begin()
{
	return myForwardIterator<T>(this, 0);
}

template <class T> myForwardIterator<T>
Vector<T>::end()
{
	return myForwardIterator<T>(this, numSize);
}

template <class T> myReverseIterator<T>
Vector<T>::rbegin()
{
	return myReverseIterator<T>(this, numSize - 1);
}

template <class T> myReverseIterator<T>
Vector<T>::rend()
{
	return myReverseIterator<T>(this, size_t(-1));
}
