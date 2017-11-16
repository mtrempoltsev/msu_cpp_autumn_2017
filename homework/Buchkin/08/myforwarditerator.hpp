#pragma once

#include <memory>

#include "myvector.hpp"

template <class T>
class myForwardIterator
{
	Vector<T>* vecPtr;
	size_t idx;
	
public:
	myForwardIterator(Vector<T>*, size_t);
	T& operator* () const;
	myForwardIterator<T>& operator++ ();
	myForwardIterator<T> operator++ (int);
	myForwardIterator<T>& operator-- ();
	myForwardIterator<T> operator-- (int);
	bool operator== (const myForwardIterator<T>&) const noexcept;
	bool operator!= (const myForwardIterator<T>&) const noexcept;
};

template <class T>
myForwardIterator<T>::myForwardIterator(Vector<T>* ptr_, size_t idx_):
vecPtr(ptr_), idx(idx_) {}

template <class T> inline T&
myForwardIterator<T>::operator* () const
{
	return (*vecPtr)[idx];
}

template <class T> myForwardIterator<T>&
myForwardIterator<T>::operator++ ()
{
	++idx;
	return *this;
}

template <class T> myForwardIterator<T>
myForwardIterator<T>::operator++ (int)
{
	myForwardIterator<T> it(vecPtr, idx);
	++idx;
	return it;
}

template <class T> myForwardIterator<T>&
myForwardIterator<T>::operator-- ()
{
	--idx;
	return *this;
}

template <class T> myForwardIterator<T>
myForwardIterator<T>::operator-- (int)
{
	myForwardIterator<T> it(vecPtr, idx);
	--idx;
	return it;
}

template <class T> inline bool
myForwardIterator<T>::operator== (const myForwardIterator<T>& it) const noexcept
{
	return (vecPtr == it.vecPtr) && (idx == it.idx);
}

template <class T> inline bool
myForwardIterator<T>::operator!= (const myForwardIterator<T>& it) const noexcept
{
	return !this->operator == (it);
}
