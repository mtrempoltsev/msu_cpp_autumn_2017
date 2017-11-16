#pragma once

#include "Iterator.h"
#include "ReverseIterator.h"


template<class T>
class Vector {

public:
	using iterator = Iterator<T>;
	using const_iterator = Iterator<const T>;
	using reverse_iterator = ReverseIterator<T>;
	using const_reverse_iterator = ReverseIterator<const T>;

	// CONSTRUCTOR BEGINS
	Vector() {
		data_ = nullptr;

		size_ = 0;
		capacity_ = 0;
	}

	explicit Vector(size_t _size) {
		size_ = _size;
		capacity_ = size_ * 2;

		data_ = new T[capacity_];
	}

	Vector(const Vector& vector) : Vector() {
		(*this) = vector;
	}

	Vector(Vector&& vector) : Vector() {
		(*this) = vector;
	}

	explicit Vector(size_t _size, const T& default_value) : Vector(_size) {
		for (size_t i = 0; i < _size; i++) {
			data_[i] = default_value;
		}
	}

	Vector(std::initializer_list<T> v_list) : Vector(v_list.size()) {
		size_t i = 0;

		for (auto it = v_list.begin(); it < v_list.end(); it++) {
			data_[i++] = (*it);
		}
	}
	// CONSTRUCTOR ENDS

	// OPERATORS BEGINS
	Vector& operator=(const Vector& _v);
	Vector& operator=(Vector&& vector);

	T& operator[](size_t _pos);
	const T& operator[](size_t _pos) const;
	// OPERATORS ENDS


	// ------------------------------------------
	const T* data() const;

	void push_back(const T& _value);
	void pop_back();

	void resize(size_t size);

	void resize(size_t size, const T& default_value);

	size_t size() const noexcept;

	bool empty() const noexcept;

	void clear();
	// ------------------------------------------


	// ITERATORS BEGINS
	iterator begin() noexcept;
	iterator end() noexcept;

	const_iterator cbegin() const noexcept;
	const_iterator cend() const noexcept;

	reverse_iterator rbegin() noexcept;
	reverse_iterator rend() noexcept;

	const_reverse_iterator crbegin() const noexcept;
	const_reverse_iterator crend() const noexcept;
	// ITERATORS ENDS


	// DESTRUCTOR BEGINS
	~Vector() {
		if (data_ != nullptr) {
			delete[] data_;
		}

		size_ = 0;
		capacity_ = 0;
	}
	// DESTRUCTOR ENDS


	friend std::ostream& operator<<(std::ostream& out, const Vector<T>& vector) {
		for (auto x : vector) {
			out << x << " ";
		}
		out << "\n*************************************";
		return out;
	}

private:
	T* data_;

	size_t size_;
	size_t capacity_;
};
