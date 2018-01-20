#include <cassert> // assert
#include <cstddef> // size_t
#include <limits>  // numeric_limits<size_t>
#include <memory>  // unique_ptr
#include <vector>  // vector
#include <cstring> // memcpy
#include <utility> // swap, move

template <typename T>
class Matrix {
	
	std::unique_ptr<T[]> data; 
	size_t cls, rws;

public:
	Matrix(std::size_t cols, std::size_t rows) : cls(cols), rws(rows) {
		
		assert(cols * rows > 0);
		assert(cols < std::numeric_limits<std::size_t>::max() / rows); // overflow 
		data.reset(new T[cols * rows]);
	}

	Matrix(const Matrix & other) {
		
		*this = other;
	}

	Matrix(Matrix && other) {
		
		*this = std::move(other);
	}

	Matrix& operator=(const Matrix & other) {
		
		if (this == &other) 
			return *this;
		
		cls = other.cls;
		rws = other.rws;
		data.reset(new T[cls*rws]);
		std::memcpy(data.get(), other.data.get(), cls*rws*sizeof(T));
		
		return *this;
	}

	Matrix& operator=(Matrix && other) {
		
		if (this == &other) 
			return *this;

		cls = other.cls;
		rws = other.rws;
		std::swap(data, other.data); 
		
		return *this;
	}

	size_t cols() const { return cls; }
	size_t rows() const { return rws; }

	class Column {
		
		friend class Matrix;
		T * data;
		const size_t size;

		Column(T * data_, std::size_t size_) : data(data_), size(size_) {}

	public:
		
		T& operator[](size_t i) const {
			assert(i < size);
			return data[i];
		}
	};

	Column operator[](size_t col) const {
		
		assert(col < cls);
		return Column(&data[col*rws], rws);
	}

	Matrix& operator*=(T scalar) {
		
		for (std::size_t i = 0; i < rws*cls; i++)
			data[i] *= scalar;
		
		return *this;
	}

	bool operator==(const Matrix & other) {
		
		assert(cls == other.cls);
		assert(rws == other.rws);
		
		for (std::size_t i = 0; i < rws*cls; i++)
			if (data[i] != other.data[i]) return false;

		return true;
	}

	bool operator!=(const Matrix & other) {
		
		return !(*this == other);
	}
};

template<typename T>
std::vector<T> operator*(const Matrix<T> & lhs, const std::vector<T> & rhs) {
	
	assert(lhs.rows() == rhs.size()); // vector matches and "eats" rightmost dimension

	std::vector<T> ret;
	ret.resize(lhs.cols()); // and the leftmost dimension is left

	for (std::size_t i = 0; i < lhs.cols(); i++) {
		ret[i] = 0;
		
		for (std::size_t j = 0; j < lhs.rows(); j++)
			ret[i] += lhs[i][j]*rhs[j];
	}

	return ret;
}

template<typename T>
std::vector<T> operator*(const std::vector<T> & lhs, const Matrix<T> & rhs) {
	
	assert(lhs.size() == rhs.cols()); // vector matches leftmost dimension

	std::vector<T> ret;
	ret.resize(rhs.rows()); // result is of rightmost dimension

	for (std::size_t i = 0; i < rhs.rows(); i++) {
		ret[i] = 0;
		
		for (std::size_t j = 0; j < rhs.cols(); j++)
			ret[i] += rhs[j][i]*lhs[j];
	}

	return ret;
}

int main() {
	
	Matrix<double> m(3,4);
	assert(m.cols() == 3);
	assert(m.rows() == 4);

	m[0][0] = 1;
	m[0][1] = 2;
	m[0][2] = 3;
	m[0][3] = 4;
	m[1][0] = 5;
	m[1][1] = 6;
	m[1][2] = 7;
	m[1][3] = 8;
	m[2][0] = 9;
	m[2][1] = 10;
	m[2][2] = 11;
	m[2][3] = 12;
	assert(m[2][3] == 12);

	std::vector<double> left={1,2,3}, right={1,2,3,4}, lp = left*m, rp = m*right;

	assert(lp.size() == 4);
	assert(rp.size() == 3);
	/*
	> (m <- matrix(1:12, nrow=4, ncol=3, byrow=F))
		 [,1] [,2] [,3]
	[1,]    1    5    9
	[2,]    2    6   10
	[3,]    3    7   11
	[4,]    4    8   12
	> m %*% l
		 [,1]
	[1,]   38
	[2,]   44
	[3,]   50
	[4,]   56
	> r %*% m
		 [,1] [,2] [,3]
	[1,]   30   70  110
	-- R has different opinion about cols & rows
	*/
	assert(lp[0] == 38);
	assert(lp[1] == 44);
	assert(lp[2] == 50);
	assert(lp[3] == 56);

	assert(rp[0] == 30);
	assert(rp[1] == 70);
	assert(rp[2] == 110);

	m *= 2;
	assert(m[0][0] == 2);
	assert(m[0][1] == 4);
	assert(m[0][2] == 6);
	assert(m[0][3] == 8);
	assert(m[1][0] == 10);
	assert(m[1][1] == 12);
	assert(m[1][2] == 14);
	assert(m[1][3] == 16);
	assert(m[2][0] == 18);
	assert(m[2][1] == 20);
	assert(m[2][2] == 22);
	assert(m[2][3] == 24);

	Matrix<double> n(3,4);
	n[0][0] = 1;
	n[0][1] = 2;
	n[0][2] = 3;
	n[0][3] = 4;
	n[1][0] = 5;
	n[1][1] = 6;
	n[1][2] = 7;
	n[1][3] = 8;
	n[2][0] = 9;
	n[2][1] = 10;
	n[2][2] = 11;
	n[2][3] = 12;
	assert(m != n);
	n *= 2;
	assert(m == n);

	Matrix<double> k{m};
	assert(k == m);
	n *= 2;
	k = n;
	assert(k == n);

	{
		Matrix<double> l(2,3);
		l[0][0] = 1;
		l[0][1] = 2;
		l[0][2] = 3;
		l[1][0] = 4;
		l[1][1] = 5;
		l[1][2] = 6;
		k = std::move(l);
		Matrix<double> o(std::move(k));
		m = o;
	}
	
	assert(m.cols() == 2);
	assert(m.rows() == 3);
	assert(m[0][0] == 1);
	assert(m[0][1] == 2);
	assert(m[0][2] == 3);
	assert(m[1][0] == 4);
	assert(m[1][1] == 5);
	assert(m[1][2] == 6);

	return 0;
}
