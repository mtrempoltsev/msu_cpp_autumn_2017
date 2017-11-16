#pragma once
#include <iostream>
template <class T>
class Titerator : public std::iterator<std::random_access_iterator_tag, T>
{
private:
	T* ptr;
public:
	explicit Titerator<T>(T* ptr_) : ptr(ptr_) { }
	bool operator == (const Titerator& tmp) { return ptr == tmp.ptr; }
	bool operator != (const Titerator& tmp) { return ptr != tmp.ptr; }
	T& operator *() const { return *ptr; }
	T& operator ->() const { return ptr; }
	Titerator<T> operator ++ () { ptr++; return *this; }
	//Titerator<T>& operator ++ (int) { Titerator<T> tmp = *this; ptr++; return tmp; }
	Titerator<T> operator -- () { ptr--; return *this; }
	//Titerator<T>& operator -- (int) { Titerator<T> tmp = *this; ptr--; return tmp; }
	Titerator<T> operator + (int n) { return Titerator<T>(ptr + n); }
	Titerator<T> operator - (int n) { return Titerator<T>(ptr - n); }
	Titerator<T>& operator += (int n) { ptr += n; return *this; }
	Titerator<T>& operator -= (int n) { ptr -= n; return *this; }
};



template<class T>
class ReverseTiterator : public std::iterator<std::random_access_iterator_tag, T>  
{
private:
	T* ptr;
public:
	explicit ReverseTiterator<T>(T* ptr_) :ptr(ptr_) { }
	bool operator == (const ReverseTiterator& tmp) { return ptr == tmp.ptr; }
	bool operator != (const ReverseTiterator& tmp) { return ptr != tmp.ptr; }
	T& operator *() const { return *ptr; }
	T& operator ->() const { return ptr; }
	ReverseTiterator<T> operator ++ ()  { ptr--; return *this; }
	//ReverseTiterator<T>& operator ++ (int)  { ReverseTiterator<T> tmp = *this; Titerator<T>::ptr--; return tmp; }
	ReverseTiterator<T> operator -- ()  { ptr++; return *this; }
	//ReverseTiterator<T>& operator -- (int)  { ReverseTiterator<T> tmp = *this; Titerator<T>::ptr--; return tmp; }
	ReverseTiterator<T> operator + (int n)  { return  ReverseTiterator<T>(ptr - n); }
	ReverseTiterator<T> operator - (int n)  { return  ReverseTiterator<T>(ptr + n); }
	ReverseTiterator<T>& operator += (int n)  { ptr -= n; return *this; }
	ReverseTiterator<T>& operator -= (int n) { ptr += n; return *this; }
};
