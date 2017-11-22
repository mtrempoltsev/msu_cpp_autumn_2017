#pragma once

#include <iterator>


template<class T>
class ReverseIterator : public std::iterator<std::random_access_iterator_tag, T> {

public:
	explicit ReverseIterator(T* ptr) : ptr_(ptr) {}

	ReverseIterator& operator++() {
		--ptr_;

		return (*this);
	}

	ReverseIterator& operator--() {
		++ptr_;

		return (*this);
	}

	ReverseIterator operator+(int x) {
		return ReverseIterator(ptr_ - x);
	}

	ReverseIterator operator-(int x) {
		return ReverseIterator(ptr_ + x);
	}

	ReverseIterator& operator+=(int x) {
		ptr_ -= x;

		return (*this);
	}

	ReverseIterator& operator-=(int x) {
		ptr_ += x;

		return (*this);
	}

	bool operator==(const ReverseIterator& it) {
		return (ptr_ == it.ptr_);
	}

	bool operator!=(const ReverseIterator& it) {
		return (ptr_ != it.ptr_);
	}

	T& operator*() {
		return (*ptr_);
	}

	T* operator->() {
		return ptr_;
	}

private:
	T* ptr_;
};
