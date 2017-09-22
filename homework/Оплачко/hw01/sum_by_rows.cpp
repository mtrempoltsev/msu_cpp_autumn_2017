#include <iostream>
#include <iomanip>
#include <chrono>
#include "constants.hpp"
#include "benchmark.hpp"

inline void calculateArraySum(const int m[DIM_SIZE][DIM_SIZE]) {
	volatile long long sum = 0;
	for (std::size_t i = 0; i < DIM_SIZE; i++) {
		for (std::size_t j = 0; j < DIM_SIZE; j++) {
			sum += m[i][j];
		}
	}
}

int main() {
	static int m[DIM_SIZE][DIM_SIZE];
	benchmarkArraySumCalculation(m);
	return 0;
}
