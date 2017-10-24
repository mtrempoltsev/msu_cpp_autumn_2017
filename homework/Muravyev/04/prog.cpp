#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Row{
public:
	Row(int l = 0, double *v = nullptr){
		len = l;
		vector = v;
	}
	~Row(){}
	const double& operator[](int i) const{
		if (i >= len)
			assert(!"index out of range");
		return vector[i];
	}
	double& operator[](int i){
		if (i >= len)
			assert(!"index out of range");
		return vector[i];
	}

private:
	int len;
	double *vector;
};

class Matrix{
public:
	Matrix(int r = 0, int c = 0){
		rows = r;
		cols = c;
		matrix = new double[r*c];
	}
	~Matrix(){
		delete[] matrix;
	}
	const int GetRows() const{
		return rows;
	}
	const int GetCols() const{
		return cols;
	}
	const Row& operator[](int i) const{
		if (i >= rows)
			assert(!"index out of range");
		col = Row(cols, &matrix[i*cols]);
		return col;
	}
	Row& operator[](int i){
		if (i >= rows)
			assert(!"index out of range");
		col = Row(cols, &matrix[i*cols]);
		return col;
	}
	Matrix& operator*=(double a){
		for (int i = 0; i < rows*cols; ++i){
			matrix[i]*=a;
		}
		return *this;
	}
	Matrix& operator*=(vector<double> v){
		if (cols != v.size())
			assert(!"incorrect operation");
		double s;
		double *m = new double[rows];
		for(int i = 0;i < rows;++i){
			s = 0;
			for(int j = 0;j < cols;++j){
				s += matrix[i*cols +j]*v[j];
			}
			m[i] = s;
		}
		delete[] matrix;
		matrix = m;
		cols = 1;
		return *this;
	}
	bool operator==(Matrix m) const{
		if (rows != m.GetRows() || cols != m.GetCols())
			return false;
		for (int i = 0;i < cols*rows;++i){
			if (matrix[i] != m[i/cols][i%cols])
				return false;
		}
		return true;
	}
	bool operator!=(Matrix m) const{
		return !(*this == m);
	}
private:
	int rows;
	int cols;
	double *matrix;
	mutable Row col;
};

void check(bool value)
{
    if (!value)
        cout << "error" << endl;
}

void checkGetSet()
{
    Matrix m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;
    
    check(m[0][0] == 1);  // Проверяем присваивание и сравнение
    check(m[0][1] == 2);  // на равенство
    check(m[0][2] == 3);
    check(m[1][0] == 4);
    check(m[1][1] == 5);
    check(m[1][2] == 6);

    check(m[0][0] != 2);  // Проверяем на неравенство

    m *= 2;         

    check(m[1][2] == 12); // Проверяем умножение на число
    check(m[0][1] == 4);

    m *= 0.5;
    check(m[1][2] == 6);
    vector<double> v(3);
    v[0] = 1;
    v[1] = 0;
    v[2] = 1;
    m *= v;
    check(m[0][0] == 4);  // Проверка умножения на вектор
    check(m[1][0] == 10);

    check(m.GetRows() == 2); // Проверка получения количества строк
    check(m.GetCols() == 1); // и столбцов
}

int main(){
	checkGetSet();
	return 0;
}