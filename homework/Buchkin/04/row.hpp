#include <vector>
#include <cassert>

class Row
{
	std::vector<double> vec;
public:
	Row(std::size_t);
	std::size_t getLength() const {return vec.size();}
	double& operator[] (std::size_t);
	Row& multByNumber(double);
	Row& multByVector(const std::vector<double>&);
	bool operator== (const Row&) const;
};

Row::Row(std::size_t length)
{
	if (length == 0) {
		assert(!"could not create a row with zero length");
	}
	vec.resize(length);
}

double&
Row::operator[] (std::size_t index)
{
	if (index >= vec.size()) {
		assert(!"index out of range");
	}
	return vec[index];
}

Row&
Row::multByNumber(double coef)
{
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		*it *= coef;
	}
	return *this;
}

Row&
Row::multByVector(const std::vector<double>& vecCoef)
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

bool
Row::operator == (const Row& row) const
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
