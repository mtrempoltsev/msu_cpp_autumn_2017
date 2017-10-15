#include "Row.h"
#include <cassert>

Row::Row(std::size_t s) : size_(s)
{
	vector_.resize(s);	
}

double& Row::operator[](std::size_t i)
{
	assert(i < vector_.size());
	return vector_[i];
}

const double& Row::operator[](std::size_t i) const
{
	assert(i < vector_.size());
	return vector_[i];
}

Row::~Row()
{
}
