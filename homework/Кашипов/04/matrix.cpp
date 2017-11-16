#include <iostream>
#include <vector>
#include <math.h>
#include <assert.h>

using namespace std;

class Row{
private:
	int len;
	double* vec;
public:
	Row(){
        len = 1;
        vec = new double[len];
        }
	Row(double* buf, int len_){
                vec=buf;
		len = len_;
	}
        //обращение к элементу в строке
	double& operator[](const int& j){
                if ((j>=len)||(j<0)){
                     assert(!"Index of matrix row out of range (cols)");
                    }
		return vec[j];
	}

};


class Matrix
{
 private:
     int rows;
     int cols;
     Row row;
     double *matrix;
 public:
     //конструктор
     Matrix(int rows_, int cols_)
         {
          if ((rows_<1)&&(cols_<1))
          {
           assert(!"Invalid size of matrix");
          }
          rows=rows_;
          cols=cols_;
          matrix = new double[rows*cols];
         }
     //копирование
     Matrix(const Matrix& matrix_)
      {
       cols = matrix_.cols;
       rows = matrix_.rows;
       matrix = new double[rows*cols];
       for (int i=0;i<rows*cols;i++)
           {
            matrix[i]=matrix_.matrix[i];
           }
      }
      //деструктор
     ~Matrix()
        {
         delete[] matrix;
        }
     //обращение к строке
     Row& operator[](const int& i){
                if ((i>=rows)&&(i<0)){
		    assert(!"Index of matrix out of range (rows)");
                }
		row = Row(matrix + (i*cols), cols);
		return row;
	}
     //умножение матрицы на число
     Matrix& operator*=(const double& num){
      for (int i=0;i<rows*cols;i++){
          matrix[i]*=num;
      } 
      return *this;
     }

     // умножение на вектор матрицу
     Matrix& operator*=(const vector<double>& vec){
        if (cols!=vec.size())
	    assert(!"Matrix and vector aren't compatable");
        double* vec_new = new double[rows];
        for(int i=0;i<rows;i++)
	    vec_new[i] = 0;
        for (int i=0;i<rows;i++) 	     
             for (int j=0;j<cols;j++)
                  vec_new[i]+=matrix[i*cols + j]*vec[j];
        delete[] matrix;
        cols = 1;
        matrix = new double[rows];
        for (int i=0;i<rows;i++)
            matrix[i] = vec_new[i];
        delete[] vec_new;  
        return *this;
     }
     // опреатор приравнивание
     Matrix& operator=(const Matrix& matrix_){
      delete[] matrix;
      cols = matrix_.cols;
      rows = matrix_.rows;
      double* matrix = new double[rows*cols];
      for (int i=0;i<cols*rows;i++)
          matrix[i]=matrix_.matrix[i];
      return *this;
     } 
     // оператор сравнения
     bool operator==(const Matrix& matrix_){
      bool answer=true;
      if ((cols!=matrix_.cols)||(rows!=matrix_.rows)){
          return false;
      }
      for (int i=0;i<cols*rows;i++)
          if(matrix[i]!=matrix_.matrix[i]){
             return false;
          }
      return true;
     }
     // проверка на неравенство
     bool operator!= (const Matrix& matrix_){
		return !(*this == matrix_);
	}
     int sizeRows(){
         return rows;
     }
     int sizeCols(){
       return cols;
     }
     void print(){
	for (int i = 0; i < rows; i++){
	   for (int j = 0; j < cols; j++){
	       cout << matrix[j + i*cols] << "  ";
	   }
	   cout << endl;
        }
     }
};



bool checkMatrixCreation(){
	Matrix m(2, 2);
	for (int i = 0; i < m.sizeRows(); i++){
		for (int j = 0; j < m.sizeCols(); j++){
			m[i][j] = i*m.sizeRows() + j;
                        
		}
	}
	int columns = m.sizeCols();
	int rows = m.sizeRows();
	if ((m[0][0]==0)&&(m[0][1]==1)&&(m[1][0]==2)&&(m[1][1]==3)&&(columns==2)&&(rows==2)){
		return true;
	}
	else{
		return false;
	}
}
bool checkMatrixMultiplyByNumber(){
			Matrix m(2, 2);
	for (int i = 0; i < m.sizeRows(); i++){
		for (int j = 0; j < m.sizeCols(); j++){
			m[i][j] = i*m.sizeRows() + j;
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
	Matrix m(2, 3);
	for (int i = 0; i < m.sizeRows(); i++){
		for (int j = 0; j < m.sizeCols(); j++){
			m[i][j] = i*m.sizeCols() + j;
		}
	}
	vector<double> v(3);
        v[0]=0;
	v[1] = 1;
        v[2] = 0;
	m*=v;
	if ((m[0][0]==1)&&(m[1][0]==4)){
		return true;
	}
	else{
		return false;
	}
}	
bool checkEqualMatrix(){
	Matrix m1(2,2);
	Matrix m2(2,2);
	for (int i = 0; i < m1.sizeRows(); i++){
		for (int j = 0; j < m1.sizeCols(); j++){
			m1[i][j] = i*m1.sizeRows() + j;
			m2[i][j] = i*m2.sizeRows() + j;
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
			cout<<"#1 OK"<<endl;
		}
	if (checkMatrixMultiplyByNumber()){
			cout<<"#2 OK"<<endl;
		}
	if (checkMatrixMultiplyByVector()){
				cout<<"#3 OK"<<endl;
		}
	if (checkEqualMatrix()){
			cout<<"#4 OK"<<endl;
		}
}
