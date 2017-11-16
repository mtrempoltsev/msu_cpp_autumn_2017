#pragma once

template <class T>
class Iterator
{
private:
	T* ptr_;

public:
	Iterator(T* ptr)
		:ptr_(ptr)
	{}

	T& operator*() const
	{
		return *ptr_;
	}

	bool operator==(const Iterator& other) const
	{
		return other.ptr_ == ptr_;
	}


	bool operator!=(const Iterator& other) const
	{
		return !(*this == other);
	}


	Iterator& operator++()
	{
		ptr_++;
		return *this;
	}
	Iterator& operator++(int)
	{
		Iterator<T> tmp(ptr_);
		ptr_++;
		return tmp;
	}

	Iterator& operator--()
	{
		ptr_--;
		return *this;
	}
	Iterator& operator--(int)
	{
		Iterator tmp(ptr_);
		ptr_--;
		return tmp;
	}
	Iterator& operator+ (size_t n)
	{
		ptr_ += n;
		return *this;
	}
	Iterator& operator- (size_t n)
	{
		ptr_ -= n;
		return *this;
	}

};

template <class T>
class Reverse_Iterator
{
private:
	T* ptr_;

public:
	Reverse_Iterator(T* ptr)
		:ptr_(ptr)
	{}


	bool operator==(const Reverse_Iterator& other) const
	{
		return other.ptr_ == ptr_;
	}

	bool operator!=(const Reverse_Iterator& other) const
	{
		return !(*this == other);
	}

	T& operator*() const
	{
		return *ptr_;
	}
	Reverse_Iterator& operator++()
	{
		ptr_--;
		return *this;
	}
	Reverse_Iterator& operator++(int)
	{
		Reverse_Iterator<T> tmp(ptr_);
		ptr_--;
		return tmp;
	}

	Reverse_Iterator& operator--()
	{
		ptr_++;
		return *this;
	}
	Reverse_Iterator& operator--(int)
	{
		Reverse_Iterator<T> tmp(ptr_);
		ptr_++;
		return tmp;
	}
	Reverse_Iterator& operator+ (size_t n)
	{
		ptr_ -= n;
		return *this;
	}
	Reverse_Iterator& operator- (size_t n)
	{
		ptr_ += n;
		return *this;
	}
};
