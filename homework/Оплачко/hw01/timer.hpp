#pragma once

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
