#include <iostream>
#include <cmath>
#include <vector>

#define EPS 1e-6 // Double compare constant

class matrix{
private:
	int N,M;	// Matrix size
public:
	double** A; // Matrix pointer of pointers (2d array)
	matrix(int N_temp, int M_temp){ // Constructor
		N = N_temp;
		M = M_temp;

		A = new double*[N];
		for(int i=0;i<N;i++){
			A[i] = new double[M];
		}
	};

	void sample(){	//Put in  matrix order numbers
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				A[i][j] = i*M+j;
			}
		}
	};

	int get_rows(){    // Get N
		return N;
	};
	int get_columns(){ // Get M
		return M;
	};

	double get_elements(int i, int j){  //Get single elements, by indexes
		if ((i>=N) or (j>=M) or (i<0) or (j<0)){
				std::cout << "wrong indexs\n";
				return 0;//NULL;
			}
		else
			return A[i][j];
	};
	void print_matrix(){ // print matrix
		for(int i=0;i<N;i++){
			for(int k=0;k<M;k++){
				std::cout << A[i][k] << "\t";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	matrix operator+(const double& b){ // sum operator overloading
		for(int i=0;i<this->N;i++){
			for(int j=0;j<this->M;j++){
				this->A[i][j] = this->A[i][j]+b;
			}
		}
		return *this;
	}

	matrix operator*(const double& b){ // multiply overloading;
		for(int i=0;i<this->N;i++){
			for(int j=0;j<this->M;j++){
				this->A[i][j] = this->A[i][j]*b;
			}
		}
		return *this;
	}

	matrix operator*(const  std::vector<double> &v){ // multiply on vector;
		if (this -> M != v.size()){
			std::cout << "wrong size of vector M[" << this -> N <<"][" <<this -> M <<"]\t v[" << v.size() << "]\n";
			return *this;
		}
		matrix B = matrix(this->N,1);
		for(int i=0; i<this->N; i++){
			volatile double sum = 0.0;
			for(int k=0; k<this->M; k++){
				sum += this->A[i][k] * v[k];
			}
			B.A[i][0] =  sum;
		}
		return B;
	}

	bool operator==(const matrix& B){  //equal of matrix
		if ((this -> N != B.N) or (this -> M != B.M)) return false;
		for(int i=0; i<this->N; i++){
			for(int k=0; k<this->M; k++){
				if ( abs(B.A[i][k] - this -> A[i][k]) > EPS){
					return false;
				}
			}
		}
		return true; 
	}

};



int main(){
	// Matrix size
	int N = 5;
	int M = 4;
	matrix A = matrix(N,M);
	A.sample();
	A.print_matrix();
	std::cout << "columns\t" << A.get_columns() << "\n";
	std::cout << "rows.  \t" << A.get_rows() << "\n";
	std::cout << "A[" << N/2 << "][" << M/2 << "]\t" << A.get_elements(N/2, M/2) << "\n" << "\n";
	// matrix B = matrix(N,M);
	matrix c = A+-5;
	c.print_matrix();
	c = c*0.5;
	c.print_matrix();
	    // Создание вектора, содержащего целые числа
    std::vector<double> v = {1, 2, 0, 0};
 	c = c*v;
 	c.print_matrix();
 	bool e = c==c;
 	std::cout << "c==c" << e << "\n";

 	e = c==A;
 	std::cout << "c==A" << e << "\n";
 	// std :: cout << c==A;
 	// (c*v).print_matrix();
    // Проход по вектору с выводом значений
    // for ( int n : v ) {
    //     std::cout << n << '\n';
    // }
}