#include <cassert> // assert
#include <cstddef> // size_t
#include <limits>  // numeric_limits<size_t>
#include <memory>  // unique_ptr
#include <vector>  // vector

class Matrix {
	
	std::unique_ptr<double[]> data;
	const std::size_t cls, rws;

public:
	Matrix(std::size_t cols, std::size_t rows) : cls(cols), rws(rows) {
		
		assert(cols * rows > 0);
		assert(cols < std::numeric_limits<std::size_t>::max() / rows); // overflow 
		// Destroys the object currently managed by the unique_ptr (if any) and takes ownership of p.
		data.reset(new double[cols * rows]);
	}

	size_t cols() const { return cls; }
	size_t rows() const { return rws; }

	class Column {
		
		friend class Matrix;
		double * data;
		const size_t size;

		Column(double * data_, std::size_t size_) : data(data_), size(size_) {}

	public:
		
		double& operator[](size_t i) const {
			
			assert(i < size);
			
			return data[i];
		}
	};

	Column operator[](size_t col) const {
		
		assert(col < cls);
		
		return Column(&data[col*rws], rws);
	}

	Matrix& operator*=(double scalar) {
		
		for (std::size_t i = 0; i < rws*cls; i++)
			data[i] *= scalar;
		
		return *this;
	}

	bool operator==(const Matrix & other) {
		// firstly to equalize dimensions
		assert(cls == other.cls);
		assert(rws == other.rws);
		
		for (std::size_t i = 0; i < rws*cls; i++)
			if (data[i] != other.data[i]) 
				return false;

		return true;
	}

	bool operator!=(const Matrix & other) {
		
		return !(*this == other);
	}
};

std::vector<double> operator*(const Matrix & lhs, const std::vector<double> & rhs) {
	// vector matches and "eats" rightmost dimension
	assert(lhs.rows() == rhs.size());
	// and the leftmost dimension is left
	std::vector<double> ret(lhs.cols()); 

	for (std::size_t i = 0; i < lhs.cols(); i++) {
		ret[i] = 0;
		for (std::size_t j = 0; j < lhs.rows(); j++)
			ret[i] += lhs[i][j]*rhs[j];
	}

	return ret;
}

std::vector<double> operator*(const std::vector<double> & lhs, const Matrix & rhs) {
	// vector matches leftmost dimension
	assert(lhs.size() == rhs.cols()); 
	// result is of rightmost dimension
	std::vector<double> ret(rhs.rows()); 

	for (std::size_t i = 0; i < rhs.rows(); i++) {
		ret[i] = 0;
		for (std::size_t j = 0; j < rhs.cols(); j++)
			ret[i] += rhs[j][i]*lhs[j];
	}

	return ret;
}

int main() {
	Matrix m(3,4);
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

	Matrix n(3,4);
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

	return 0;
}
