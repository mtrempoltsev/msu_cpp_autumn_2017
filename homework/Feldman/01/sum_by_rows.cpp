#include <chrono>
#include <iostream>

using namespace std;
#define N 10000
class Timer
{
public:
	Timer()
		: start_(std::chrono::high_resolution_clock::now())
	{
	}

	~Timer()
	{
		const auto finish = std::chrono::high_resolution_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
	}

private:
	const std::chrono::high_resolution_clock::time_point start_;
};

int main() {
	int** matrix = new int*[N]; //create matrix

	for (int i = 0; i < N; ++i) {
		matrix[i] = new int[N];

		for (int j = 0; j < N; ++j) { // fill matrix 
			matrix[i][j] = 1;

		}
	}
	int sum = 0;
	{
		Timer t;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				sum += matrix[j][i]; //sum by rows
			}
		}
	}
	for (int i = 0; i < N; ++i) {
		delete[] matrix[i]; //delete matrix

	}
	delete matrix;
	cout << sum << endl;
	return 0;
}