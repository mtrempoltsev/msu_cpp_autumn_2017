#include <vector>
#include <cassert>

using std::size_t;
using std::vector;

template <class T>
class Proxy
{
	std::vector<T> vec;
public:
	Proxy(size_t length = 1);
	Proxy(const Proxy<T>&);
	Proxy(Proxy<T>&&);
	size_t len() const {return vec.size();}
	T& operator[] (size_t);
	const T& operator[] (size_t) const;
	Proxy& mulnum(T);
	Proxy& mulvec(const std::vector<T>&);
	bool operator == (const Proxy&) const;
	Proxy<T>& operator= (const Proxy<T>&);
	Proxy<T>& operator= (Proxy<T>&&);
};

template <class T>
Proxy<T>::Proxy(size_t length)
{
	if (length == 0) {
		assert(!"Error");
	}
	vec.resize(length);
}

template <class T>
Proxy<T>::Proxy(const Proxy<T>& Proxy)
{
	vec.resize(Proxy.len());
	auto ProxyIt = Proxy.vec.cbegin();
	for (auto it = vec.begin(); it != vec.end(); ++it, ++ProxyIt) {
		*it = *ProxyIt;
	}
}

template <class T>
Proxy<T>::Proxy(Proxy<T>&& Proxy)
{
	vec = Proxy.vec;
}

template <class T> Proxy<T>&
Proxy<T>::operator= (const Proxy<T>& Proxy)
{
	vec.clear();
	vec.resize(Proxy.len());
	auto ProxyIt = Proxy.vec.cbegin();
	for (auto it = vec.begin(); it != vec.end(); ++it, ++ProxyIt) {
		*it = *ProxyIt;
	}
	return *this;
}

template <class T> Proxy<T>&
Proxy<T>::operator= (Proxy<T>&& Proxy)
{
	vec = Proxy.vec;
	return *this;
}

template <class T> T&
Proxy<T>::operator[] (size_t index)
{
	if (index >= vec.size()) {
		assert(!"Error");
	}
	return vec[index];
}

template <class T> const T&
Proxy<T>::operator[] (size_t index) const
{
	if (index >= vec.size()) {
		assert(!"Error");
	}
	return vec[index];
}

template <class T> Proxy<T>&
Proxy<T>::mulnum(T coef)
{
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		*it *= coef;
	}
	return *this;
}

template <class T> Proxy<T>&
Proxy<T>::mulvec(const std::vector<T>& vecCoef)
{
	if (vec.size() != vecCoef.size()) {
		assert(!"Error");
	}
	auto itCoef = vecCoef.cbegin();
	for (auto it = vec.begin(); it != vec.end(); ++it, ++itCoef) {
		*it *= *itCoef;
	}
	return *this;
}

template <class T> bool
Proxy<T>::operator == (const Proxy& Proxy) const
{
	if (vec.size() != Proxy.vec.size()) {
		return false;
	}
	auto it2 = Proxy.vec.cbegin();
	for (auto it1 = vec.begin(); it1 != vec.end(); ++it1, ++it2) {
		if (*it1 != *it2) {
			return false;
		}
	}
	return true;
}
