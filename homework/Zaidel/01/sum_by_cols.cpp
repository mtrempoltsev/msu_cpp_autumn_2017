#include <iostream>
#include <chrono>
#include <iostream>

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


#define N 10000 //количество элементов

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

	Timer* timer = new Timer();
        
        sum = 0;
        for (volatile int j = 0; j < N; ++j) 
        {
	    for (volatile int i = 0; i < N; ++i)
            {
		sum += arr_mat[i][j];
	    }
        }
        
        delete timer;

        std::cout<<"RES: "<< sum<< std::endl;

	for (int i = 0; i< N; ++i)
		delete[] arr_mat[i];

	delete[] arr_mat;

	return 0;
}
