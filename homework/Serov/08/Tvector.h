#include "Titerator.h"
#include <iostream>
template <class T>
class Tvector
{
private:
	T* vec;
	size_t size_;
	size_t capacity_;
public:

	using value_type = T;
	using Iterator = Titerator<T>;
	using RIterator = ReverseTiterator<T>;
	
	explicit Tvector() : vec(nullptr), size_(0), capacity_(0)
	{
	}	
	
	explicit Tvector(size_t count) : size_(count), capacity_(count * 2)
	{
		vec = new value_type[capacity_];
	}
	
	Tvector(size_t count, const value_type& defaultValue) : Tvector(count)
	{
		for (size_t i = 0; i < size_; i++)
			vec[i] = defaultValue;
	}

	~Tvector()
	{
		size_ = 0;
		capacity_ = 0;
		if (vec != nullptr)
		{
			delete[] vec;
			vec = nullptr;
		}
	}
	
	value_type& operator[](size_t index) const
	{
		if (index>=size_)
			throw("Out of range");
		
		return vec[index];
	}

	size_t size() const noexcept
	{
		return size_;
	}
	
	bool empty() const noexcept
	{
		if (size_ == 0)
			return true;
		else
			return false;
	}

	void clear() noexcept
	{	
		if (vec != nullptr)
		{
			delete[] vec;
			vec = nullptr;
		}
		size_ = 0;
		capacity_ = 0;
	}

	void resize(size_t new_size) noexcept
	{	
		if (new_size <= capacity_)
			size_ = new_size;
		if (new_size > capacity_)
		{
			capacity_ = new_size * 2;
			value_type* new_vec = new value_type[capacity_];
			for (size_t i = 0; i < size_; i++)
				new_vec[i] = vec[i];
			if (vec != nullptr)
			{
				delete[] vec;
				vec = nullptr;
			}
			vec = new_vec;
			size_ = new_size;
		}		
	}
	
	void resize(size_t new_size, value_type& val) noexcept
	{	
		if (new_size <= capacity_)
		{
			if (new_size > size_)
			{
				for (size_t i = size_; i < new_size; i++)
				vec[i] = val;
			}
			size_ = new_size;
		}
		if (new_size > capacity_)
		{
			capacity_ = new_size * 2;
			value_type* new_vec = new value_type[capacity_];
			for (size_t i = 0; i < size_; i++)
				new_vec[i] = vec[i];
			for (size_t i = size_; i < new_size; i++)
				new_vec[i] = val;
			delete[] vec;
			vec = nullptr;
			vec = new_vec;
			size_ = new_size;
		}		
	}	

	void push_back(value_type element) noexcept
	{
		this->resize(size_+1);
		vec[size_-1] = element;
	}
	
	void pop_back() 
	{
		if (size_ == 0)
			throw ("size equals 0");
		else if (size_ == 1)
			this->clear();
		else
			size_--;
	}

	Iterator begin() noexcept
	{
		return Iterator(vec);
	}
	
	Iterator end() noexcept
	{
		return Iterator(vec + size_);
	}

	RIterator rbegin() noexcept
	{
		return RIterator(vec + size_ - 1);
	}
	
	RIterator rend() noexcept
	{
		return RIterator(vec - 1);
	}
};	


