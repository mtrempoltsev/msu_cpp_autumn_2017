#pragma once
#include <vector>
#include <cassert>
class Matrix;

class Row {
public:
	std::vector<double> row;
	unsigned int cols;
	Row(int cols_, double val) :cols(cols_){
		for (size_t i = 0; i < cols; ++i)
			row.push_back(val);
	}
	double& operator [] (size_t col) {
		assert(col < cols);
		return row[col];
	}
	friend Matrix;
};



class Matrix
{
public:
	Matrix(int rows_, int columns_);
	~Matrix();
	unsigned int get_rows();
	unsigned int get_columns();
	Row& operator [](unsigned int row); 
	Matrix& operator *= (int val);
	Matrix& operator *= (std::vector<double> src);
	bool operator == (Matrix& val);
	bool operator != (Matrix& val);
private:
	unsigned int rows;
	unsigned int columns;
	std::vector<Row> matrix;




};






