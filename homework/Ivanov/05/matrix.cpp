#include <vector>
#include <cassert>
#include "matrix.h"

using std::size_t;
using std::vector;

Proxy::Proxy(size_t size_check) {
    if(size_check == 0) {
        assert(!"could not create a row with zero size_check");
    }
    vec.resize(size_check);
}

size_t Proxy::getsize() const {
    return vec.size();
}

T& Proxy::operator[] (size_t idx) {
    if(idx >= vec.size()) {
        assert(!"index out of range");
    }
    return vec[idx];
}

Proxy& Proxy::multconst(T c) {
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        *it *= c;
    }
    return *this;
}

Proxy& Proxy::multvect(const vector<T>& mul_vec) {
    if(vec.size() != mul_vec.size()) {
        assert(!"the lengths of the vectors are not identical");
    }
    auto it2 = mul_vec.cbegin();
    for(auto it1 = vec.begin(); it1 != vec.end(); ++it1, ++it2) {
        *it1 *= *it2;
    }
    return *this;
}

bool Proxy::operator== (const Proxy& row) const {
    if(vec.size() != row.vec.size()) {
        return false;
    }
    auto it2 = row.vec.cbegin();
    for(auto it1 = vec.begin(); it1 != vec.end(); ++it1, ++it2) {
        if(*it1 != *it2) {
            return false;
        }
    }
    return true;
}

Proxy::~Proxy() {}


Matrix::Matrix(size_t rows = 0, size_t cols = 0) {
	if(!rows || !cols) {
		assert(!"zero rows or columns");
	}
	vec.resize(rows, Proxy(cols));
}

Matrix::Matrix(const Matrix& copy_from) {
    vec.size() = copy_from.size();
    vec[0].size() = copy_from[0].size();
    for(size_t i = 0; i < vec.size(); i++) {
        for(size_t i = 0; i < vec.size(); i++) {
            vec[i] = copy_from.vec[i];
        }
    }
}

Matrix::Matrix(Matrix&& from) {
    vec = from.vec;
    from.vec = nullptr;
    return *this;
}

Matrix& Matrix::operator= (Matrix&& from) {
    if(this == &from) {
        return *this;
    }
    vec = from.vec;
    vec.size() = copy_from.size();
    vec[0].size() = copy_from[0].size();
    from.vec = nullptr;
    return *this;
}

Matrix& Matrix::operator= (const Matrix& move_from) {
    if(this == &move_from) {
        return *this;
    }
    vec.size() = copy_from.size();
    vec[0].size() = copy_from[0].size();
    for(size_t i = 0; i < _rows * _cols; i++) {
        vec[i] = move_from.vec[i];
    }
    return *this;
}

Proxy& Matrix::operator[] (size_t idx) {
	if(idx >= vec.size()) {
		assert(!"index out of range");
	}
	return vec[idx];
}

size_t Matrix::getcols() const {
    return vec[0].getsize();
}

size_t Matrix::getrows() const {
    return vec.size();
}

Matrix& Matrix::operator*= (T c) {
	for(auto it = vec.begin(); it != vec.end(); it++) {
		it->multconst(c);
	}
	return *this;
}

Matrix& Matrix::operator*= (const vector<T>& mul_vect) {
	for(auto it = vec.begin(); it != vec.end(); ++it) {
		it->multvect(mul_vect);
	}
	return *this;
}

bool Matrix::operator== (Matrix& matrix) {
	if(getrows() != matrix.getrows() || getcols() != matrix.getcols()) {
		return false;
	}
	auto it2 = matrix.vec.cbegin();
	for(auto it1 = vec.begin(); it1 != vec.end(); ++it1, ++it2) {
		if(!(*it1 == *it2)) {
			return false;
		}
	}
	return true;
}

bool Matrix::operator!= (Matrix& matrix) {
    return !(*this == matrix);
}

Matrix::~Matrix() {
}