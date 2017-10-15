#pragma once
#include <vector>

class Slice {
public:
	double& operator[](size_t i);
	double operator[](size_t i) const;

	Slice(double** content, size_t sliceIndex, size_t size);
	Slice() = delete;
	~Slice();
private:
	double** content;

	const size_t size;
	const size_t index;
};