#include "Slice.h"
#include <iostream>

Slice::Slice(double** content, size_t sliceIndex, size_t size) : content(content), index(sliceIndex), size(size) {
	
}

Slice::~Slice() {

}

double& Slice::operator[](size_t i) {
	if (i >= size) {
		throw std::runtime_error(std::string("[Slice]: invalid index: ") + std::to_string(i));
	}
	return content[index][i];
}

double Slice::operator[](size_t i) const {
	if (i >= size) {
		throw std::runtime_error(std::string("[Slice]: invalid index: ") + std::to_string(i));
	}
	return content[index][i];
}