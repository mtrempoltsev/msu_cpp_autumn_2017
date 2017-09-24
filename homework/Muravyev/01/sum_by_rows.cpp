#include <chrono>
#include <iostream>

#define N 10000 // Задаем размерность матрицы

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

int main(){
	int** matrix = new int*[N];
	for(int k = 0;k < N;++k)
		matrix[k] = new int[N];
	int sum = 0;
	for(int k = 0;k < N;++k){
		for(int m = 0;m < N;++m){
			matrix[k][m] = 2;  // Заполняем матрицу
		}
	}
	Timer t;                           // Начинаем отсчет времени
	for(int i = 0;i < N;++i){
		for(int j = 0;j < N;++j){
			sum += matrix[i][j]; // Непосредственно суммирование элементов
		}
	}
	for(int n = 0;n < N;++n){
		delete[] matrix[n];
	}
	delete[] matrix;
	return sum;
}