#include <vector>
#include <cassert>

using std::size_t;

template <class T>
class Row
{
	std::vector<T> vec;
public:
	Row(size_t length = 1);
	Row(const Row<T>&);
	Row(Row<T>&&);

	Row<T>& operator= (const Row<T>&);
	Row<T>& operator= (Row<T>&&);

	size_t getLength() const {return vec.size();}
	T& operator[] (size_t);
	const T& operator[] (size_t) const;
	Row& multByNumber(T);
	Row& multByVector(const std::vector<T>&);
	bool operator== (const Row&) const;
};

template <class T>
Row<T>::Row(size_t length)
{
	if (length == 0) {
		assert(!"could not create a row with zero length");
	}
	vec.resize(length);
}

template <class T>
Row<T>::Row(const Row<T>& row)
{
	vec.resize(row.getLength());
	auto rowIt = row.vec.cbegin();
	for (auto it = vec.begin(); it != vec.end(); ++it, ++rowIt) {
		*it = *rowIt;
	}
}

template <class T>
Row<T>::Row(Row<T>&& row)
{
	vec = row.vec;
}

template <class T> Row<T>&
Row<T>::operator= (const Row<T>& row)
{
	vec.clear();
	vec.resize(row.getLength());
	auto rowIt = row.vec.cbegin();
	for (auto it = vec.begin(); it != vec.end(); ++it, ++rowIt) {
		*it = *rowIt;
	}
	return *this;
}

template <class T> Row<T>&
Row<T>::operator= (Row<T>&& row)
{
	vec = row.vec;
	return *this;
}

template <class T> T&
Row<T>::operator[] (size_t index)
{
	if (index >= vec.size()) {
		assert(!"index out of range");
	}
	return vec[index];
}

template <class T> const T&
Row<T>::operator[] (size_t index) const
{
	if (index >= vec.size()) {
		assert(!"index out of range");
	}
	return vec[index];
}

template <class T> Row<T>&
Row<T>::multByNumber(T coef)
{
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		*it *= coef;
	}
	return *this;
}

template <class T> Row<T>&
Row<T>::multByVector(const std::vector<T>& vecCoef)
{
	if (vec.size() != vecCoef.size()) {
		assert(!"lengths of vectors don't match");
	}
	auto itCoef = vecCoef.cbegin();
	for (auto it = vec.begin(); it != vec.end(); ++it, ++itCoef) {
		*it *= *itCoef;
	}
	return *this;
}

template <class T> bool
Row<T>::operator == (const Row& row) const
{
	if (vec.size() != row.vec.size()) {
		return false;
	}
	auto it2 = row.vec.cbegin();
	for (auto it1 = vec.begin(); it1 != vec.end(); ++it1, ++it2) {
		if (*it1 != *it2) {
			return false;
		}
	}
	return true;
}
