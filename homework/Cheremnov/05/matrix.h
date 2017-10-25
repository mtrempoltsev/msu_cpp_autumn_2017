#pragma once
using namespace std;
#include <iostream>
#include <vector>
#include <cassert>
template<typename T>
class Matrix
{
	//Proxy class for notconstant referring
	template<typename M, typename L>
	class Row
	{
		public:
			//Constructor of class Row. Row - is number of current row. 
			// matrix - link to object of Matrix class
			Row(size_t row, M& matrix)
			: cur_row(row), matrix_obj(matrix) {}
			//Get the link to the element with the specified column from this row
			L& operator[](size_t column) {
				//Check if the index is out of range
				if (column >= matrix_obj.columns) {
					assert(!"columns' index out of range");
				}
				//Find the index of the element and return it
				return matrix_obj.data[cur_row * matrix_obj.columns + column];
			}	
			private:
				// Which row we are processing
				size_t cur_row;
				// With which object of class Matrix we are working
				M& matrix_obj;
	};
	public:
		//Constructor of class Matrix. Row_nums is number of rows,
		//columns_rows - number of columns
		Matrix(size_t row_num, size_t column_num)
		: rows(row_num), columns(column_num)
		{
			//We reserve place for all elements of Matrix
			data.resize(row_num * column_num);
			//Assign to zero all the elements of vector
			for(size_t i = 0; i < row_num * column_num; i++){
				data[i] = 0;
			}
		}
		//Function for returning number of rows
		size_t row_number(){
			return rows;
		}
		//Function for returning number of columns
		size_t column_number(){
			return columns;
		}
		//Function returns the object of proxy class, used for processing
		//operator [][]
		Row<Matrix, T> operator[] (size_t row){
			//Check if the index is out of range
			if(row >= rows){
				assert(!"rows' index out of range");
			}
			return Row<Matrix, T>(row, *this);
		}
		//Multiplicate matrix and vector
		Matrix operator* (const vector<T> vect) {
			//Check if we can multiplicate
			if(vect.size() != columns && vect.size() != rows){
				assert(!"size of vector doesn't match neither number of columns, nor number of rows");
			}
			//If we multiplicate the vector as matrix * vector
			if(vect.size() == columns){
				//Create new Matrix for assigning result to it
				Matrix res(rows, 1);
				//Get result based on the rules of multiplication of matrix and vector
				for (size_t i = 0; i < rows; i++) {
					for(size_t j = 0; j < columns; j++){
						res.data[j] += data[i * columns + j] * vect[j];
					}
				}
				//Return new object of Matrix class
				return res;
			} else{
				//Create new Matrix for assigning result to it
				Matrix res(1, columns);
				//Get result based on the rules of multiplication of matrix and vector
				for (size_t i = 0; i < rows; i++) {
					for(size_t j = 0; j < columns; j++){
						res.data[i] += data[i * columns + j] * vect[j];
					}
				}
				//Return new object of Matrix class
				return res;
			}

		}
		//Multiplicate matrix and vector and apply result to this matrix
		Matrix& operator*= (const vector<T> vect) {
			//Check if we can multiplicate
			if(vect.size() != columns && vect.size() != rows){
				assert(!"size of vector doesn't match neither number of columns, nor number of rows");
			}
			//Create temporary vector for data
			vector<T> tmp;
			//If we multiplicate the vector as matrix * vector
			if(vect.size() == columns){
				//The size of tmp is rows
				tmp.resize(rows);
				for(int i = 0; i < rows; i++){
					tmp[i] = 0;
				}
				//Get result based on the rules of multiplication of matrix and vector
				for (size_t i = 0; i < rows; i++) {
					for(size_t j = 0; j < columns; j++){
						tmp[i] += data[i * columns + j] * vect[j];
					}
				}
				//Now the number of columns is 1
				columns = 1;
				//Then we move the values from the tmp array to data array
				data.resize(rows);
				for(int i = 0; i < rows; i++){
					data[i] = tmp[i];
				}
			} else{ //If we multiplicate vector as vector*matrix
				tmp.resize(columns);
				for(int i = 0; i < columns; i++){
					tmp[i] = 0;
				}
				//Get result based on the rules of multiplication of matrix and vector
				for (size_t i = 0; i < rows; i++) {
					for(size_t j = 0; j < columns; j++){
						tmp[j] += data[i * columns + j] * vect[j];
					}
				}
				//Then we move the values from the tmp array to data array
				data.resize(columns);
				//Now number of rows is 1
				rows = 1;
				for(size_t i = 0; i < columns; i++){
					data[i] = tmp[i];
				}
			}
			//Return this object of Matrix class
			return *this;
		}
		//Multiplicate matrix and number
		Matrix operator* (T x){
			//Create new Matrix for assigning result to it
			Matrix res(rows, columns);
			//Just multiplicate every element to x
			for (size_t i = 0; i < data.size(); i++) {
				res.data[i] = x * data[i];
			}
			//Return new object of Matrix class
			return res;
		}
		//Multiplicate matrix and number and apply to this matrix
		Matrix& operator*= (T x){
			//Just multiplicate every element to x
			for (size_t i = 0; i < data.size(); i++) {
				data[i] *= x;
			}
			//Return current object
			return *this;
		}
		//Function for checking matrixes on equality
		bool operator== (Matrix &m){
			//If matrixes are different sizes, they couldn't be equal
			if(rows != m.row_number() || columns != m.column_number()){
				return 0;
			}
			for(size_t i = 0; i < rows; i++){
				for(size_t j = 0; j < columns; j++){
					//If one elements isn't equal, matrixes aren't equal
					if(data[i * columns + j] != m[i][j]){
						return 0;
					}
				}
			}
			return 1;
		}
		//Function for checking matrixes on inequality
		bool operator!= (Matrix &m){
			return !(*this == m);
		}
		//This function copies the Matrix object
		//Matrix m1
		//Matrix m2 = m1 
		Matrix(const Matrix& m) {
			rows = m.rows;
			columns = m.columns;
			data.resize(rows * columns);
			for (size_t i = 0; i < rows * columns; i++) {
				data[i] = m.data[i];
			}
		}
		//This function copies the Matrix object
		//Matrix m1
		//Matrix m2
		//m2 = m1 
		Matrix& operator=(const Matrix& m) {
			//To avoid the situation when we copy the same objects
			if(this == &m)
				return *this;
			rows = m.rows;
			columns = m.columns;
			data.resize(rows * columns);
			for (size_t i = 0; i < rows * columns; i++) {
				data[i] = m.data[i];
			}
			return *this;
		}
		//This function moves the Matrix object	
		//Matrix m1
		//Matrix m2 = std::move(m2)
		Matrix(Matrix&& m) {
			rows = m.rows;
			columns = m.columns;
			data = m.data;
			m.data.clear();
		}

		//This function moves the Matrix object	
		//Matrix m1
		//Matrix m2
		//m2 = std::move(m1)
		Matrix& operator=(Matrix&& m) {
			if(this == &m)
				return *this;
			rows = m.rows;
			columns = m.columns;
			data = m.data;
			m.data.clear();
			return *this;
		}
		//Function for printing matrix
		void print_matrix(){
			for(size_t i = 0; i < rows; i++){
				for(size_t j = 0; j < columns; j++){
					cout << data[i * columns + j] << " ";
				}
				cout << std::endl;
			}
		}
		//Function for checking if the size of data is really zero
		bool checkzero(){
			return data.size() == 0;
		}
	private:
		//In this vector elements of matrix are stored
		//(Matrix in flattened form)
		vector <T> data;
		//Number of rows and columns of matrix
		size_t rows, columns;
};
