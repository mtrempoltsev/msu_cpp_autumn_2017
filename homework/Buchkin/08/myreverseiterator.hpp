#pragma once

#include <memory>

#include "myvector.hpp"

template <class T>
class myReverseIterator
{
	Vector<T>* vecPtr;
	size_t idx;
	
public:
	myReverseIterator(Vector<T>*, size_t);
	T& operator* () const;
	myReverseIterator<T>& operator++ ();
	myReverseIterator<T> operator++ (int);
	myReverseIterator<T>& operator-- ();
	myReverseIterator<T> operator-- (int);
	bool operator== (const myReverseIterator<T>&) const noexcept;
	bool operator!= (const myReverseIterator<T>&) const noexcept;
};

template <class T>
myReverseIterator<T>::myReverseIterator(Vector<T>* ptr_, size_t idx_):
vecPtr(ptr_), idx(idx_) {}

template <class T> inline T&
myReverseIterator<T>::operator* () const
{
	return (*vecPtr)[idx];
}

template <class T> myReverseIterator<T>&
myReverseIterator<T>::operator++ ()
{
	--idx;
	return *this;
}

template <class T> myReverseIterator<T>
myReverseIterator<T>::operator++ (int)
{
	myReverseIterator<T> it(vecPtr, idx);
	--idx;
	return it;
}

template <class T> myReverseIterator<T>&
myReverseIterator<T>::operator-- ()
{
	++idx;
	return *this;
}

template <class T> myReverseIterator<T>
myReverseIterator<T>::operator-- (int)
{
	myReverseIterator<T> it(vecPtr, idx);
	++idx;
	return it;
}

template <class T> inline bool
myReverseIterator<T>::operator== (const myReverseIterator<T>& it) const noexcept
{
	return (vecPtr == it.vecPtr) && (idx == it.idx);
}

template <class T> inline bool
myReverseIterator<T>::operator!= (const myReverseIterator<T>& it) const noexcept
{
	return !this->operator == (it);
}
