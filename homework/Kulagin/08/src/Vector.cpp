#pragma once

#include "../include/Vector.h"


// OPERATORS BEGINS
template<class T>
Vector<T>& Vector<T>::operator=(Vector&& _v) {
	if (data_ != nullptr) {
		delete[] data_;
	}

	data_ = std::move(_v.data_);
	size_ = _v.size_;
	capacity_ = _v.capacity_;

	_v.data_ = nullptr;
	_v.size_ = 0;
	_v.capacity_ = 0;

	return (*this);
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector& _v) {
	if (_v.data_ != data_ || _v.size_ > size_) {
		if (data_ != nullptr) {
			delete[] data_;
		}

		size_ = _v.size_;
		capacity_ = _v.capacity_;
		data_ = new T[capacity_];
	}

	for (size_t i = 0; i < size_; i++) {
		data_[i] = _v.data_[i];
	}

	return (*this);
}

template<class T>
T& Vector<T>::operator[](size_t _pos) {
	return data_[_pos];
}

template<class T>
const T& Vector<T>::operator[](size_t _pos) const {
	return data_[_pos];
}
// OPERATORS ENDS


// ----------------------------------------------
template<class T>
const T* Vector<T>::data() const {
	return data_;
}

template<class T>
void Vector<T>::push_back(const T& _value) {
	if (data_ == nullptr) {
		*this = std::move(Vector(8));

		size_ = 0;
	}

	if (size_ == capacity_) {
		auto v = std::move(*this);

		resize(size_);

		for (size_t i = 0; i < size_; i++) {
			data_[i] = v[i];
		}
	}

	data_[size_] = _value;
	size_++;
}

template<class T>
void Vector<T>::pop_back() {
	if (size_ == 1) {
		clear();
	} else if (size_ > 1) {
		--size_;
	}
}

template<class T>
void Vector<T>::resize(size_t _size) {
	(*this) = std::move(Vector(_size));
}

template<class T>
void Vector<T>::resize(size_t size, const T& default_value) {
	(*this) = std::move(Vector(size, default_value));
}

template<class T>
size_t Vector<T>::size() const noexcept {
	return size_;
}

template<class T>
bool Vector<T>::empty() const noexcept {
	return (size_ == 0);
}

template<class T>
void Vector<T>::clear() {
	(*this) = std::move(Vector());
}
// ----------------------------------------------


// ITERATORS BEGINS
template<class T>
using iterator = Iterator<T>;

template<class T>
using const_iterator = Iterator<const T>;

template<class T>
iterator<T> Vector<T>::begin() noexcept {
	return Iterator<T>(data_);
}

template<class T>
Iterator<T> Vector<T>::end() noexcept {
	return Iterator<T>(data_ + size_);
}

template<class T>
Iterator<const T> Vector<T>::cbegin() const noexcept {
	return Iterator<const T>(data_);
}

template<class T>
Iterator<const T> Vector<T>::cend() const noexcept {
	return Iterator<const T>(data_ + size_);
}

template<class T>
ReverseIterator<T> Vector<T>::rbegin() noexcept {
	return ReverseIterator<T>(data_ + size_ - 1);
}

template<class T>
ReverseIterator<T> Vector<T>::rend() noexcept {
	return ReverseIterator<T>(data_ - 1);
}

template<class T>
ReverseIterator<const T> Vector<T>::crbegin() const noexcept {
	return ReverseIterator<const T>(data_ + size_ - 1);
}

template<class T>
ReverseIterator<const T> Vector<T>::crend() const noexcept {
	return ReverseIterator<const T>(data_ - 1);
}
// ITERATORS ENDS
