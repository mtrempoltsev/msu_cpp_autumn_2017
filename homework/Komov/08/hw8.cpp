#include <cassert>   // assert
#include <memory>    // unique_ptr
#include <algorithm> // fill, move(ii..ii -> oi), min
#include <iterator>  // distance, reverse_iterator
#include <vector>    // for testing
#include <utility>   // std::move(o)

template<typename T>
class Vector {
	std::unique_ptr<T[]> data;
	size_t siz, capacity;

	// decide whether to enlarge/shrink the array
	// do so in increments of 3/2
	// if needed, move in the C++ way
	// update size and capacity to reflect any changes
	void ensure(size_t want) {
		static const int cap_num = 3, cap_den = 2;
		if (want > capacity && want < capacity * cap_num / cap_den) {
			// allocate to at least 3/2 of current capacity to save on linear operations
			capacity = capacity * cap_num / cap_den;
		} else if (want <= capacity && want > capacity * cap_den / cap_num) {
			// don't bother if shrinking but requested size is > 2/3 of capacity
			siz = want;
			return;
		} else {
			// honour "big" changes exactly as requested
			capacity = want;
		}

		T* new_data = new T[capacity]; // note: we're wasting O(n) on default initialization
		// move only what we need and can fit in new_data
		std::move(data.get(), data.get() + std::min(siz, want), new_data);
		data.reset(new_data); // frees old data
		siz = want;
	}

public:
	// we're just lucky that random access forward iterator was modeled on pointer
	// note: even std::disance works as expected
	typedef T *iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;

	Vector(size_t size = 0, const T& init = T()) : siz(0), capacity(0) {
		ensure(size);
		if (size) // need to fill the newly obtained space with something specific
			std::fill_n(data.get(), siz, init);
	}

	template<typename II>
	Vector(II first, II last) : siz(0), capacity(0) {
		// NOTE: takes additional O(n) unless it's a random access iterator
		ensure(std::distance(first, last));
		std::copy(first, last, data.get());
	}

	Vector& operator=(const Vector & other) {
		ensure(other.siz);
		std::copy_n(other.data.get(), other.siz, data.get());
		return *this;
	}

	Vector (const Vector & other) : siz(0), capacity(0) {
		*this = other;
	}

	Vector& operator=(Vector && other) {
		siz = other.siz;
		capacity = other.capacity;
		std::swap(data, other.data); // destructor will clean up
		return *this;
	}

	Vector(Vector && other) : siz(0), capacity(0) {
		*this = std::move(other);
	}

	T& operator[](size_t i) {
		return data[i]; // cppreference: No bounds checking is performed.
	}

	void push_back(const T& val) {
		ensure(siz+1); // increase size by 1
		data[siz-1] = val; // siz-1 is the index of last element
	}

	void pop_back() {
		ensure(siz-1);
	}

	bool empty() const {
		return !siz;
	}

	size_t size() const {
		return siz;
	}

	void clear() {
		ensure(0);
	}

	iterator begin() {
		return data.get();
	}

	iterator end() {
		return data.get() + siz;
	}

	reverse_iterator rbegin() {
		return reverse_iterator(data.get() + siz);
	}

	reverse_iterator rend() {
		return reverse_iterator(data.get());
	}

	void resize(size_t new_size, const T& val = T()) {
		size_t old_size = siz;
		ensure(new_size);
		if (new_size > old_size)
			std::fill(data.get() + old_size, data.get() + new_size, val);
	}
};

int main() {
	Vector<int> v((size_t)55, 999);
	assert(v.size() == 55);
	assert(v[54] == 999);
	{
		std::vector<int> w {1, 2, 3, 4, 5};
		Vector<int> x{w.begin(), w.end()};
		assert(x.size() == w.size());
		for (size_t i = 0; i < w.size(); i++)
			assert(x[i] == w[i]);

		Vector<int> y{x};
		assert(y.size() == x.size());
		for (size_t i = 0; i < x.size(); i++)
			assert(y[i] == x[i]);

		v = std::move(y);
	}

	assert(v.size() == 5);

	v.push_back(10);
	assert(v[v.size()-1] == 10);
	v.pop_back();
	assert(v.size() == 5);
	v.clear();
	assert(v.size() == 0);

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);

	v.resize(10, -1);

	std::vector<int> w{v.begin(), v.end()};
	auto vit = v.rbegin();
	auto wit = w.rbegin();

	while (wit != w.rend()) {
		assert(*vit == *wit);
		wit++;
		vit++;
	}

	assert(vit == v.rend());

	return 0;
}
