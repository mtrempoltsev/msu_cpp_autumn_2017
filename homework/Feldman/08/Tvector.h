#pragma once
#include "Titerator.h"
template <class T>
class Tvector{
private:
	T* data_;
	size_t size_;
	size_t capacity_;
	
	
public:
	using iterator =  Titerator<T>;
	using const_iterator = Titerator<const T>;
	using reverse_iterator = ReverseTiterator<T>;
	using const_reverse_iterator = ReverseTiterator<const T>;

	Tvector() : data_(nullptr), size_(0), capacity_(0) {}
	Tvector(const Tvector& vec) {
		data_ = new T[vec.capacity_];
		size_ = vec.size_;
		capacity_ = vec.capacity_;
		for (size_t i = 0; i < size_; ++i) {
			data_[i] = vec[i];
		}
	}
	~Tvector() {
		size_ = 0;
		capacity_ = 0;
		if (data_ != nullptr) {
		    delete[] data_;
		    data_ = nullptr;
		}
	}
	explicit Tvector(size_t size) : size_(size), capacity_(size * 2) {
		data_ = new T[capacity_];
	}
	Tvector(size_t size, const T& defaultValue) : Tvector(size) {
		for (size_t i = 0; i < size; ++i) {
			data_[i] = defaultValue;
		}
	}
	bool empty() const noexcept {
		return size_ == 0;
	}

	size_t size() const noexcept {
		return size_;
	}

	iterator begin() const noexcept {
		return iterator(data_);
	}

	iterator end() const noexcept {
		return iterator(data_ + size_);
	}

	reverse_iterator rbegin() const noexcept {
		return reverse_iterator(data_ + size_ - 1);
	}

	reverse_iterator rend() const noexcept {
		return reverse_iterator(data_ - 1);
	}

	iterator cbegin() const noexcept {
		return const_iterator(data_);
	}

	iterator cend() const noexcept {
		return const_iterator(data_ + size_);
	}

	reverse_iterator crbegin() const noexcept {
		return const_reverse_iterator(data_ + size_ - 1);
	}

	reverse_iterator crend() const noexcept {
		return const_reverse_iterator(data_ - 1);
	}

	void resize(size_t size) {
		if (size <= size_)
			return;		
		size_ = size;
		T* tmp = new T[size * 2];
		for (size_t i = 0; i < size_ - 1; ++i) {
			tmp[i] = data_[i];
		}
		if (data_ != nullptr) {
			delete[] data_;
			data_ = nullptr;
		}
		data_ = tmp;
		capacity_ = size * 2;
	}

	void resize(size_t size, const T& defaultValue) { //ПОФИКСИТЬ!!!!
		if (size <= size_)
			return;		
		//size_ = size;
		T* tmp = new T[size * 2];
		for (size_t i = 0; i < size_; ++i) {
			tmp[i] = data_[i];
		}
		for (size_t i = size_; i < size; ++i) {
			tmp[i] = defaultValue;
		}
		
		if (data_ != nullptr) {
			delete[] data_;
			data_ = nullptr;
		}
		data_ = tmp;
		capacity_ = size * 2;
		size_ = size;
		
	}

	void clear() {
		*this = std::move(Tvector());
	}

	void push_back(const T& value) {
		if (data_ == nullptr) {
			*this = std::move(Tvector(32));
			this->size_ = 0;
		}

		if (size_ == capacity_) {
			this->resize(this->size_ + 1);
			this->data_[this->size_ - 1] = value;
			
			
		}

		else 
			this->data_[this->size_++] = value;		
	}

	void pop_back() {
		if (size_ == 1) {
			clear();
		}
		if (size_ > 1) {
			size_--;
		}
	}

	T* data() {
		return data_;
	}
	
	T& operator[] (unsigned int n) {
		if (n >= size_) {
			throw "Out of range\n";
		}

		return data_[n];
	}

	const T& operator[] (unsigned int n)  const {
		return data_[n];
	}

	size_t capacity() const  {
		return capacity_;
	}

	bool operator == (const Tvector<T>& vec) {
		if (size() != vec.size())
			return false;
		for (size_t i = 0; i < size(); ++i) {
			if (data_[i] != vec.data_[i])
				return false;
		}
		return true;
	}

	Tvector& operator=(const Tvector& vec)
	{
		if (*this == vec) 
			return *this;
		if (data_ != nullptr) {
			delete[] data_;
			data_ = nullptr;
		}
		data_ = new T[vec.capacity_];
		size_ = vec.size_;
		capacity_ = vec.capacity_;
		
		
		
		for (size_t i = 0; i < this->size_; ++i)
		{
			data_[i] = vec.data_[i];
		}
		return *this;
	}
	
	




	
	


};
