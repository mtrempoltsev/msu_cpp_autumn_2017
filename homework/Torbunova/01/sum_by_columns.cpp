#include "timer.hpp"
#include "constant.hpp"
using namespace std;





int main() {
	//Matrix creation
	int** m = new int* [N];
	for (int i = 0; i < N; i++){
		m[i] = new int[N];
	}


	//Matrix initialize
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			m[i][j] = i*N + j;
		}
	}

	volatile long int sum = 0;

	//Summation by columns
	std::cout << "This is summation by columns" << std::endl;
	for (int k = 0; k < ATTEMPTS; k++)
	{
		Timer T;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				sum += m[j][i];
			}
		}
	}
	std::cout << "This is average time of summation by columns:  " << average_time / ATTEMPTS << std::endl;
	//Delete matrix
	for (int i = 0; i < N; i++){
		delete[] m[i];
	}
	delete[] m;
	return 0;
}


