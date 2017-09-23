#include "timer.hpp"

int main(int argc, char const *argv[]) 
{
	const int size = 10000;

	int** matrix = new int* [size];
	volatile int sum = 0;

	for (int i = 0; i < size; ++i) {
		matrix[i] = new int [size];
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