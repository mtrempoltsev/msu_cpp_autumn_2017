#pragma once

#include "timer.hpp"
#include "constants.hpp"

void calculateArraySum(const int[DIM_SIZE][DIM_SIZE]);

void benchmarkArraySumCalculation(const int m[DIM_SIZE][DIM_SIZE]) {
	unsigned int heatingCycCount = HEATING_CYCLES_NUM;
	while (heatingCycCount--) {
		calculateArraySum(m);
	}
	unsigned int cycCount = CYCLES_NUM;
	while (cycCount--) {
		Timer timer;
		calculateArraySum(m);
	}
	Timer::printAverageTime();
}
