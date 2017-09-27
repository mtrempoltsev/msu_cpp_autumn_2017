
#include <iostream>
#include <chrono>
#include <iostream>

#define N 10000 //количество элементов
#define MAX_ITER 100 //количество замеров

/*
* В этой программе производится суммирование по столбцам и замер времени работы.
* */
int main()
{
	int** arr_mat = new int*[N];

	for (size_t i = 0; i< N; ++i)
	{
		arr_mat[i] = new int[N];
		for (size_t j = 0; j<N; ++j)
			arr_mat[i][j] = 1;
	}

	// разогрев
	std::cout << "Разогрев: " << std::endl;
	volatile long  sum = 0;
	for (volatile int j = 0; j < N; ++j) {
		for (volatile int i = 0; i < N; ++i) {
			sum += arr_mat[i][j];
		}
	}

	std::cout << "Результат: " << sum << std::endl;
	sum = 0;
	std::cout << "Суммирование по столбцам: " << std::endl;
	// по  строкам  а потом по столбцам

	long long sumTime = 0;
	std::chrono::high_resolution_clock::time_point finish;
	int m_it = 1;
	for (m_it = 1; m_it <= MAX_ITER; ++m_it)
	{
		const std::chrono::high_resolution_clock::time_point start_t = std::chrono::high_resolution_clock::now();
		for (volatile int j = 0; j < N; ++j) {
			for (volatile int i = 0; i < N; ++i) {
				sum += arr_mat[i][j];
			}
		}

		const auto finish_t = std::chrono::high_resolution_clock::now();
		const long long  cur_time = std::chrono::duration_cast<std::chrono::microseconds>(finish_t - start_t).count();

		std::cout << cur_time << std::endl;
		sumTime += cur_time;
	}

	std::cout << "Среднее время: " << sumTime / double(m_it) << std::endl;

	for (int i = 0; i< N; ++i)
		delete arr_mat[i];

	delete arr_mat;

	return 0;
}
