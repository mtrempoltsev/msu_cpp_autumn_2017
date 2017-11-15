#pragma once

#include <memory>
#include <initializer_list>
#include "iterator.cpp"

template <class T>
class Vector
{
private:

	std::unique_ptr<T[]> data_;
	size_t size_;
	size_t capacity_;
	std::allocator<T> a1;
public:

	using reference = T&;
	using const_reference = const T&;

	using iterator = Iterator<T>;
	using const_iterator = Iterator<const T>;

	using reverse_iterator = Reverse_Iterator<T>;
	using const_reverse_iterator = Reverse_Iterator<const T>;


	Vector(std::initializer_list<T> init)
		:size_(init.size())
		,capacity_(init.size())
	{
		data_ = std::make_unique<T[]>(size_);
		std::copy(init.begin(), init.end(), data_.get());
	}

	Vector(const Vector& copied)
		:size_(copied.size_)
		,capacity_(copied.capacity_)
	{
		data_ = std::make_unique<T[]>(capacity_);
		std::copy(copied.data_.get(), copied.data_.get()+size_, data_.get());
	}

	Vector(size_t size = 0)
		:size_(size)
		,capacity_(size)
	{
		data_ = std::make_unique<T[]>(size_);
	}

	~Vector()
	{
		size_ = 0;
		capacity_ = 0;
	}

	void clear()
	{
		data_.reset();
		size_ = 0;
		capacity_ = 0;
	}

	void resize(size_t new_size)
	{
		if (new_size < 0)
		{
			throw runtime_error("size is less than 0");
		}
		if (new_size > capacity_)
		{
			change_capacity(new_size);
		}
		size_ = new_size;
	}

	void resize(size_t new_size, T default_val)
	{
		size_t old_size = size_;
		resize(new_size);
		for (size_t i = old_size; i < size_; i++)
		{
			data_[i] = default_val;
		}
	}

	void change_capacity(size_t new_capacity)
	{
		if (new_capacity < size_)
		{
			throw runtime_error("capacity is less than size");
		}
		if (new_capacity == capacity_)
		{
			return;
		}

		auto tmp = std::make_unique<T[]>(new_capacity);
		std::copy(data_.get(), data_.get() + size_, tmp.get());
		data_ = std::move(tmp);
		capacity_ = new_capacity;
	}

	constexpr size_t size() const noexcept
	{
		return size_;
	}

	constexpr size_t capacity() const noexcept
	{
		return capacity_;
	}

	constexpr bool empty() const noexcept
	{
		if (size_ == 0)
			return true;
		else
			return false;
	}

	reference at(size_t pos)
	{
		if (pos >= size_)
		{
			throw runtime_error("out of range");
		}
		return data_[pos];
	}

	reference operator[](size_t pos)
	{
		if ((pos >= size_) || (pos < 0))
		{
			throw runtime_error("out of range");
		}
		return data_[pos];
	}

	void push_back(const T& a)
	{
		if (capacity_ == size_)
		{
			if (capacity_ == 0)
				change_capacity(1);
			else
				change_capacity(size_ * 2);
		}
		data_[size_] = a;
		size_++;
	}

	void pop_back()
	{
		if (size_ < 1)
		{
			throw runtime_error("no elements");
		}
		data_[size_ - 1] = 0;
		size_--;
	}



	iterator begin() const
	{
		return iterator(data_.get());
	}
	iterator end() const
	{
		return iterator(data_.get() + size_);
	}


	reverse_iterator rbegin() const
	{
		return reverse_iterator(data_.get() + size_ - 1);
	}
	reverse_iterator rend() const
	{
		return reverse_iterator(data_.get() - 1);
	}

	//if cout is supported
	void print() const
	{
		for (int i = 0; i < size_; i++)
			cout << data_[i] << " ";
		cout << endl;
	}

};
