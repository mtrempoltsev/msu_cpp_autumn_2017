#include "timer.hpp"

int main() 
{
	const int size = 10000;

	static int matrix[size][size];
	volatile int sum = 0;

	//fill by 1
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; j++) {
			matrix[i][j] = 1;
		}
	}

	Timer* t = new Timer;
	for (int j = 0; j < size; ++j) {
		for (int i = 0; i < size; ++i) {
			sum += matrix[i][j];
		}
	}
	delete t;

	return 0;
}