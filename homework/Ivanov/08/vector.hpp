#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>

template <class T>
class Vector;

template <class T>
class reverse_iter
{
	Vector<T>* v_ptr;
	size_t idx;
	
public:
	reverse_iter(Vector<T>*, size_t);
	T& operator* () const;
	reverse_iter<T>& operator++ ();
	reverse_iter<T> operator++ (int);
	reverse_iter<T>& operator-- ();
	reverse_iter<T> operator-- (int);
	bool operator== (const reverse_iter<T>&) const noexcept;
	bool operator!= (const reverse_iter<T>&) const noexcept;
};

template <class T>
reverse_iter<T>::reverse_iter(Vector<T>* ptr, size_t index):
v_ptr(ptr), idx(index) {}

template <class T> inline T&
reverse_iter<T>::operator* () const
{
	return (*v_ptr)[idx];
}

template <class T> reverse_iter<T>&
reverse_iter<T>::operator++ ()
{
	--idx;
	return *this;
}

template <class T> reverse_iter<T>
reverse_iter<T>::operator++ (int)
{
	reverse_iter<T> it(v_ptr, idx);
	--idx;
	return it;
}

template <class T> reverse_iter<T>&
reverse_iter<T>::operator-- ()
{
	++idx;
	return *this;
}

template <class T> reverse_iter<T>
reverse_iter<T>::operator-- (int)
{
	reverse_iter<T> it(v_ptr, idx);
	++idx;
	return it;
}

template <class T> inline bool
reverse_iter<T>::operator== (const reverse_iter<T>& it) const noexcept
{
	return (v_ptr == it.v_ptr) && (idx == it.idx);
}

template <class T> inline bool
reverse_iter<T>::operator!= (const reverse_iter<T>& it) const noexcept
{
	return !this->operator == (it);
}

template <class T>
class forward_iter
{
	Vector<T>* v_ptr;
	size_t idx;
	
public:
	forward_iter(Vector<T>*, size_t);
	T& operator* () const;
	forward_iter<T>& operator++ ();
	forward_iter<T> operator++ (int);
	forward_iter<T>& operator-- ();
	forward_iter<T> operator-- (int);
	bool operator== (const forward_iter<T>&) const noexcept;
	bool operator!= (const forward_iter<T>&) const noexcept;
};

template <class T>
forward_iter<T>::forward_iter(Vector<T>* ptr, size_t index):
v_ptr(ptr), idx(index) {}

template <class T> inline T&
forward_iter<T>::operator* () const
{
	return (*v_ptr)[idx];
}

template <class T> forward_iter<T>&
forward_iter<T>::operator++ ()
{
	++idx;
	return *this;
}

template <class T> forward_iter<T>
forward_iter<T>::operator++ (int)
{
	forward_iter<T> it(v_ptr, idx);
	++idx;
	return it;
}

template <class T> forward_iter<T>&
forward_iter<T>::operator-- ()
{
	--idx;
	return *this;
}

template <class T> forward_iter<T>
forward_iter<T>::operator-- (int)
{
	forward_iter<T> it(v_ptr, idx);
	--idx;
	return it;
}

template <class T> inline bool
forward_iter<T>::operator== (const forward_iter<T>& it) const noexcept
{
	return (v_ptr == it.v_ptr) && (idx == it.idx);
}

template <class T> inline bool
forward_iter<T>::operator!= (const forward_iter<T>& it) const noexcept
{
	return !this->operator == (it);
}


template <class T>
class Vector
{
	std::unique_ptr<T[]> ptr = std::unique_ptr<T[]>(new T[1]);
	
	size_t size_n = 0;
	size_t size_a = 1;
	
public:
	using valueType = T;
	using iterator = forward_iter<T>;
	using reverse_iterator = reverse_iter<T>;
	
	T& operator[] (size_t);
	bool empty() const {return size_n == 0;}
	size_t size() const {return size_n;}
	
	void push_back(const T&);
	void pop_back();
	void clear() {size_n = 0;};
	
	forward_iter<T> begin();
	forward_iter<T> end();
	reverse_iter<T> rbegin();
	reverse_iter<T> rend();
};

template <class T> T&
Vector<T>::operator[] (size_t idx)
{
	if (idx >= size_n) {
		throw std::runtime_error("Trying to access inexisting element");
	}
	return ptr[idx];
}

template <class T> void
Vector<T>::push_back(const T& value)
{
	if (size_n == size_a) {
		std::unique_ptr<T[]> newPtr(new T[2 * size_a]);
		for (size_t i = 0; i != size_a; ++i) {
			newPtr[i] = ptr[i];
		}
		ptr.swap(newPtr);
		size_a *= 2;
	}
	
	ptr[size_n] = value;
	++size_n;
}

template <class T> void
Vector<T>::pop_back()
{
	if (size_n == 0) {
		throw std::runtime_error("Trying to pop_back empty vector");
	}
	
	--size_n;
}

template <class T> forward_iter<T>
Vector<T>::begin()
{
	return forward_iter<T>(this, 0);
}

template <class T> forward_iter<T>
Vector<T>::end()
{
	return forward_iter<T>(this, size_n);
}

template <class T> reverse_iter<T>
Vector<T>::rbegin()
{
	return reverse_iter<T>(this, size_n - 1);
}

template <class T> reverse_iter<T>
Vector<T>::rend()
{
	return reverse_iter<T>(this, size_t(-1));
}

