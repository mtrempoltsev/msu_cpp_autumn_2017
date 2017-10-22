#pragma once
#include <vector>
#include <cassert>

template <class T>
class Row
{
public:
	Row(std::size_t s) : size_(s)
	{
		vector_.resize(s);
	}
	Row(const Row& r)
	{
		size_ = r.size_;
		vector_ = r.vector_;
	}
	Row(Row&& r)
	{
		size_ = std::move(r.size_);
		vector_ = std::move(r.vector_);
	}
	T& operator[](std::size_t i)
	{
		assert(i < vector_.size());
		return vector_[i];
	}
	const T& operator[](std::size_t i) const
	{
		assert(i < vector_.size());
		return vector_[i];
	}
	~Row() {};
private:
	std::vector<T> vector_;
	std::size_t size_;
};

