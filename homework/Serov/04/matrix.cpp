#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Row{ //понадобится для реализации [][]
public:
	vector <double> row;	
	size_t size;
	Row(size_t columns, double value){ //аналогично простому вектору
		assert(columns>0);
		row.resize(columns);
		size=columns;
		for (size_t i=0;i<columns;i++)
			row[i]=value;
	}
	double& operator[](size_t index2){  //вторые скобки
		assert(index2<size);
		return row[index2];
	}
	

};

class Matrix{
public:
	Matrix(size_t rows, size_t columns);
	size_t get_number_of_rows();  
	size_t get_number_of_columns();
	Row& operator[](size_t index1);  //первые скобки
	Matrix& operator*=(double multiplier); //умножение на число
	Matrix& operator*=(vector<double> vecMultiplier); //умножение на вектор
	bool operator==(Matrix& M_compare);
	bool operator!=(Matrix& M_compare);
private:
	size_t number_of_rows;
	size_t number_of_columns;
	vector <Row> M;
};

Matrix::Matrix(size_t rows,size_t columns){
	for (size_t i=0;i<rows;i++){
		M.push_back(Row(columns,0));
	}	
	number_of_rows=rows;
	number_of_columns=columns;
}

size_t Matrix::get_number_of_rows(){
	return number_of_rows;
}

size_t Matrix::get_number_of_columns(){
	return number_of_columns;
}

Row& Matrix::operator[](size_t index1){
	assert(index1<number_of_rows);
	return M[index1];
}

Matrix& Matrix::operator*=(double multiplier){
	for (size_t i=0;i<number_of_rows;i++){
		for (size_t j=0;j<number_of_columns;j++){
			M[i][j]*=multiplier;
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(vector<double> vecMultiplier){ //умножение на вектор справа, в результате получаем столбец
	assert(vecMultiplier.size()==number_of_columns);
	vector<Row> answer;
	for (size_t i=0;i<number_of_rows;i++){
		double res=0.0;
		for (size_t j=0;j<number_of_columns;j++){
			res+=M[i][j]*vecMultiplier[j];
		}
		answer.push_back(Row(1,res));
	}
	M=answer;
	number_of_columns=1;
	return *this;
}

bool Matrix::operator==(Matrix& M_compare){
	assert(number_of_rows==M_compare.get_number_of_rows() && number_of_columns==M_compare.get_number_of_columns());
	for (size_t i=0;i<number_of_rows;i++){
		for (size_t j=0;j<number_of_columns;j++){
			if (M[i][j]!=M_compare[i][j])
				return 0;
		}
	}
	return 1;
}

bool Matrix::operator!=(Matrix& M_compare){
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
	Matrix m(2, 3);

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

	Matrix m1(2,3);

	m1[0][0] = 1;
	m1[0][1] = 2;
	m1[0][2] = 3;
	m1[1][0] = 4;
	m1[1][1] = 5;
	m1[1][2] = 6;

	Matrix m2(2,3);
	
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

	//Matrix m3(3,2);

	//check(m1==m3);



}

int main(){
	checkGetSet();
	return 0;
}
