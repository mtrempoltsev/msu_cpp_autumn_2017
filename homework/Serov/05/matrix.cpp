#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

template <class T>
class Row{ //понадобится для реализации [][]
public:
	vector <T> row;	
	size_t size;
	Row(size_t columns, T value){ //аналогично простому вектору
		assert(columns>0);
		row.resize(columns);
		size=columns;
		for (size_t i=0;i<columns;i++)
			row[i]=value;
	}
	T& operator[](size_t index2){  //вторые скобки
		assert(index2<size);
		return row[index2];
	}
	

};

template <class T>
class Matrix{
public:
	Matrix(size_t rows, size_t columns);
	Matrix(Matrix& copied);
	Matrix& operator=(Matrix& copied);
	Matrix(Matrix&& moved);
	Matrix& operator=(Matrix&& moved);
	size_t get_number_of_rows();  
	size_t get_number_of_columns();
	Row<T>& operator[](size_t index1);  //первые скобки
	Matrix& operator*=(double multiplier); //умножение на число
	Matrix& operator*=(vector<double> vecMultiplier); //умножение на вектор
	bool operator==(Matrix& M_compare);
	bool operator!=(Matrix& M_compare);
private:
	size_t number_of_rows;
	size_t number_of_columns;
	vector <Row<T>> M;
};

template <class T>
Matrix<T>::Matrix(size_t rows,size_t columns){
	for (size_t i=0;i<rows;i++){
		M.push_back(Row<T>(columns,0));
	}	
	number_of_rows=rows;
	number_of_columns=columns;
}	

template <class T>
Matrix<T>::Matrix(Matrix& copied){
	number_of_rows=copied.number_of_rows;
	number_of_columns=copied.number_of_columns;
	for (size_t i=0;i<number_of_rows;i++){
		Row<T> row(number_of_columns,0);
		for (size_t j=0; j<number_of_columns;j++){
			row.row[j]=copied.M[i][j];		
		}
		M.push_back(row);	
	}
}

template <class T>
Matrix<T>& Matrix<T>::operator=(Matrix& copied){
	if (this==&copied)
		return *this;
	M.clear();
	number_of_rows=copied.number_of_rows;
	number_of_columns=copied.number_of_columns;
	for (size_t i=0;i<number_of_rows;i++){
		Row<T> row(number_of_columns,0);
		for (size_t j=0; j<number_of_columns;j++){
			row.row[j]=copied.M[i][j];		
		}
		M.push_back(row);	
	}
	return *this;	
}

template <class T>
Matrix<T>::Matrix(Matrix&& moved){
	number_of_rows=move(moved.number_of_rows);
	number_of_columns=move(moved.number_of_columns);
	for (size_t i=0; i<number_of_rows; i++){
		M.push_back(move(moved.M[i]));
	}
	moved.M.clear();
	moved.number_of_columns=0;
	moved.number_of_rows=0;	
}

template <class T>
Matrix<T>& Matrix<T>::operator=(Matrix&& moved){
	if (this==&moved)
		return *this;
	number_of_rows=move(moved.number_of_rows);
	number_of_columns=move(moved.number_of_columns);
	M.clear();
	for (size_t i=0; i<number_of_rows; i++){
		Row<T> row=move(moved.M[i]);
		M.push_back(row);
	}
	moved.M.clear();
	moved.number_of_columns=0;
	moved.number_of_rows=0;
	return *this;
}

template <class T>
size_t Matrix<T>::get_number_of_rows(){
	return number_of_rows;
}

template <class T>
size_t Matrix<T>::get_number_of_columns(){
	return number_of_columns;
}

template <class T>
Row<T>& Matrix<T>::operator[](size_t index1){
	assert(index1<number_of_rows);
	return M[index1];
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(double multiplier){
	for (size_t i=0;i<number_of_rows;i++){
		for (size_t j=0;j<number_of_columns;j++){
			M[i][j]*=multiplier;
		}
	}
	return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(vector<double> vecMultiplier){ //умножение на вектор справа, в результате получаем столбец
	assert(vecMultiplier.size()==number_of_columns);
	vector<Row<T>> answer;
	for (size_t i=0;i<number_of_rows;i++){
		double res=0.0;
		for (size_t j=0;j<number_of_columns;j++){
			res+=M[i][j]*vecMultiplier[j];
		}
		answer.push_back(Row<T>(1,res));
	}
	M=answer;
	number_of_columns=1;
	return *this;
}

template <class T>
bool Matrix<T>::operator==(Matrix& M_compare){
	assert(number_of_rows==M_compare.get_number_of_rows() && number_of_columns==M_compare.get_number_of_columns());
	for (size_t i=0;i<number_of_rows;i++){
		for (size_t j=0;j<number_of_columns;j++){
			if (M[i][j]!=M_compare[i][j])
				return false;
		}
	}
	return true;
}

template <class T>
bool Matrix<T>::operator!=(Matrix& M_compare){
	return !(*this==M_compare);
}

void check(bool value)
{
	if (!value){
	        cerr << "error" << endl;
	}
}

void checkGetSet()
{
	Matrix<int> m(2, 3);

	check(m.get_number_of_rows()==2);
	check(m.get_number_of_columns()==3);

	//check(m[3][2]);
	//check(m[1][4]);
	
	m[0][0] = 1;
	m[0][1] = 2;
	m[0][2] = 3;
	m[1][0] = 4;
	m[1][1] = 5;
	m[1][2] = 6;
    
	check(m[0][0] == 1);
	check(m[0][1] == 2);
	check(m[0][2] == 3);
	check(m[1][0] == 4);
	check(m[1][1] == 5);
	check(m[1][2] == 6);
    	
	Matrix<int> m_copy1(m);

	check(m_copy1[1][1] == 5);

	Matrix<int> m_copy2=m;

	check(m_copy2[1][2] == 6);

	m[1][2] = 100;
    
	check(m[1][2] == 100);
	
	m[1][2] = 6;

	m*=2;
	
	check(m[0][0] == 2);
	check(m[0][1] == 4);
	check(m[0][2] == 6);
	check(m[1][0] == 8);
	check(m[1][1] == 10);
	check(m[1][2] == 12);

	vector<double> v(3,2);

	m*=v;

	check(m[0][0]==24);
	check(m[1][0]==60);

	Matrix<int> m1(2,3);

	m1[0][0] = 1;
	m1[0][1] = 2;
	m1[0][2] = 3;
	m1[1][0] = 4;
	m1[1][1] = 5;
	m1[1][2] = 6;

	Matrix<int> m2(2,3);
	
	m2[0][0] = 1;
	m2[0][1] = 2;
	m2[0][2] = 3;
	m2[1][0] = 4;
	m2[1][1] = 5;
	m2[1][2] = 6;

	check(m1==m2);

	m2[0][0] = 0;

	//check(m1==m2);
	check(m1!=m2);

	Matrix<int> m_move1(1,1);

	m_move1=move(m2);

	check (m_move1[1][1] == 5);
	//check (m2[1][1] === 5);


	Matrix<int> m_move2=move(m1);
	
	check(m_move2[0][0] == 1);
	check(m_move2[0][1] == 2);
	check(m_move2[0][2] == 3);
	check(m_move2[1][0] == 4);
	check(m_move2[1][1] == 5);
	check(m_move2[1][2] == 6);
	//check (m1[1][1] == 5);



}

int main(){
	checkGetSet();
	return 0;
}
