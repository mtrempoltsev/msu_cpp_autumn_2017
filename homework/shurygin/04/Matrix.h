#pragma once
#include <vector>
#include "Row.h"

class Matrix
{
public:	
	Matrix(std::size_t rows, std::size_t cols);
	std::size_t GetRows() const { return rows_; }
	std::size_t GetCols() const { return cols_; }
	Row& operator[](std::size_t);	
	Matrix operator*=(double);
	Matrix operator*=(std::vector<double>);
	bool operator==(Matrix) const;
	bool operator!=(Matrix) const;
	~Matrix();
private:
	std::size_t rows_;
	std::size_t cols_;
	std::vector<Row> matrix_;
};
