#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

template <class T>
class Row{        // Вспомогательный класс "строка"
public:
	Row(int l = 0, T *v = nullptr){
		len = l;
		vector = v;
	}
	~Row(){}
	const T& operator[](int i) const{
		if (i >= len)
			assert(!"index out of range");
		return vector[i];
	}
	T& operator[](int i){
		if (i >= len)
			assert(!"index out of range");
		return vector[i];
	}

private:
	int len;
	T *vector;
};

template <class T>
class Matrix{     // Основной класс "матрица"
public:
	Matrix(int r = 0, int c = 0){
		rows = r;
		cols = c;
		matrix = new T[r*c];
	}
	Matrix(const Matrix<T>& m){  // Конструктор копирования
		delete[] matrix;
		cols = m.GetCols();
		rows = m.GetRows();
		matrix = new T[rows*cols];
		for(int i = 0;i < rows;++i){
			for(int j = 0;j < cols;++j){
				matrix[i*cols+j] = m[i][j];
			}
		}
	}
	Matrix(Matrix<T>&& m){  // Конструктор перемещения
		if (this == &m)
		{
			return;
		}
		rows = move(m.rows);
		cols = move(m.cols);
		delete[] matrix;
		matrix = move(m.matrix);
		m.matrix = nullptr;
		m.rows = 0;
		m.cols = 0;
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
	const Row<T>& operator[](int i) const{
		if (i >= rows)
			assert(!"index out of range");
		col = Row<T>(cols, &matrix[i*cols]);
		return col;
	}
	Row<T>& operator[](int i){
		if (i >= rows)
			assert(!"index out of range");
		col = Row<T>(cols, &matrix[i*cols]);
		return col;
	}
	Matrix<T>& operator*=(T a){
		for (int i = 0; i < rows*cols; ++i){
			matrix[i]*=a;
		}
		return *this;
	}
	Matrix<T>& operator*=(vector<T>& v){
		if (cols != v.size())
			assert(!"incorrect operation");
		T s;
		T *m = new T[rows];
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
	Matrix& operator=(Matrix<T>&& m){ // Оператор перемещения
		if (this == &m)
		{
			return *this;
		}
		rows = move(m.rows);
		cols = move(m.cols);
		delete[] matrix;
		matrix = move(m.matrix);
		m.matrix = nullptr;
		m.rows = 0;
		m.cols = 0;
		return *this;
	}
	Matrix<T>& operator=(const Matrix<T>& m){ // Оператор копирования
		delete[] matrix;
		cols = m.GetCols();
		rows = m.GetRows();
		matrix = new T[rows*cols];
		for(int i = 0;i < rows;++i){
			for(int j = 0;j < cols;++j){
				matrix[i*cols+j] = m[i][j];
			}
		}
		return *this;
	}
	bool operator==(const Matrix<T>& m) const{
		if (rows != m.GetRows() || cols != m.GetCols())
			return false;
		for (int i = 0;i < cols*rows;++i){
			if (matrix[i] != m[i/cols][i%cols])
				return false;
		}
		return true;
	}
	bool operator!=(const Matrix<T>& m) const{
		return !(*this == m);
	}
private:
	int rows;
	int cols;
	T *matrix;
	mutable Row<T> col;
};

void check(bool value){
    if (!value)
        cout << "error" << endl;
}

void checkGetSet(){    // Тест
	Matrix<double> mat;
    Matrix<double> m(2, 3);
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

    mat = m;              // Проверка копирования
    mat[0][0] = 2;
    check(mat[0][0] == 2); 
    check(m[0][0] == 4);  // Проверяем, что объекты не связаны

    check(m.GetRows() == 2); // Проверка получения количества строк
    check(m.GetCols() == 1); // и столбцов
   
    mat = move(m);           // Проверка оператора перемещения
    check(mat[0][0] == 4);


    // Проверяем, что работают шаблоны
    // Делаем то же самое, но с int вместо double
    Matrix<int> imat;
    Matrix<int> im(2, 3);
    im[0][0] = 1;
    im[0][1] = 2;
    im[0][2] = 3;
    im[1][0] = 4;
    im[1][1] = 5;
    im[1][2] = 6;
    
    check(im[0][0] == 1);  // Проверяем присваивание и сравнение
    check(im[0][1] == 2);  // на равенство
    check(im[0][2] == 3);
    check(im[1][0] == 4);
    check(im[1][1] == 5);
    check(im[1][2] == 6);

    check(im[0][0] != 2);  // Проверяем на неравенство

    im *= 2;         

    check(im[1][2] == 12); // Проверяем умножение на число
    check(im[0][1] == 4);

    
    vector<int> iv(3);
    iv[0] = 1;
    iv[1] = 0;
    iv[2] = 1;
    im *= iv;
    check(im[0][0] == 8);  // Проверка умножения на вектор
    check(im[1][0] == 20);

    imat = im;              // Проверка копирования
    imat[0][0] = 2;
    check(imat[0][0] == 2); 
    check(im[0][0] == 8);  // Проверяем, что объекты не связаны

    check(im.GetRows() == 2); // Проверка получения количества строк
    check(im.GetCols() == 1); // и столбцов

	imat = move(im);           // Проверка оператора перемещения
    check(imat[0][0] == 8);
}

int main(){
	checkGetSet();
	return 0;
}