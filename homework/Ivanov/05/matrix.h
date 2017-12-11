#pragma once
#include <vector>

using std::size_t;
using std::vector;

template <class T>
class Proxy
{
	vector<T> vec;
public:
	Proxy(size_t);
	size_t getsize() const;
	T& operator[] (size_t);
	Proxy& multconst(T);
	Proxy& multvect(const vector<T>&);
	bool operator== (const Proxy&) const;
	~Proxy();
};

template <class T>
class Matrix
{
	vector<Proxy<T>> vec;
public:
	Matrix(size_t, size_t);
    size_t getcols() const;
    size_t getrows() const;
    Matrix(const Matrix<T>&);
	Matrix (Matrix<T>&&);
	Matrix& operator=(Matrix&&);
	Matrix& operator=(const Matrix&);
	Proxy<T>& operator[] (size_t);
	Matrix& operator*= (double);
	Matrix& operator*= (const vector<T>&);
    bool operator== (Matrix &);
    bool operator!= (Matrix &);
	~Matrix();
};