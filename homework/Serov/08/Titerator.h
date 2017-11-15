template <class T>
class Titerator : public std::iterator<std::random_access_iterator_tag, T>
{
	T* ptr_;
public:
	explicit Titerator(T* ptr) : ptr_(ptr)
	{
	}
	
	bool operator==(const Titerator<T>& other) const
	{
		return ptr_ == other.ptr_;
	}
	
	bool operator!=(const Titerator<T>& other) const
	{
		return !(*this == other);
	}

	T& operator*() const
	{
		return *ptr_;
	}
	
	Titerator& operator++()
	{
		++ptr_;
		return *this;
	}

	Titerator& operator--()
	{
		--ptr_;
		return *this;
	}

	Titerator& operator+=(size_t n)
	{
		ptr_+=n;
		return *this;
	}
	
	Titerator& operator-=(size_t n)
	{
		ptr_-=n;
		return *this;
	}
};

template <class T>
class ReverseTiterator : public std::iterator<std::random_access_iterator_tag, T>
{
	T* ptr_;
public:
	explicit ReverseTiterator(T* ptr) : ptr_(ptr)
	{
	}
	
	bool operator==(const ReverseTiterator<T>& other) const
	{
		return ptr_ == other.ptr_;
	}
	
	bool operator!=(const ReverseTiterator<T>& other) const
	{
		return !(*this == other);
	}

	T& operator*() const
	{
		return *ptr_;
	}
	
	ReverseTiterator& operator++()
	{
		--ptr_;
		return *this;
	}

	ReverseTiterator& operator--()
	{
		++ptr_;
		return *this;
	}

	ReverseTiterator& operator+=(size_t n)
	{
		ptr_-=n;
		return *this;
	}
	
	ReverseTiterator& operator-=(size_t n)
	{
		ptr_+=n;
		return *this;
	}
};
