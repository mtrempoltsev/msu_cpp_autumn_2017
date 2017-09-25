#include <chrono>
#include <iostream>
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
	int** firstMatrix = new int*[N]; //В нее же записываем результат
	int** secondMatrix = new int*[N];
	for (int i = 0; i < N; ++i) {
		firstMatrix[i] = new int[N];
		secondMatrix[i] = new int[N];
		for (int j = 0; j < N; ++j) { // сразу же заполняем матрицы 
			firstMatrix[i][j] = 1;
			secondMatrix[i][j] = 2;
		}
	}
	{
		Timer t;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {				
			    firstMatrix[j][i] += secondMatrix[j][i]; //суммирование по столбцам
			}
		}
	}
	for (int i = 0; i < N; ++i) {
		delete[] firstMatrix[i];
		delete[] secondMatrix[i];
	}
	return 0;
}