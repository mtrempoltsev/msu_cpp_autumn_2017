#include <iostream>
#include <vector>
#include <math.h>
#include <assert.h>
using namespace std;
//Proxy class
class Row{
public:
	Row(){}
	Row(double* buf, int len_buf){
		vec = buf;
		len = len_buf;
	}
	double& operator[](int j){
		assert(!((j >= len)||(j<0)) && "Index of matrix row out of range");
		return vec[j];
	}
private:
	int len;
	double* vec;
};
//Matrix class
class Matrix{
private:
	size_t columns;
	size_t rows;
	Row row;
	double* matrix;
public:
	//Constructor
	Matrix(int columns_buf, int rows_buf){
		assert(!(columns_buf < 1 || rows_buf < 1)&&"Invalid size of matrix");
		columns = columns_buf;
		rows = rows_buf;
		matrix = new double[columns*rows];
		for (size_t i = 0; i < rows; i++){
			for (size_t j = 0; j < columns; j++){
				matrix[j + i*rows] = 0;
			}
		}
	}
	//Copy constructor
	Matrix(const Matrix& matrix_buf){
		columns = matrix_buf.columns;
		rows = matrix_buf.rows;
		for (size_t i = 0; i < columns*rows; i++){
			matrix[i] = matrix_buf.matrix[i];
		}
	}
	//Destructor
	~Matrix(){
		delete[] matrix;
 	}
	//One index operation
	Row& operator[](size_t i){
		assert(!(i >= rows)&&"Index of matrix out of range");
		row = Row(matrix + (i*columns), columns);
		return row;
	}
	//Multiply by number
	Matrix& operator*= (const double& number){
		for (size_t i = 0; i < columns*rows; i++){
			matrix[i] *= number;
		}
		return *this;
	}
	//Multiply by vector
	Matrix& operator*=(const vector <double>&vect){
		assert(!(columns != vect.size()) && "Matrix and vector arent compatable");
		double* temp = new double[rows];
		for (size_t i = 0; i < rows; i++) temp[i] = 0;
		for (size_t i = 0; i < rows; i++){
			for (size_t j = 0; j < columns; j++){
				temp[i] += matrix[j + i*rows] * vect[j];
			}
		}
		delete[] matrix;
		columns = 1;
		matrix = new double[rows*columns];
		for (size_t i = 0; i < rows; i++){
			matrix[i] = temp[i];
		}
		delete[] temp;
		return *this;
	}
	//Matrix assignment
	Matrix operator= (Matrix& matrix_buf){
		columns = matrix_buf.columns;
		rows = matrix_buf.rows;
		for (size_t i = 0; i < columns*rows; i++){
			matrix[i] = matrix_buf.matrix[i];
		}
		return *this;
	}
	//Matrix equal operator
	bool operator== (const Matrix& matrix_compare){
		if (columns != matrix_compare.columns || rows != matrix_compare.rows) return false;
		for (size_t i = 0; i < columns*rows; i++){
			if (matrix[i] != matrix_compare.matrix[i]) return false;
		}
		return true;
	}
	//Matrix not equal operator
	bool operator!= (const Matrix& matrix_compare){
		return !(*this == matrix_compare);
	}
	size_t sizeCol(){
		return columns;
	}
	size_t sizeRow(){
		return rows;
	}
	void print(){
		for (size_t i = 0; i < rows; i++){
			for (size_t j = 0; j < columns; j++){
				cout << matrix[j + i*columns] << "  ";
			}
			cout << endl;
		}
	}
};

bool checkMatrixCreation(){
	Matrix m(2, 2);
	for (size_t i = 0; i < m.sizeRow(); i++){
		for (size_t j = 0; j < m.sizeCol(); j++){
			m[i][j] = i*m.sizeRow() + j;
		}
	}
	int columns = m.sizeCol();
	int rows = m.sizeRow();
	if ((m[0][0]==0)&&(m[0][1]==1)&&(m[1][0]==2)&&(m[1][1]==3)&&(columns==2)&&(rows==2)){
		return true;
	}
	else{
		return false;
	}
}
bool checkMatrixMultiplyByNumber(){
			Matrix m(2, 2);
	for (size_t i = 0; i < m.sizeRow(); i++){
		for (size_t j = 0; j < m.sizeCol(); j++){
			m[i][j] = i*m.sizeRow() + j;
		}
	}
	m*=2;
	if ((m[0][0]==0)&&(m[0][1]==2)&&(m[1][0]==4)&&(m[1][1]==6)){
		return true;
	}
	else{
		return false;
	}
}
bool checkMatrixMultiplyByVector(){
	Matrix m(2, 2);
	for (size_t i = 0; i < m.sizeRow(); i++){
		for (size_t j = 0; j < m.sizeCol(); j++){
			m[i][j] = i*m.sizeRow() + j;
		}
	}
	vector <double> v(2);
	for (size_t i=0; i<v.size(); i++) v[i]=i;
	m*=v;
	if ((m[0][0]==1)&&(m[1][0]==3)){
		return true;
	}
	else{
		return false;
	}
}	
bool checkEqualMatrix(){
	Matrix m1(2,2);
	Matrix m2(2,2);
	for (size_t i = 0; i < m1.sizeRow(); i++){
		for (size_t j = 0; j < m1.sizeCol(); j++){
			m1[i][j] = i*m1.sizeRow() + j;
			m2[i][j] = i*m2.sizeRow() + j;
		}
	}
	if (m1==m2){
		return true;
		}
	else{
		return false;
	}
}
	
int main(){
	if (checkMatrixCreation()){
			cout<<"Test of matrix creation passed"<<endl;
		}
	if (checkMatrixMultiplyByNumber()){
			cout<<"Test of matrix multiply by number passed"<<endl;
		}
	if (checkMatrixMultiplyByVector()){
				cout<<"Test of matrix multiply by vector passed"<<endl;
		}
	if (checkEqualMatrix()){
			cout<<"Test of equal matrix passed"<<endl;
		}
}
