#include <iostream>
#include <vector>
#include <cassert>

//Matrix implementation

//Proxy class
template<class T>
class Column{
public:

	//n - number of elements in column
	Column(int n){
		column = new T [n];
		n_rows = n;
	}

	~Column(){
		delete [] column;
	}

	//Returns reference to j element of the column
	T& operator[](int j){
		//Check for index out of range
		if(j < 0 || j >= n_rows)
			assert(!"index out of range");

		return column[j];
	}

private:

	int n_rows;      //Number of elements in column
	T* column;  //Array of elements
};

//Main class
template<class T>
class Matrix{
public:
	
	//n - number of columns
	//m - number of rows
	Matrix(int n, int m){
		matrix = new Column<T>* [n];
		for(int i = 0; i < n; i++)
			matrix[i] = new Column<T>(m);

		n_cols = n;
		n_rows = m;
	}

	//Copy constructor
	Matrix(Matrix<T>& m){
		n_cols = m.n_cols;
		n_rows = m.n_rows;

		matrix = new Column<T>* [n_cols];
		for(int i = 0; i < n_cols; i++)
			matrix[i] = new Column<T>(n_rows);

		for(int i = 0; i < n_cols; i++)
			for(int j = 0; j < n_rows; j++)
				(*matrix[i])[j] = m[i][j];
	}

	//Move constructor
	Matrix(Matrix<T>&& m){
		n_cols = m.n_cols;
		n_rows = m.n_rows;

		matrix = m.matrix;

		m.matrix = nullptr;
		m.n_cols = 0;
		m.n_rows = 0;
	}

	~Matrix(){
		for(int i = 0; i < n_cols; i++)
			delete matrix[i];

		delete [] matrix;
	}

	//Returns number of columns
	int get_cols(){
		return n_cols;
	}

	//Returns number of rows
	int get_rows(){
		return n_rows;
	}

	//Returns reference to (i, j) element of matrix
	Column<T>& operator[](int i){
		//Check for out of range
		if(i < 0 || i >= n_cols)
			assert(!"index out of range");

		return *matrix[i];
	}

	//Multiplies matrix by d
	//Returns reference to changed matrix
	Matrix<T>& operator*=(T d){
		for(int i = 0; i < n_cols; i++)
			for(int j = 0; j < n_rows; j++)
				(*matrix[i])[j] *= d;

		return *this;
	}

	//Multiplies matrix by std::vector
	//Returns reference to changed matrix
	Matrix<T>& operator*=(std::vector<T>& v){
		//Check for correct dimensions
		if(v.size() != (uint)n_cols)
			assert(!"vector length != number of columns");

		//Result of multiplication
		Matrix res(1, n_rows);
		
		//Computing the result
		for(int j = 0; j < n_rows; j++){
			res[0][j] = 0;
			for(int i = 0; i < n_cols; i++)
				res[0][j] += (*matrix[i])[j] * v[i];
		}

		//Changing the size of matrix to Nx1
		for(int i = 0; i < n_cols; i++)
			delete matrix[i];

		delete [] matrix;

		matrix = new Column<T>* [1];
		matrix[0] = new Column<T>(n_rows);
		n_cols = 1;

		for(int j = 0; j < n_rows; j++)
			(*matrix[0])[j] = res[0][j];

		return *this;
	}

	//Returns true if matricies have same size and all elements are equal
	bool operator==(Matrix<T>& m){
		//Check if size are the same
		if(n_cols != m.n_cols || n_rows != m.n_rows)
			return false;

		//Check elements
		for(int i = 0; i < n_cols; i++)
			for(int j = 0; j < n_cols; j++)
				if((*matrix[i])[j] != m[i][j])
					return false;

		return true;
	}

	//Returns true if matricies aren't equal
	bool operator!=(Matrix<T>& m){
		return !(*this == m);
	}

	//Copy operator
	Matrix<T>& operator=(Matrix<T>& m){
		if(this == &m)
			return *this;

		for(int i = 0; i < n_cols; i++)
			delete matrix[i];

		delete [] matrix;

		n_cols = m.n_cols;
		n_rows = m.n_rows;

		matrix = new Column<T>* [n_cols];
		for(int i = 0; i < n_cols; i++)
			matrix[i] = new Column<T>(n_rows);

		for(int i = 0; i < n_cols; i++)
			for(int j = 0; j < n_rows; j++)
				(*matrix[i])[j] = m[i][j];

		return *this;
	}

	//Move operator
	Matrix<T>& operator=(Matrix<T>&& m){
		if(this == &m)
			return *this;

		for(int i = 0; i < n_cols; i++)
			delete matrix[i];

		delete [] matrix;

		n_cols = m.n_cols;
		n_rows = m.n_rows;

		matrix = m.matrix;

		m.matrix = nullptr;
		m.n_cols = 0;
		m.n_rows = 0;

		return *this;
	}

private:

	int n_cols;       //Number of columns
	int n_rows;       //Number of rows
	Column<T>** matrix;  //Array of Column pointers
};

//Tests
void check(bool value){
    if (!value)
        std::cout << "error" << std::endl;
}

//Checks [][] operator
void CheckGetSet(){
	Matrix<double> m(2, 2);

	m[0][0] = 0;
	m[0][1] = 1;
	m[1][0] = 2;
	m[1][1] = 3;

	check(m[0][0] == 0);
	check(m[0][1] == 1);
	check(m[1][0] == 2);
	check(m[1][1] == 3);
}

//Checks *= by number function
void CheckMultNumber(){
	Matrix<double> m(1, 2);

	m[0][0] = 1;
	m[0][1] = 2;

	m *= 2;

	check(m[0][0] == 2);
	check(m[0][1] == 4);
}

//Checks *= by vector function
void ChecMultVector(){
	Matrix<double> m(2, 2);

	m[0][0] = 1;
	m[0][1] = 1;
	m[1][0] = 1;
	m[1][1] = 1;

	std::vector<double> vec = {2, 2};

	m *= vec;

	check(m.get_cols() == 1);
	check(m.get_rows() == 2);
	check(m[0][0] == 4);
	check(m[0][1] == 4);
}

//Checks == and != operators
void CheckEQ(){
	Matrix<double> m1(2, 2), m2(2, 2), m3(3, 2);

	m2[0][0] = m1[0][0] = 1;
	m2[0][1] = m1[0][1] = 1;
	m2[1][0] = m1[1][0] = 1;
	m2[1][1] = m1[1][1] = 1;

	check(m1 == m2); //Equal matricies

	m1[0][0] = 2;

	check(m1 != m2); //Same size but unequal elements

	check(m3 != m1); //Different sizes
}

//Checks get_cols() and get_rows functions
void CheckGetColsRows(){
	Matrix<double> m(2, 2);

	check(m.get_cols() == 2);
	check(m.get_rows() == 2);
}

//Checks copy operator and constructor
void CheckCopyOperConstr(){
	Matrix<double> m1(2, 2);

	m1[0][0] = 1;
	m1[0][1] = 2;
	m1[1][0] = 3;
	m1[1][1] = 4;

	Matrix<double> m2 = m1;

	check(m2[0][0] == 1);
	check(m2[0][1] == 2);
	check(m2[1][0] == 3);
	check(m2[1][1] == 4);

	Matrix<double> m3(1, 1);
	m3 = m1;

	check(m3[0][0] == 1);
	check(m3[0][1] == 2);
	check(m3[1][0] == 3);
	check(m3[1][1] == 4);	
}

//Checks move operator and constructor
void CheckMoveOperConstr(){
	Matrix<double> m1(2, 2);

	m1[0][0] = 1;
	m1[0][1] = 2;
	m1[1][0] = 3;
	m1[1][1] = 4;

	Matrix<double> m2 = std::move(m1);

	check(m2[0][0] == 1);
	check(m2[0][1] == 2);
	check(m2[1][0] == 3);
	check(m2[1][1] == 4);
	check(m1.get_rows() == 0);
	check(m1.get_cols() == 0);

	Matrix<double> m3(1, 1);
	m3 = std::move(m2);

	check(m3[0][0] == 1);
	check(m3[0][1] == 2);
	check(m3[1][0] == 3);
	check(m3[1][1] == 4);
	check(m2.get_rows() == 0);
	check(m2.get_cols() == 0);	
}

int main(){

	CheckGetSet();
	CheckMultNumber();
	ChecMultVector();
	CheckEQ();
	CheckGetColsRows();
	CheckCopyOperConstr();
	CheckMoveOperConstr();

	return 0;
}