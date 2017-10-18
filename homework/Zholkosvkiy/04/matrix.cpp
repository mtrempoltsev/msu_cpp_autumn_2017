#include <iostream>
#include <typeinfo>
#include <vector>
#include <math.h>
using namespace std;

class Row_proxy
{
	public:

	int row_size;
	double* row;
	Row_proxy(){}
	Row_proxy(double* c, int len)
	{
		Row_proxy::row = c;
		Row_proxy::row_size = len;
	}

	void set(double* c, int len)
	{
		Row_proxy::row = c;
		Row_proxy::row_size = len;
	}

	double &operator[](size_t j)
	{
		if (j >= row_size)
		{
			throw runtime_error("Error");
		}
		return row[j];
	}
};

class Matrix
{
private:
	int rows;
	int cols;
	Row_proxy row;
	double* data;

public:
	//constructor
	Matrix(int rows, int cols)
		{
		if ((rows < 1) || (cols < 1))
		{
			throw runtime_error("Error");
		}
		Matrix::rows = rows;
		Matrix::cols = cols;
		//the first index is column, the second - row
		data = new double[cols*rows];

		for(int i=0; i<rows; i++)
			for(int j=0; j<cols; j++)
				set(i,j, 0);
	}
	//copy matrix
	Matrix(const Matrix& orig)
	{
		cols = orig.cols;
		rows = orig.rows;

		for (int i=0; i<orig.cols * orig.rows; i++)
		{
			data[i] = orig.data[i];
		}
	}
	~Matrix()
	{
		delete[] data;
	}
	//matrix[i][j] - returns column i, return element j

	//Read from the matrix
	Row_proxy& operator[](size_t i)
	{
		if (i>=rows)
		{
			throw runtime_error("Error");
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
			throw runtime_error("Error");
		}

		double* temp;
		temp = new double[rows];

		for(int i=0; i<rows; i++)
		{
			temp[i] = 0;
			for(int j=0; j<cols; j++)
			{
				temp[i] += get(i,j)*v[j];
			}
		}
		cols = 1;

		delete[] data;
		data = new double[rows];
		for(int i=0; i<rows; i++)
		{
			data[i] = temp[i];
		}
		delete[] temp;
		return *this;
	}

	//comparison
	Matrix operator= (Matrix& other)
	{
		cols = other.cols;
		rows = other.rows;

		for (int i=0; i<cols*rows; i++)
		{
			data[i] = other.data[i];
		}
		return *this;
	}

	bool operator==(const Matrix& other)
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
			throw runtime_error("Error");
			return 0;
		}
		return data[i*cols + j];
	}

	//set value
	void set(size_t i, size_t j, double val)
	{
		if ((i >= rows) || (j >= cols))
		{
			throw runtime_error("Error");
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
	Matrix m(2, 3);
	m[0][0] = 1;
	m[0][1] = 2;
	m[0][2] = 3;
	m[1][0] = 4;
	m[1][1] = 5;
	m[1][2] = 6;

	int s=0;
	try
	{
		s += check(m[0][0] == 1);
		s += check(m[0][1] == 2);
		s += check(m[0][2] == 3);
		s += check(m[1][0] == 4);
		s += check(m[1][1] == 5);
		s += check(m[1][2] == 6);

		m[1][2] = 100;

		s += check(m[1][2] == 100);

		m[1][2] = 6;
		vector<double> v = {1, 5,9};
		m *= v; //(38,83)

		Matrix m1(2,1);
		m1[0][0] = 38;
		m1[1][0] = 83;
		s += check(m1 == m);

		m *= 3;
		s += check (m[0][0] == 114);
		s += check (m[1][0] == 249);

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
