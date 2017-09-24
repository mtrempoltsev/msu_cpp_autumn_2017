#pragma once

#include <iostream>
#include <iomanip>
#include <chrono>

namespace _Timer {
	std::chrono::microseconds::rep durationsSum = 0;
	unsigned int repeatsNumber = 0;

	void updateAndPrintTimerStats(std::chrono::microseconds::rep duration) {
		++repeatsNumber;
		durationsSum += duration;
		std::cout << "Repeat #" << repeatsNumber << ": " << duration << " us" <<
			std::endl;
	}
	void printAverageTimerStats() {
		std::cout << "Average time: " << std::fixed << std::setprecision(0) <<
			static_cast<double>(durationsSum) / repeatsNumber << " us" <<
			std::endl;
	}
}

class Timer {
public:
	Timer() : start_(std::chrono::high_resolution_clock::now()) {}
	~Timer() {
		const auto finish = std::chrono::high_resolution_clock::now();
		const auto duration = std::chrono::duration_cast<
			std::chrono::microseconds>(finish - start_).count();
		_Timer::updateAndPrintTimerStats(duration);
	}
private:
	const std::chrono::high_resolution_clock::time_point start_;
};
