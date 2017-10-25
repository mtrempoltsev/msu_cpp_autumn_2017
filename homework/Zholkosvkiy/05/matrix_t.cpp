#include <iostream>
#include <typeinfo>
#include <vector>
#include <math.h>
using namespace std;

template <typename T>
class Row_proxy
{
	public:

	int row_size;
	T* row;
	Row_proxy(){}
	Row_proxy(T* c, size_t len)
	{
		Row_proxy::row = c;
		Row_proxy::row_size = len;
	}

	void set(T* c, size_t len)
	{
		Row_proxy::row = c;
		Row_proxy::row_size = len;
	}

	T &operator[](size_t j)
	{
		if (j >= row_size)
		{
			cout << j << ", " << row_size << endl;
			throw runtime_error("Error");
		}
		return row[j];
	}
};

template <typename T>
class Matrix
{
private:
	int rows;
	int cols;
	Row_proxy<T> row;
	T* data;

public:
	//constructor
	Matrix(size_t rows, size_t cols)
	{
		if ((rows < 1) || (cols < 1))
		{
			throw runtime_error("Error1");
		}
		Matrix::cols = cols;
		Matrix::rows = rows;

		//the first index is column, the second - row
		data = new T[cols*rows];

		for(int i=0; i<rows; i++)
			for(int j=0; j<cols; j++)
				set(i,j, 0);
	}



	Matrix(const Matrix& copied)
	{

		cols = copied.cols;
		rows = copied.rows;

		data = new T[cols*rows];
		std::copy(copied.data, copied.data + cols * rows, data);

	}
	//move
	Matrix(Matrix<T>&& movied)
	{
		data = movied.data;
		rows = movied.rows;
		cols = movied.cols;

		movied.data = nullptr;
		movied.rows = 667;
		movied.cols = 667;
	}


	Matrix<T>& operator=(Matrix<T>&& movied)
	{
		if(this == &movied)
		{
			return *this;
		}
		delete[] data;
		data = movied.data;
		cols = movied.cols;
		rows = movied.rows;

		movied.data = nullptr;
		movied.cols = 0;
		movied.rows = 0;

		return *this;

	}

	//copy
	Matrix& operator=(const Matrix<T>& copied)
	{
		if(this == &copied)
		{
			return *this;
		}
		delete[] data;
		cols = copied.cols;
		rows = copied.rows;

		data = new T[cols*rows];
		std::copy(copied.data, copied.data + cols * rows, data);
		return *this;
	}


	//matrix[i][j] - returns column i, return element j
	//Read from the matrix
	Row_proxy<T>& operator[](size_t i)
	{
		if (i>=rows)
		{
			throw runtime_error("Error2");
		}
		row.set(data + (i*cols), cols);
		return row;
	}
	//multiply by number
	Matrix& operator*=(const double& num)
	{
		for (int i=0; i<cols*rows; i++)
		{
			data[i] *= num;
		}
		return *this;
	}


	//multiply buy vector
	Matrix& operator*=(const vector<double>& v)
	{
		//vector size and number of columns must be equal
		if (cols != v.size() )
		{
			throw runtime_error("Error3");
		}

		T* temp;
		temp = new T[rows];

		for(int i=0; i<rows; i++)
		{
			temp[i] = 0;
			for(int j=0; j<cols; j++)
			{
				temp[i] += get(i,j)*v[j];
			}
		}
		cols = 1;
		data = temp;

		return *this;
	}


	//comparison
	bool operator==(const Matrix<T>& other)
	{
		if (rows != other.rows)
		{
			return false;
		}
		if (cols != other.cols)
		{
			return false;
		}
		for (size_t i=0; i<rows*cols; i++)
		{
			if (data[i] != other.data[i])
			{
				return false;
			}
		}
		return true;
	}
	bool operator !=(const Matrix& other)
	{
		return !(*this == other);
	}

	//get value from the matrix
	double get(size_t i, size_t j)
	{
		if ((i >= rows) || (j >= cols))
		{
			throw runtime_error("Error4");
			return 0;
		}
		return data[i*cols + j];
	}

	//set value
	void set(size_t i, size_t j, double val)
	{
		if ((i >= rows) || (j >= cols))
		{
			throw runtime_error("Error5");
		}
		data[j + i*cols] = val;
	}
	int getCols()
	{
		return cols;
	}
	int getRaws()
	{
		return rows;
	}
	//print the matrix
	void print()
	{
		for (int i=0; i<rows; i++)
		{
			for (int j=0; j<cols; j++)
			{
				cout << get(i, j) << " ";
			}
			cout << endl;
		}
	}

};


int check(bool A)
{
	if (!A)
	{
		return 1;
	}
	return 0;
}

int checkGetSet()
{
	Matrix <double> m(2,3);
	m[0][0] = 1;
	m[0][1] = 2;
	m[0][2] = 3;
	m[1][0] = 4;
	m[1][1] = 5;
	m[1][2] = 6;

	int s=0;
	try
	{

		//check [][]
		s += check(m[0][0] == 1);
		s += check(m[0][1] == 2);
		s += check(m[0][2] == 3);
		s += check(m[1][0] == 4);
		s += check(m[1][1] == 5);
		s += check(m[1][2] == 6);


		m[1][2] = 100;

		s += check(m[1][2] == 100);

		//chech *vector
		m[1][2] = 6;
		vector<double> v = {1, 5,9};
		m *= v; //(38,83)

		Matrix<double> m1(2,1);
		m1[0][0] = 38;
		m1[1][0] = 83;
		s += check(m1 == m);

		//check *=
		m *= 3;
		s += check (m[0][0] == 114);
		s += check (m[1][0] == 249);

		//check move constructor
		Matrix<double> mv1 = m;
		Matrix<double> mv2 = std::move(m);

		s += check(mv1 == mv2);

		//	assigment
		Matrix<double> mv3 = mv1;
		mv2 = std::move(mv1);

			s+= check(mv3 == mv2);

		cout << "There were " << s <<" errors" << endl;
		if (s==0)
		{
			return 0;
		}
	}
	catch (const runtime_error& e)
	{
		cout << "failed" << endl;
	}
	return 1;
}

int main()
{
	int a = checkGetSet();
	return a;
}
