#include "Row.cpp"
#include <cassert>


#include <cassert>


#pragma once
#include <vector>
#include <cassert>



template <class T>
class Matrix
{
public:
	Matrix(int rows_, int columns_) :rows(rows_) ,columns(columns_){
		//assert(rows_ > 0 && columns_ > 0);
		if (rows <=0 || columns <= 0) {
			std::cout << "INVALID MATRIX SIZE" << std::endl;
			exit(1);
		}
		for (size_t i = 0; i < rows; ++i) {
			matrix.push_back(Row<T>(columns,0));
		}
	}
	~Matrix() {}
	
	Matrix(Matrix& val) {
		rows = val.rows;
		columns = val.columns;
		for (size_t i = 0; i < rows; ++i) {
			Row<T> row(columns,0);
			for (size_t j = 0; j < columns; ++j)
				row.row[j] = val.matrix[i][j];
			matrix.push_back(row);
		}
		
	}
	
	
	Matrix& operator= (Matrix &val) {
		if (this == &val)
			return *this;
		rows = val.rows;
		columns = val.columns;
		matrix.clear();
		for (size_t i = 0; i < rows; ++i) {
			Row<T> row(columns,0);
			for (size_t j = 0; j < columns; ++j)
				row.row[j] = val.matrix[i][j];
			matrix.push_back(row);
		}
		return *this;	
	
	}
	
	
	Matrix(Matrix && val) {
		rows = std::move(val.rows);
		columns = std::move(val.columns);
		for (size_t i = 0; i < rows; ++i) {
			Row<T> row = std::move(val.matrix[i]);
			matrix.push_back(row);
			
		}
	
	}
	
	Matrix& operator= (Matrix && val) {
		if (this == &val) 
			return *this;		
		rows = std::move(val.rows);
		columns = std::move(val.columns);
		matrix.clear();
		for (size_t i = 0; i < rows; ++i) {
			Row<T> row = std::move(val.matrix[i]);
			matrix.push_back(row);
			
		}
		return *this;
		
	}
	

		
	unsigned int get_rows() {
		return rows;
	}
	
	unsigned int get_columns() {
		return columns;
	}
	Row<T>& operator [](unsigned int row) {
		if (row >= rows) {
			std::cout << "OUT OF RANGE!" << std::endl;
			exit(1);
		}
		return matrix[row]; 
	}
	
	Matrix& operator *= (T val) {
		for (size_t i = 0; i < rows; ++i) {
			for (size_t j = 0; j < columns; ++j) {
			matrix[i][j] *= val;
			}
		}
		return *this;
	}
	
	Matrix& operator *= (std::vector<T> src) {
		assert(src.size() == columns);
		if (src.size() != columns) {
			std::cout << "OUT OF RANGE!" << std::endl;
			exit(1);
		}
		std::vector<Row<T>> result;
		for (size_t i = 0; i < rows; ++i) {
			double sum = 0;
			for (size_t j = 0; j < columns; ++j) {
				sum += matrix[i][j] * src[j];
			}
			result.push_back(Row<T>(1,sum));
		}
		matrix = result;
		columns = 1;

		return *this;
	}
	bool operator == (Matrix& val) {
		if (rows != val.get_rows() || columns != val.get_columns()){
			std::cout << "OUT OF RANGE!" << std::endl;
			exit(1);
		}
		for (size_t i = 0; i < rows; ++i) {
			for (size_t j = 0; j < columns; ++j) {
				if (matrix[i][j] != val[i][j])
					return false;
			}
		}
		return true;
	}
	bool operator != (Matrix& val) {
		return !(*this == val);
	}
private:
	unsigned int rows;
	unsigned int columns;
	std::vector<Row<T>> matrix;




};

