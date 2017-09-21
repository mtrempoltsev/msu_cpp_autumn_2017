#include <iostream>
#include <iomanip>
#include <chrono>
#include "constants.hpp"

class Timer {
public:
	static std::chrono::microseconds::rep durationsSum;
	static unsigned int repeatsNumber;
	Timer() : start_(std::chrono::high_resolution_clock::now()) {}
	~Timer() {
		const auto finish = std::chrono::high_resolution_clock::now();
		const auto duration = std::chrono::duration_cast<
			std::chrono::microseconds>(finish - start_).count();
		durationsSum += duration;
		++repeatsNumber;
		std::cout << "Repeat #" << repeatsNumber << ": " << duration << " us" <<
			std::endl;
	}
	static void printAverageTime() {
		std::cout << "Average time: " << std::fixed << std::setprecision(0) <<
			static_cast<double>(durationsSum) / repeatsNumber << " us" <<
			std::endl;
	}
private:
	const std::chrono::high_resolution_clock::time_point start_;
};

std::chrono::microseconds::rep Timer::durationsSum = 0;
unsigned int Timer::repeatsNumber = 0;

inline void calculateArraySum(const int m[DIM_SIZE][DIM_SIZE]) {
	volatile long long sum = 0;
	for (std::size_t i = 0; i < DIM_SIZE; i++) {
		for (std::size_t j = 0; j < DIM_SIZE; j++) {
			sum += m[j][i];
		}
	}
}

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

int main() {
	static int m[DIM_SIZE][DIM_SIZE];
	benchmarkArraySumCalculation(m);
	return 0;
}
