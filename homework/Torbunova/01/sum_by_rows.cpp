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
	//Summation by raws
	std::cout << "This is summation by raws" << std::endl;
	for (int k = 0; k < ATTEMPTS; k++)
	{
		Timer T;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				sum += m[i][j];
			}
		}
	}
	std::cout << "This is average time of summation by raws:  " << average_time/ATTEMPTS << std::endl;
	average_time = 0;

	for (int i = 0; i < N; i++){
		delete[] m[i];
	}
	delete[] m;
	return 0;
}


